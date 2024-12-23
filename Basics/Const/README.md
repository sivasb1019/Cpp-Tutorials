In C++, the `const` keyword is used to define constant values—variables that cannot be modified after initialization. It helps ensure that certain values or parameters remain unchanged throughout the program, providing better program safety, optimization opportunities, and clearer code.

Here are several uses of the `const` keyword in C++:

### 1. **Constant Variables**
You can define a constant variable, meaning its value cannot be changed after it is initialized.

```cpp
const int x = 10;
// x = 20;  // Error: cannot assign to a variable that is const
```

### 2. **Constant Pointers**
You can declare a pointer that points to a constant value, meaning the data it points to cannot be changed, although the pointer itself can be modified to point to another address.

```cpp
const int* ptr = &x;  // Pointer to a constant integer
// *ptr = 20;  // Error: cannot modify value through pointer
ptr = &y;  // Allowed: pointer can point to a different address
```

Alternatively, a pointer itself can be declared as constant, meaning the pointer cannot be modified to point to another address, but the data it points to can be changed.

```cpp
int* const ptr = &x;  // Constant pointer to an integer
*ptr = 20;  // Allowed: you can modify the data
// ptr = &y;  // Error: cannot change the address the pointer is pointing to
```

### 3. **Constant Member Functions**
In the context of classes, you can define member functions that do not modify the object’s state. Such functions are declared with the `const` keyword after the function signature.

```cpp
class MyClass {
public:
    int value;
    void setValue(int v) { value = v; }
    int getValue() const { return value; }  // This function does not modify the object
};
```

The `const` keyword here tells the compiler that `getValue()` will not alter the object’s data, making it a "const-correct" function.

### 4. **Constant References**
You can pass parameters by reference and ensure they cannot be modified inside the function using `const` references.

```cpp
void printValue(const int& x) {
    // x = 10;  // Error: cannot modify a const reference
    std::cout << x << std::endl;
}
```

### 5. **Constant Function Parameters**
You can also use `const` to protect function arguments, ensuring that they are not modified.

```cpp
void printConstantValue(const int value) {
    // value = 10;  // Error: cannot modify a const parameter
    std::cout << value << std::endl;
}
```

### 6. **Constant Expressions**
In C++11 and later, `constexpr` is a keyword that also specifies constants, but it ensures that the expression is evaluated at compile time. The `const` keyword guarantees that the value is constant, but it doesn't require compile-time evaluation.

```cpp
const int a = 5;  // Constant variable
constexpr int b = 10;  // Constant expression, evaluated at compile-time
```

### 7. **Const with Arrays**
Arrays and pointers can also use `const` to ensure the data or the pointer itself remains constant.

```cpp
const int arr[5] = {1, 2, 3, 4, 5};
// arr[0] = 10;  // Error: cannot modify the array elements
```

### 8. **Const with `enum` Constants**
In C++ enumerations, `const` can be used to define constant values.

```cpp
enum Color {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

const Color favoriteColor = GREEN;
```

### Summary of `const` behavior:
- **`const` variable**: The value cannot be changed after initialization.
- **`const` pointer**: Either the pointer or the data it points to can be made constant.
- **`const` member function**: The function does not modify the object it belongs to.
- **`const` parameter**: Ensures that the parameter cannot be modified inside the function.

`const` is a powerful tool to enforce immutability and improve the reliability and clarity of your code.