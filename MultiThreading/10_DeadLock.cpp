/*
### **Deadlock in C++**

A **deadlock** is a situation in concurrent programming where two or more threads are waiting for each other to release resources, resulting in a standstill where none of the threads can proceed.

---

### **Causes of Deadlock**

Deadlocks occur when the following four conditions hold simultaneously (the Coffman conditions):

1. **Mutual Exclusion**:
   - A resource is held by one thread and cannot be shared.

2. **Hold and Wait**:
   - A thread holding a resource is waiting to acquire additional resources held by other threads.

3. **No Preemption**:
   - Resources cannot be forcibly taken from a thread; they must be released voluntarily.

4. **Circular Wait**:
   - A circular chain of threads exists, where each thread is waiting for a resource held by the next thread in the chain.


### **How to Avoid Deadlock**

1. **Use a Consistent Locking Order**:
   - Always acquire locks in the same order.
   - Example: If both threads lock `mutex1` before `mutex2`, deadlocks can be avoided.

2. **Use `std::lock()` for Lock Acquisition**:
   - `std::lock()` locks multiple mutexes simultaneously without causing deadlock.

3. **Avoid Nested Locks**:
   - Minimize or avoid scenarios where a thread locks one mutex and then attempts to lock another.

4. **Use a Timeout**:
   - Use `std::unique_lock` with a timeout to avoid waiting indefinitely for a lock.

5. **Use Higher-Level Constructs**:
   - Replace manual locks with thread-safe data structures or abstractions like `std::async` or thread pools.

---

### **Detecting Deadlocks**

Deadlocks are hard to detect because they often depend on timing. Tools like **thread sanitizers** or specialized debugging utilities can help identify deadlocks in complex programs.

---

### **Key Points**

1. Deadlocks occur when threads are stuck waiting for resources held by each other.
2. Avoid them using consistent locking order, `std::lock()`, or timeouts.
3. Deadlocks can degrade system performance and must be addressed during the design phase.
*/

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mutex1;
mutex mutex2;

void thread1() {
    lock_guard<mutex> lock1(mutex1); // Lock mutex1
    this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    lock_guard<mutex> lock2(mutex2); // Try to lock mutex2
    cout << "Thread 1 acquired both mutexes.\n";
}

void thread2() {
    lock_guard<mutex> lock2(mutex2); // Lock mutex2
    // this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    lock_guard<mutex> lock1(mutex1); // Try to lock mutex1
    cout << "Thread 2 acquired both mutexes.\n";
}

int main() {
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
