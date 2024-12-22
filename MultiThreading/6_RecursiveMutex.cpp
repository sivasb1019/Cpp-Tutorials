/*
Recursive Mutex in C++ (std::recursive_mutex)

    - A std::recursive_mutex is similar to a regular std::mutex, but with one key difference: the same thread can lock the mutex multiple times. This is useful when a thread needs to acquire the lock more than once in recursive functions.

    - If Thread T1 first calls lock() or try_lock() on a recursive_mutex (m1), then m1 is locked by T1. If T1 is running recursively (or in a nested call), T1 can call lock() or try_lock() on m1 any number of times without issues.

    - However, if Thread T1 acquires the lock multiple times (e.g., 10 times), it will have to unlock it the same number of times before any other thread can acquire the lock. 
    - This means that std::recursive_mutex keeps a count of how many times it has been locked, and it expects that many unlock() calls.

    - There is no predefined limit to how many times a thread can lock a recursive_mutex, but:

    - If you call lock() and the mutex has already been locked too many times, it may throw a std::system_error (this is often due to recursion limits or system restrictions).
    - If you use try_lock() and it exceeds the allowed limit, it will return false.
    
BOTTOM LINE:
    - std::recursive_mutex is similar to a regular std::mutex but allows the same thread to lock it multiple times without causing a deadlock.
    - Avoid using std::recursive_mutex if possible because it introduces overhead, especially in cases where the thread locking the mutex multiple times can be avoided.
    - std::recursive_mutex can be used in recursive functions or loops, but you should carefully manage how many times you lock it to avoid unnecessary complexity or performance issues.

Overhead::
-  std::recursive_mutex introduces additional overhead compared to std::mutex because it needs to track how many times it has been locked by the same thread. 
- It also adds complexity in terms of managing lock counts.
Why to avoid:
- If you find yourself needing a recursive mutex, it's usually a sign that the design might need improvement. Recursive locking is often an indication of potential issues in program structure, and non-recursive alternatives (e.g., rethinking the design) can often simplify the logic and improve performance.
*/

#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

recursive_mutex mtx;

void recursiveFunction(int t, int count) {
    if (count <= 0) return;
    
    mtx.lock();  // First lock
    cout << t << " Thread locked   " << count << " times.\n";
    
    recursiveFunction(t, count-1);  // Recursive call
    
    mtx.unlock();  // Unlock first time
    cout << t << " Thread unlocked " << count << " times.\n";
}

int main() {
    thread t1(recursiveFunction, 1, 3);
    thread t2(recursiveFunction, 2, 4);
    t1.join();
    return 0;
}
