#include"./header/ThreadPool.h"
#include"./thread_pool/ThreadPool.cpp"
#include<unistd.h>
#include<iostream>
#include<pthread.h>

void taskFunc(void* arg);

int main(){

    ThreadPool<int> pool(3, 10);
    for (int i = 0; i < 100; i++){
        int* num = new int(i+100);
        pool.addTask(Task<int>(taskFunc, num));
    }
    sleep(5);
    return 0;
}

void taskFunc(void* arg){
    int num = *(int*) arg;
    std::cout<< "thread " << pthread_self() << " is working, "<<
    "num is " << num << std::endl;
    sleep(1);
}