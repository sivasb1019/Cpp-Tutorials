/*
`std::async` is a function used to launch asynchronous tasks. 
    - It allows you to execute a function or callable object in a separate thread and retrieve its result using a `std::future` object. 
    - This enables concurrent programming without directly managing threads.

## **Key Features of `std::async`:**

1. **Asynchronous Execution:**
   - It runs the specified function in a separate thread by default, allowing your program to continue executing while the function runs in the background.

2. **Return Value Handling:**
   - It returns a `std::future` object, which can be used to retrieve the result of the asynchronous task when it’s ready.

3. **Error Handling:**
   - If an exception occurs in the asynchronous task, it is stored in the `std::future` and rethrown when `get()` is called.

4. **Execution Policy:**
   - You can control whether the task runs asynchronously or lazily (on-demand) using `std::launch` policies.

## **Syntax:** - std::future<T> std::async(std::launch policy, Callable&& f, Args&&... args);

### **Parameters:**
- **`policy`** *(optional)*:
  - Defines how the task is executed:
    - `std::launch::async`: Runs the task asynchronously in a new thread.
    - `std::launch::deferred`: Delays execution until the result is needed (when `get()` or `wait()` is called). (it is not create a thread)
    - Combined policies like `std::launch::async | std::launch::deferred` allow the system to decide.
- **`Callable`**:
  - The function or callable object to execute.
- **`Args`**:
  - Arguments to pass to the function.

### **Return Value:**
- A `std::future` object that represents the result of the asynchronous operation.

## **Advantages of `std::async`:**
1. Simplifies asynchronous programming by managing threads automatically.
2. Handles exceptions thrown in asynchronous tasks.
3. Supports both eager (async) and lazy (deferred) execution.
4. Eliminates the need for explicit thread creation and management.

## **Limitations of `std::async`:**
1. May not provide fine-grained control over thread creation and pooling compared to `std::thread`.
2. Combining launch policies (`std::launch::async | std::launch::deferred`) leaves the execution mode to system discretion, which might be non-deterministic.
3. Additional overhead compared to manually managing threads for simpler cases.

`std::async` is a powerful and flexible tool for concurrent programming, ideal for tasks where thread management should be abstracted and simplified.
*/

#include <iostream>
#include <future>
#include <thread>

using namespace std;

int compute(int sec) {
    cout << "Waiting inside compute function..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Simulate a delay
    cout << "Waiting completed..." << endl;
    return 10;
}

int main() {
    future<int> asyncResult = async(launch::async, compute, 2); // thread will be created
    future<int> deferredResult = async(launch::deferred, compute, 2); // thread will be no created

    // this_thread::sleep_for(chrono::seconds(2)); // Simulate a delay
    // Wait for the asyncResult
    cout << "Waiting for asyncResult...\n";
    int value1 = asyncResult.get();
    cout << "The asyncResult is: " << value1 << "\n";

    // Wait for the deferredResult
    cout << "Waiting for deferredResult...\n";
    int value2 = deferredResult.get();
    cout << "The deferredResult is: " << value2 << "\n";

    return 0;
}