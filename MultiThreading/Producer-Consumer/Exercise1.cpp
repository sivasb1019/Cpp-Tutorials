/*
Producer Consumer OR Bounded Buffer Problem
THE PROBLEM STATEMENT:
    1. Producer will produce and consumer will consume with synchronization of a common buffer. 
    2. Until producer thread produces any data consum thread can't consume
    3. Threads will use condition_variable to notify each other.
    4. We need mutex if we use condition_variable because CV waits on mutex. 
    5. This is one of the example of producer consumer there are many.
PRODUCER thread steps:
    1. lock mutes, if success then go ahead otherwise wait for mutex to get free.
    2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
    3. insert item in buffer.
    4. unlock mutex.
    5.notify consumer.
CONSUMER thread steps:

1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume. 
3. consume item from butter
4. unlock mutex.
5. notify producer

Note:
Producer and Consumer have to notify each other upon comletion of their job
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;
mutex mtx;
condition_variable cv;
queue<int> numbers;
int free_ = 5, full = 0;

void producer(){
    cout << "Producer Waiting....\n";
    do{
        unique_lock<mutex> lock(mtx);
        cout << "Producer got the lock..." << endl;
        cv.wait(lock, [] { return (free_>0) ? true : false;});
        free_--;
        cout << "Producer Started. Pushing to the queue..." << endl;
        numbers.push(10);
        full++;
        cout << "full: " << full << " free: " << free_ << endl;
        cout << "Notifying Consumer..." << endl << endl;
        lock.unlock();
        cv.notify_one();
    }while(5);
}

void consumer(){
    cout << "Consumer Waiting....\n";
    do{
        unique_lock<mutex> lock(mtx);
        cout << "Consumer got the lock..." << endl;
        cv.wait(lock, [] { return (full>0) ? true : false;});
        full--;
        cout << "Consumer Started. Popping from the queue..." << " ";
        cout << numbers.front() << endl;;
        numbers.pop();
        free_++;
        cout << "full: " << full << " free: " << free_ << endl;
        cout << "Notifying Producer..." << endl << endl;
        lock.unlock();
        cv.notify_one();
    }while(5);
    
}

int main(){
    thread t1(producer);
    thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}