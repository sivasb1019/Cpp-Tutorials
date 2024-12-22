/*
Lock Gaurd:
lock_guard is a RAII (Resource Acquisition Is Initialization) style mechanism used to manage mutex locking and unlocking in a safe and efficient manner. 
It is part of the C++ Standard Library, defined in the <mutex> header, and is typically used to ensure that a mutex is locked for the duration of a scope and automatically unlocked when the scope is exited (i.e., when the lock_guard object goes out of scope).

Key Features of std::lock_guard:

Automatic Locking and Unlocking:
    - When a std::lock_guard object is created, it locks the associated mutex.
    - When the lock_guard object is destroyed (goes out of scope), it automatically unlocks the mutex, even in case of exceptions.

Exception-Safety:
    - The RAII principle guarantees that the mutex will be unlocked even if an exception occurs within the scope, preventing potential deadlocks.

Simplification:
        - It reduces the risk of human errors, such as forgetting to unlock a mutex, since the unlocking happens automatically when the lock_guard is destructed.

Non-Copyable:
    - std::lock_guard is non-copyable and non-movable to prevent accidental transfer of mutex ownership.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

using namespace std;

int money = 0;
mutex mtx;

void printMoneyCount(string t) {
    lock_guard<mutex> lock(mtx);
    cout << t << " Count: ";
    for (int i = 1; i < 10+1; i++) {
        money++; //critical section
        cout << i << " ";
    }
    cout << endl << t << " Money: " << money << endl << endl;
}

int main() {
    thread t1(printMoneyCount, "Thread 1");
    thread t2(printMoneyCount, "Thread 2");

    t1.join();
    t2.join();

    cout << "Total Money: " << money << endl;

    return 0;

}
