# Future and Promise

### **`std::future` and `std::promise` in C++**

`std::future` and `std::promise` are tools provided by the C++ Standard Library to enable asynchronous programming and communication between threads. promise is like a setter and fuure is like a getter.

---

### **1. `std::future`**
A `std::future` is an object that represents a value or exception that will be set at some point in the future. It acts as a placeholder for the result of an asynchronous operation.

#### **Key Features of `std::future`:**
- Retrieves the result of an asynchronous computation.
- Waits for the computation to finish if the result isn't ready.
- Obtained from `std::async`, `std::packaged_task`, or `std::promise`.

#### **Member Functions:**
- **`get()`**: Retrieves the value or exception from the future (blocks if not ready).
- **`wait()`**: Waits for the asynchronous operation to finish.
- **`valid()`**: Checks if the future has a valid state.
- **`wait_for()` / `wait_until()`**: Waits for a specified time.

---

### **2. `std::promise`**
A `std::promise` is an object that provides a mechanism for a thread to set a value or exception to be retrieved by a `std::future`.

#### **Key Features of `std::promise`:**
- Creates a communication channel between threads.
- Used to set the value (or exception) of a `std::future`.

#### **Member Functions:**
- **`get_future()`**: Returns a `std::future` associated with the promise.
- **`set_value()`**: Sets the result value.
- **`set_exception()`**: Sets an exception.

---

### **Relationship Between `std::future` and `std::promise`**

- **`std::promise`** produces the result (or exception), and **`std::future`** retrieves it.
- A `std::future` is associated with exactly one `std::promise`.

---

### **Best Practices**

1. Use `std::promise` and `std::future` when you need manual control over result sharing between threads.
2. Use `std::async` or `std::packaged_task` for simpler asynchronous tasks.
3. Always handle exceptions in asynchronous operations to prevent undefined behavior.

---

### **Summary**

- **`std::future`**: Retrieves results from asynchronous tasks.
- **`std::promise`**: Allows a thread to set results for a `std::future`.

Together, they form a powerful mechanism for inter-thread communication and synchronization.
