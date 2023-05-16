#pragma once
#include<queue>
#include<pthread.h>

using callback = void(*)(void* arg);

template<class T>
class Task{
public:
    Task<T>(){
        function = nullptr;
        arg = nullptr;
    }
    Task<T>(callback f, void* arg){
        this->arg = static_cast<T*> (arg);
        function = f;
    }

    callback function;
    T* arg;
};

template<typename T>
class TaskQueue{
public:
    TaskQueue();
    ~TaskQueue();

    void addTask(Task<T> task);             // add a task
    void addTask(callback f, void* arg);
    Task<T> takeTask();                     // take a task
    inline size_t taskNumber();

private: 
    pthread_mutex_t _mutex;
    std::queue<Task<T>> _taskQ;
};