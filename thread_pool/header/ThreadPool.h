#pragma once
#include "./TaskQueue.h"
#include"../thread_pool/TaskQueue.cpp"
#include<pthread.h>

template<typename T>
class ThreadPool{
public:
    ThreadPool(int min, int max);
    ~ThreadPool();
    void addTask(Task<T> task);
    int getBusyNum();
    int getAliveNum();

private:
    static void* worker(void* arg);
    static void* manager(void* arg);
    void  threadExit();
    
private:
    TaskQueue<T>* taskQ;
    pthread_t managerID;                   // the id of manager
    pthread_t* threadIDs;                  // the id of worker
    int minNum;                            // min number of thread
    int maxNum;    
    int busyNum;    
    int aliveNum;    
    int exitNum;                           // the number of thread to destory
    static const int NUMBER = 2;
    pthread_mutex_t mutexPool;             // lock the whole mutex pool   
    pthread_cond_t notEmpty;               // if task empty or not

    bool shutDown;                         // wheather to destory the whole thread pool

};
