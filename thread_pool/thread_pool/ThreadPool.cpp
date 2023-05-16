#include"../header/ThreadPool.h"
#include<iostream>
#include<pthread.h>
#include<string.h>
#include<string>
#include<unistd.h>

template<typename T>
ThreadPool<T>::ThreadPool(int min, int max){
    do{
        taskQ = new TaskQueue<T>;
        if(taskQ == nullptr){
            std::cout<< "malloc taskQ fails..."<< std::endl;
            break;
        }

        threadIDs = new pthread_t[max];
        if(threadIDs == nullptr){
            std::cout<< "malloc threadIDs fail..."<< std::endl;
            break;
        }
        memset(threadIDs, 0, sizeof(pthread_t)*max);   //  initial threadIDs to 0
        minNum = min;                            
        maxNum = max;    
        busyNum = 0;    
        aliveNum = min;    
        exitNum = 0;  

        if(pthread_mutex_init(&mutexPool, NULL) != 0 || 
                    pthread_cond_init(&notEmpty, NULL) != 0){
                        std::cout<<"mutex or condition init fail..."<< std::endl;
                        break;
        }

        shutDown = false;

        pthread_create(&managerID, NULL, manager, this);
        for(int i = 0; i< min; ++i){
            pthread_create(&threadIDs[i], NULL, worker, this);
        }
        return;

    } while (0);
    
    if(threadIDs) delete[] threadIDs;
    if(taskQ) delete taskQ;

}

template<typename T>
void* ThreadPool<T>::worker(void* arg){
    ThreadPool* pool = static_cast<ThreadPool*> (arg);
    while(1){
        pthread_mutex_lock(&pool->mutexPool);
        // determine if  task queue is empty
        while (pool->taskQ->taskNumber() == 0 && !pool->shutDown){
            // no things to do, so we block thread
            pthread_cond_wait(&pool->notEmpty, &pool->mutexPool);
            if(pool->exitNum > 0){
                pool->exitNum--;
                // wheather to destory thread
                if(pool->aliveNum > pool->minNum){
                    pool->aliveNum--;
                    pthread_mutex_unlock(&pool->mutexPool);
                    pool->threadExit();
                }
            }
        }
        // if thread-pool shutdown
        if(pool->shutDown){
            pthread_mutex_unlock(&pool->mutexPool);
            pool->threadExit();
        }
        // take a task from task_queue
        Task<T> task = pool->taskQ->takeTask();

        pool->busyNum++;
        pthread_mutex_unlock(&pool->mutexPool);

        std::cout<<"thread " << pthread_self() << " start working" << std::endl;

        task.function(task.arg);
        delete task.arg;             // task is a local vari, but its para located at heap
        task.arg = nullptr;
        
        std::cout<<"thread " << pthread_self() << " end working" << std::endl;

        pthread_mutex_lock(&pool->mutexPool);
        pool->busyNum--;
        pthread_mutex_unlock(&pool->mutexPool);
    }
    return NULL;
}

template<typename T>
void* ThreadPool<T>::manager(void* arg){
    ThreadPool* pool = static_cast<ThreadPool*> (arg);
    while (!pool->shutDown){
        // detect every 2s
        sleep(2);

        // find out the number of thread in task-pool and current thread
        // find out the number of busy thread
        pthread_mutex_lock(&pool->mutexPool);
        int queueSize = pool->taskQ->taskNumber();
        int aliveNum = pool->aliveNum;
        int busyNum = pool->busyNum;
        pthread_mutex_unlock(&pool->mutexPool);

        // according the strategy to add thread
        if(queueSize > aliveNum && aliveNum < pool->maxNum){
            pthread_mutex_lock(&pool->mutexPool);
            int counter = 0;
            for (int i = 0; i < pool->maxNum && counter < NUMBER &&
                    pool->aliveNum < pool->maxNum; i++){
                if(pool->threadIDs[i] == 0){
                    pthread_create(&pool->threadIDs[i], NULL, worker, pool);
                }
                pool->aliveNum++;
            }
            pthread_mutex_unlock(&pool->mutexPool);        
        }
        //destory thread
        if(busyNum *2 < aliveNum && aliveNum > pool->minNum){
            pthread_mutex_lock(&pool->mutexPool);
            pool->exitNum = NUMBER;
            pthread_mutex_unlock(&pool->mutexPool);        
            for (int i = 0; i < NUMBER; i++){
                pthread_cond_signal(&pool->notEmpty);
            }
        }

    }
    return NULL;
    
}

template<typename T>
void ThreadPool<T>::threadExit(){
    pthread_t tid = pthread_self();
    for (int i = 0; i < maxNum; i++){
        if(threadIDs[i] == tid){
            threadIDs[i] = 0;
            std::cout<< "threadExit() called " << tid << " exiting..." <<std::endl; 
            break;
        }
    }
    pthread_exit(NULL);
}

template<typename T>
void ThreadPool<T>::addTask(Task<T> task){
    if(shutDown){
        return;
    }
    taskQ->addTask(task);                // there is already a mutex lock in taskQ 
    pthread_cond_signal(&notEmpty);
}

template<typename T>
int ThreadPool<T>::getBusyNum(){
    pthread_mutex_lock(&mutexPool);
    int busyNum = this->busyNum;
    pthread_mutex_unlock(&mutexPool);
    return busyNum;
}

template<typename T>
int ThreadPool<T>::getAliveNum(){
    pthread_mutex_lock(&mutexPool);
    int aliveNum = this->aliveNum;
    pthread_mutex_unlock(&mutexPool);
    return aliveNum;
}

template<typename T>
ThreadPool<T>::~ThreadPool(){
    shutDown = true;  
    pthread_join(managerID, NULL);
    for(int i = 0; i < aliveNum; i++){
        pthread_cond_signal(&notEmpty);
    }
    if(taskQ){
        delete taskQ;
    }
    if (threadIDs){
        delete [] threadIDs;
    }
    pthread_mutex_destroy(&mutexPool);
    pthread_cond_destroy(&notEmpty);
    
}
