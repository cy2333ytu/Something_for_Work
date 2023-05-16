#include"../header/TaskQueue.h"
#include<pthread.h>

template<typename T>
TaskQueue<T>::TaskQueue(){
    pthread_mutex_init(&_mutex, NULL);
}

template<typename T>
TaskQueue<T>::~TaskQueue(){
    pthread_mutex_destroy(&_mutex);
}

template<typename T>
void TaskQueue<T>::addTask(Task<T> task){
    pthread_mutex_lock(&_mutex);
    _taskQ.push(task);
    pthread_mutex_unlock(&_mutex);
}

template<typename T>
void TaskQueue<T>::addTask(callback f, void* arg){
    pthread_mutex_lock(&_mutex);
    _taskQ.push(Task<T>(f, arg));
    pthread_mutex_unlock(&_mutex);
}

template<typename T>
Task<T> TaskQueue<T>::takeTask(){
    Task<T> t;
    pthread_mutex_lock(&_mutex);
    if(!_taskQ.empty()){
        t = _taskQ.front();      // take out the first elem but it still in the queue
        _taskQ.pop();            // remove the first elem in the queue 
    }
    pthread_mutex_unlock(&_mutex);

    return t;
}

template<typename T>
inline size_t TaskQueue<T>::taskNumber(){
    return _taskQ.size();
}