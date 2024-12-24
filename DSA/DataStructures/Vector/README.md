# Vector in C++ STL
- Vector is a dynamic array which stored in a contiguos memory.
- Add or remove can be done at the end and can accessible by index.
- **Use when**: 
	- You need a dynamic array with fast random access (constant time) and efficient memory usage. 
	- It’s efficient when you need to frequently append elements at the end.
- **When to avoid**: 
	- When you need to insert or delete elements at the front or in the middle of the collection frequently, as these operations are costly (O(n)).

### Syntax of Vector
```cpp
vector<T> vec_name;
```

### Declaration and Initialization:
1. Default Initialization

	- An empty vector can be created using the below declaration. This vector can be filled later on in the program.
	```cpp
	vector<T> vec_name;
	```

2. Initialization with Size and Default Value

	- A vector of a specific size can also be declared and initialized to the given value as default value.
	```cpp
	vector<T> vec_name(size, value); 
	```

3. Initialization Using Initializer List

	- Vector can also be initialized using a list of values enclosed in {} braces separated by comma.
	```cpp
	vector<T> vec_name = { v1, v2, v3….};
	vector<T> vec_name ({ v1, v2, v3….});
	```

### Basic Vector Operations

```cpp
vector<char> v = {'a', 'c', 'f', 'd', 'z'};
```
1. Accessing Elements
	- Just like arrays, vector elements can be accessed using their index inside the [] subscript operator. 
	- This method is fast but doesn’t check whether the given index exists in the vector or not. 
	- So, there is another member method vector at() for safely accessing elements.

	```cpp
	v[3]; // 'd'
    v.at(2); // 'f'
	```

2. Updating Elements
	- Updating elements is very similar to the accessing except that we use an additional assignment operator to assign a new value to a particular element. 
	- It uses the same methods: [] subscript operator and vector at().

	```cpp
	v[3] = 's'; // 's'
    v.at(2) = 'b'; // 'b'
	```

3. Traversing Vector
	- Vector in C++ can be traversed using indexes in a loop. 
	- The indexes start from 0 and go up to vector size – 1. 
	- To iterate through this range, we can use a loop and determine the size of the vector using the vector size() method.

	```cpp
	for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
	```

4. Inserting Elements
	- An element can be inserted into a vector using vector insert() method which takes linear time. 
	- But for the insertion at the end, the vector push_back() method can be used. 
	- It is much faster, taking only constant time.

	```cpp
	// Inserting 'z' at the back
      v.push_back('z');
  
      // Inserting 'c' at index 1
      v.insert(v.begin() + 1, 'c');
	```

5. Deleting Elements
	- An element can be deleted from a vector using vector erase() but this method needs iterator to the element to be deleted. 
	- If only the value of the element is known, then find() function is used to find the position of this element.
	- For the deletion at the end, the vector pop_back() method can be used, and it is much faster, taking only constant time.

	```cpp
	// Deleting last element 'z'
      v.pop_back();
	// Deleting element 'f'
      v.erase(find(v.begin(), v.end(), 'f'));
	```

Here's the table with the added column for time complexity of each `std::vector` function. The time complexities depend on factors like whether the operation is on the end of the vector, the middle, or the beginning, as well as the size of the vector.

| **Category**              | **Function**           | **Description**                                                                                     | **Time Complexity**            |
|---------------------------|------------------------|-----------------------------------------------------------------------------------------------------|--------------------------------|
| **Inserting Elements**     | `push_back()`          | Adds an element to the end of the vector.                                                           | **Amortized O(1)**             |
|                           | `emplace_back()`       | Constructs and inserts an element at the end of the vector.                                          | **Amortized O(1)**             |
|                           | `insert()`             | Inserts elements at a specific position in the vector.                                               | **O(n)** (where n is the number of elements after the insertion point) |
|                           | `emplace()`            | Constructs and inserts an element in the vector at a specified position.                            | **O(n)** (where n is the number of elements after the insertion point) |
| **Deleting Elements**      | `pop_back()`           | Removes the last element of the vector.                                                             | **O(1)**                       |
|                           | `erase()`              | Removes elements from a specific position or range in the vector.                                   | **O(n)** (where n is the number of elements after the erased element) |
|                           | `clear()`              | Removes all elements from the vector, making it empty.                                              | **O(n)**                       |
| **Accessing Elements**     | `operator[]`          | Accesses the element at a specific position (unchecked).                                           | **O(1)**                       |
|                           | `at()`                 | Accesses the element at a specific position, with bounds checking.                                  | **O(1)**                       |
|                           | `front()`              | Accesses the first element of the vector.                                                           | **O(1)**                       |
|                           | `back()`               | Accesses the last element of the vector.                                                            | **O(1)**                       |
|                           | `begin()`              | Returns an iterator pointing to the first element of the vector.                                    | **O(1)**                       |
|                           | `end()`                | Returns an iterator pointing to the past-the-end element of the vector.                             | **O(1)**                       |
|                           | `rbegin()`             | Returns a reverse iterator pointing to the last element of the vector.                              | **O(1)**                       |
|                           | `rend()`               | Returns a reverse iterator pointing to the element preceding the first element of the vector.       | **O(1)**                       |
| **Constant Accessing**     | `cbegin()`            | Returns a const_iterator to the beginning of the vector.                                            | **O(1)**                       |
|                           | `cend()`               | Returns a const_iterator to the end of the vector.                                                  | **O(1)**                       |
|                           | `crbegin()`            | Returns a const_reverse_iterator to the reverse beginning.                                          | **O(1)**                       |
|                           | `crend()`              | Returns a const_reverse_iterator to the reverse end.                                                | **O(1)**                       |
| **Size/Capacity**          | `size()`               | Returns the number of elements in the vector.                                                       | **O(1)**                       |
|                           | `capacity()`           | Returns the size of the storage space currently allocated to the vector.                            | **O(1)**                       |
|                           | `max_size()`           | Returns the maximum number of elements that the vector can hold.                                    | **O(1)**                       |
|                           | `empty()`              | Checks if the vector is empty.                                                                      | **O(1)**                       |
|                           | `resize()`             | Changes the size of the vector. If the size is increased, new elements are default-initialized.     | **O(n)** (where n is the new size of the vector) |
|                           | `reserve()`            | Requests that the vector capacity be at least enough to contain a specified number of elements.      | **O(n)** (where n is the requested capacity) |
|                           | `shrink_to_fit()`      | Reduces memory usage by freeing unused space (non-binding request).                                  | **O(n)** (where n is the number of elements) |
| **Memory Management**      | `data()`               | Returns a direct pointer to the memory array used internally by the vector to store its owned elements. | **O(1)**                       |
|                           | `get_allocator()`      | Returns a copy of the allocator object associated with the vector.                                   | **O(1)**                       |
| **Other Operations**       | `swap()`               | Swaps the contents of the vector with those of another vector.                                       | **O(n)** (where n is the size of the vector) |
|                           | `assign()`             | Assigns new values to the vector elements by replacing old ones.                                    | **O(n)** (where n is the number of elements) |

### Summary of Time Complexity:

- **Amortized O(1)**: Operations like `push_back()` and `emplace_back()` generally take constant time, but occasional resizing might take longer.
- **O(1)**: Operations like `front()`, `back()`, `operator[]`, `at()`, and others that simply access or return values are constant-time operations.
- **O(n)**: Operations like `insert()`, `erase()`, `clear()`, and `resize()` that require shifting elements or resizing the internal data structure have linear time complexity.
- **O(n)** for `swap()`, `assign()`, `shrink_to_fit()`, and some other operations that depend on the number of elements in the vector.

### Time Complexity Considerations:

- **`push_back()` and `emplace_back()`**: These are generally O(1), but when the vector needs to resize, the complexity becomes O(n) due to the reallocation and copying of elements. However, since reallocations occur infrequently, the average time complexity is amortized O(1).
- **`insert()` and `erase()`**: These are linear-time operations because they may require shifting elements after the insertion or removal.
- **`resize()` and `reserve()`**: These operations involve resizing the underlying memory and might involve copying or reallocating the data, which is why their complexity depends on the number of elements involved.
  
This table provides a comprehensive view of the functions and their time complexities for the `std::vector` class in C++.
### Summary of Categories:

1. **Inserting Elements**: Functions like `push_back()`, `insert()`, `emplace_back()`, and `emplace()` are used to add elements to the vector.
2. **Deleting Elements**: Functions like `pop_back()`, `erase()`, and `clear()` are used to remove elements from the vector.
3. **Accessing Elements**: Functions like `operator[]`, `at()`, `front()`, `back()`, and iterators (`begin()`, `end()`, `rbegin()`, `rend()`) allow access to elements.
4. **Constant Accessing**: The `cbegin()`, `cend()`, `crbegin()`, and `crend()` functions provide access to the vector’s elements as constant iterators, preventing modification.
5. **Size/Capacity**: Functions like `size()`, `capacity()`, `max_size()`, `empty()`, and `resize()` help manage the size and capacity of the vector.
6. **Memory Management**: `data()` and `get_allocator()` give control over the internal memory management and allocator.
7. **Other Operations**: Functions like `swap()` and `assign()` provide additional functionality for modifying the vector’s contents or its relationship with other vectors.

This classification should make it easier for you to understand which functions are used for specific tasks when working with `std::vector`.
