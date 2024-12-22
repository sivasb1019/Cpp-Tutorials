/*
### Condition Variables:
   - Condition variables are a synchronization mechanism that enables threads to communicate with one another efficiently and wait for specific conditions to be met before proceeding.
   - They are a part of the C++ Standard Library and are defined in the `<condition_variable>` header.

   - **Why Use Condition Variables?**
     - Thread Communication:
       - Allows one thread to notify others that a specific event has occurred.
     - Avoiding Busy Waiting:
       - Threads can wait efficiently without constantly polling a shared resource.
     - Producer-Consumer Problems:
       - Synchronizes threads for tasks like buffer sharing, where producers and consumers operate on shared data.

   - **Key Functions:**
     - `wait()`:
       - Makes the thread wait until it is notified.
     - `notify_one()`:
       - Wakes up one waiting thread.
     - `notify_all()`:
       - Wakes up all waiting threads.
*/


#include <iostream> 
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std;

condition_variable cv; 
mutex mtx;
long balance = 0;

void depositMoney (int money) {
    cout << "Deposit money...\n";
    lock_guard<mutex> lg (mtx);
    balance+=money;
    cout << "Amount Added Current Balance: " << balance << endl; 
    cv.notify_one();
}

void withdrowMoney (int money) {
    cout << "withdraw money...\n";
    unique_lock<mutex> ul (mtx); 
    cv.wait(ul, [] { return (balance!=0) ? true : false; }); // if the condition not met, it release the mutex.
    
    if (balance >= money) {
        balance = balance - money;
        cout << "Amount Deducted:" << money << endl;
    }
    else{
        cout << "Amount Can't Be Deducted, Current Balance Is Less Than " << money << endl;
    }
    cout <<"Current Balance Is: " << balance << endl;
}

int main() {
    thread t1(withdrowMoney, 500);
    thread t2 (depositMoney, 500);
    t1.join();
    t2.join(); return 0;
}