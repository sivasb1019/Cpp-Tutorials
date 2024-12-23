/*
Unique Lock:
    - The class unique_lock is a mutex ownership wrapper.
    - A std::unique_lock in C++ is a more flexible and feature-rich locking mechanism compared to std::lock_guard. 
    - It is part of the C++ Standard Library, defined in the <mutex> header, and provides a way to lock and unlock mutexes in a 
      more controlled manner, supporting various locking strategies and features like deferred locking, manual unlocking, and lock ownership transfer.
    
    - It Allows:
        a. Can Have Different Locking Strategies
        b. time-constrained attempts at locking (try_lock_for, try_lock_until) c. recursive locking
        d. transfer of lock ownership (move not copy)
        e. condition variables. See this in coming videos
    
Locking Strategies:
        TYPE                                EFFECTS (S)
    1. defer lock               do not acquire ownership of the mutex.
    2. try_to_lock              try to acquire ownership of the mutex without blocking.
    3. adopt_lock               assume the calling thread already has ownership of the mutex.
    
    
    
    

Key Features of std::unique_lock:
Flexibility:
    - std::unique_lock provides greater flexibility than std::lock_guard, allowing you to lock and unlock a mutex manually, 
      control when the lock is acquired, and even transfer lock ownership between threads.

Deferred Locking:
    - You can create a std::unique_lock object without immediately locking the mutex. 
    - The lock can be acquired later using the lock() method.
    
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    lock.lock()

Manual Unlocking:
    - Unlike std::lock_guard, which automatically unlocks the mutex when the object goes out of scope, 
      std::unique_lock allows you to manually unlock the mutex at any point using the unlock() method.
    
    std::unique_lock<std::mutex> lock(mtx);
    lock.unlock();

Lock Ownership Transfer:
    - std::unique_lock can be moved between scopes, and the ownership of the lock can be transferred. 
    - This allows more complex locking scenarios where you might want to transfer the lock from one function or thread to another.

    std::unique_lock<std::mutex> lock(mtx);
    std::unique_lock<std::mutex> lock2 = std::move(lock); 

Supports Recursion:
    - It can work with both regular std::mutex and std::recursive_mutex, allowing recursive locking when necessary.

Condition Variables:
    - std::unique_lock is often used in conjunction with condition variables (via std::condition_variable), 
      as it supports waiting and notification operations (via wait(), notify_one(), etc.).

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [](){ return ready; });

*/

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int money = 0;
mutex mtx;

void printMoneyCount(string t) {
    unique_lock<mutex> lock(mtx);
    cout << t << " Count: ";
    for (int i = 1; i < 10+1; i++) {
        money++; //critical section
        cout << i << " ";
    }
    cout << endl << t << " Money: " << money << endl << endl;
}

void deferLock(const char *threadNumber, int limit){
    unique_lock<mutex> lock(mtx, defer_lock); // doesn't lock the mutex as defer lock is mentioned.
    lock.lock();
    cout << threadNumber << " Count: ";
    for (int i = 1; i <= limit; i++) {
        money++; //critical section
        cout << i << " ";
    }
    cout << endl << threadNumber << " Money: " << money << endl << endl;

    // lock.unlock(); is not needed as the unique lock destructor will unlock it.
}


int main() {
    // thread t1(printMoneyCount, "Thread 1");
    // thread t2(printMoneyCount, "Thread 2");

    thread t1(deferLock, "Thread 1", 10);
    thread t2(deferLock, "Thread 2", 10);

    t1.join();
    t2.join();

    cout << "Total Money: " << money << endl;

    return 0;

}
