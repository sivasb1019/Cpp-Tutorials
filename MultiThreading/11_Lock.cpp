/*
### **`std::lock` in C++**

`std::lock` is a utility function in the C++ Standard Library that allows you to lock multiple `std::mutex` objects simultaneously without risking a **deadlock**. It ensures that all the provided mutexes are locked in a deadlock-free manner by determining a safe order of locking internally.

### **Key Features of `std::lock`**

1. **Deadlock-Free**: 
   - It prevents deadlocks by atomically locking all the provided mutexes.

2. **Lock Multiple Mutexes**:
   - It can lock two or more mutexes passed as arguments.

3. **Flexibility**:
   - Can be used with `std::mutex`, `std::timed_mutex`, `std::recursive_mutex`, and other mutex types.

4. **Combination with `std::adopt_lock`**:
   - When `std::lock` is used, you must pass `std::adopt_lock` to the `std::lock_guard` or `std::unique_lock` to indicate that the mutexes are already locked.


### Syntax - std::lock(mutex1, mutex2, ...);

- The function attempts to lock all mutexes passed to it. If any mutex is already locked by another thread, it waits until it becomes available.

### **Advantages of `std::lock`**

1. **Deadlock Prevention**:
   - It is a safe way to acquire multiple locks without worrying about the order of acquisition.

2. **Simplicity**:
   - Removes the burden of manually locking and unlocking mutexes in the correct order.

### **When to Use `std::lock`?**
- When you need to acquire multiple locks at the same time.
- To avoid deadlocks in multi-threaded applications.

### **Notes**
- If any mutex cannot be locked, `std::lock` will block until it can acquire all mutexes.
- If exceptions are thrown during the locking process, it ensures that no mutexes are left in a locked state.

### **Best Practices**
1. Use `std::lock` instead of manually locking mutexes when handling multiple locks.
2. Always use `std::adopt_lock` with `std::lock_guard` or `std::unique_lock` after calling `std::lock`.


 Example        Thread 1                           Thread 2               is Deadlock
    1       std::lock(m1, m2);                std::lock(m1, m2);              No
    2       std::lock(m1, m2);                std::lock(m2, m1);              No
    3       std::lock(m1, m2, m3, m4);        std::lock(m3, m4);              No
                                              std::lock(m2, m1);              
    4       std::lock(m1, m2);                std::lock(m3, m4);              Yes
            std::lock(m3, m4);                std::lock(m2, m1);              
*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1;
std::mutex mutex2;

void thread1() {
    std::lock(mutex1, mutex2); // Lock both mutexes atomically
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 1 has locked both mutexes.\n";
}

void thread2() {
    std::lock(mutex2, mutex1); // Lock both mutexes atomically
    std::lock_guard<std::mutex> lock1(mutex1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mutex2, std::adopt_lock);

    std::cout << "Thread 2 has locked both mutexes.\n";
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
