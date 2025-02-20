### Function 1: `IsDLLLoadedInProcess`

```cpp
bool IsDLLLoadedInProcess(DWORD pid, const std::wstring& dllName)
```
#### Purpose:
This function checks whether a specific DLL (`dllName`) is loaded in a process with a given process ID (`pid`).

- **`pid`**: This stands for **Process ID**. It's the identifier of the process we're checking. We need to know which process to inspect, so `pid` represents that.
- **`dllName`**: This is the name of the **DLL** we're checking for within the given process. It's a string that will be used to compare with the names of loaded modules inside the process.

---

#### Inside the function:

1. **`hProcess`**:
   ```cpp
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
   ```
   - **`hProcess`** stands for **handle to the process**. A handle is a reference to an open object in Windows, and here it references the process we're inspecting.
   - We use this handle to query information about the process and read its memory.

2. **`modules`**:
   ```cpp
   std::vector<HMODULE> modules(1024);
   ```
   - **`modules`** is a **vector** that will store the handles of the modules (DLLs) loaded by the process.
   - We initialize it with a size of `1024` to accommodate up to 1024 modules (a good starting point).
   - **`HMODULE`** is a Windows type representing a module handle, which identifies a loaded module like a DLL or EXE.

3. **`cbNeeded`**:
   ```cpp
   DWORD cbNeeded;
   ```
   - **`cbNeeded`** stands for **bytes needed**. It stores the number of bytes returned by the function `EnumProcessModules`, which tells us how much memory is required to store the list of loaded modules.
   - This is used to determine how many modules were loaded in the process.

4. **`numModules`**:
   ```cpp
   size_t numModules = cbNeeded / sizeof(HMODULE);
   ```
   - **`numModules`** represents the **number of modules** loaded by the process. We calculate it by dividing `cbNeeded` (the number of bytes) by the size of a single `HMODULE` to get the number of modules.

5. **`moduleFileName`**:
   ```cpp
   wchar_t moduleFileName[MAX_PATH];
   ```
   - **`moduleFileName`** holds the **full path** of the DLL (or executable) file for each loaded module.
   - We use this buffer to store the path returned by the `GetModuleFileNameEx` function.

6. **`modulePath`**:
   ```cpp
   std::wstring modulePath(moduleFileName);
   ```
   - **`modulePath`** is a `std::wstring` that represents the full path of the loaded module (DLL or EXE). We convert the `moduleFileName` array into a `std::wstring` to make it easier to work with in C++.

7. **`found`**:
   ```cpp
   size_t found = modulePath.find(dllName);
   ```
   - **`found`** is used to check if the `dllName` exists in the `modulePath`.
   - `find` returns the position of the first occurrence of `dllName` in `modulePath` (if found). If the DLL is loaded, `found` will not be `std::wstring::npos` (which represents "not found").

---

### Function 2: `FindProcessIDsByName`

```cpp
std::vector<DWORD> FindProcessIDsByName(const std::wstring& processName)
```
#### Purpose:
This function finds and returns the **process IDs (PIDs)** of all processes with a specific name (`processName`).

- **`processName`**: The name of the process (e.g., "postgres.exe") we're looking for. We want to find processes with this name.

---

#### Inside the function:

1. **`aProcesses`**:
   ```cpp
   DWORD aProcesses[1024];
   ```
   - **`aProcesses`** is an array that holds the **list of all process IDs (PIDs)** on the system. It's large enough to hold up to `1024` PIDs.

2. **`cbNeeded`**:
   ```cpp
   DWORD cbNeeded;
   ```
   - **`cbNeeded`** stands for **bytes needed**. It stores how many bytes of process IDs were returned by `EnumProcesses`.

3. **`processCount`**:
   ```cpp
   unsigned int processCount;
   ```
   - **`processCount`** represents the number of processes returned by `EnumProcesses`. We calculate it by dividing `cbNeeded` (in bytes) by the size of a `DWORD` (the size of a PID).

4. **`pid`**:
   ```cpp
   DWORD pid = aProcesses[i];
   ```
   - **`pid`** is a single process ID from the `aProcesses` array. We use this to query the process and check its name.

5. **`hProcess`**:
   ```cpp
   HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
   ```
   - **`hProcess`** is a handle to the process we're checking. We use this to open the process and query its name.

6. **`szProcessName`**:
   ```cpp
   wchar_t szProcessName[MAX_PATH];
   ```
   - **`szProcessName`** is a buffer to store the **name of the process** (e.g., `postgres.exe`). We use this to check if the process matches the one we're looking for.

7. **`processIDs`**:
   ```cpp
   std::vector<DWORD> processIDs;
   ```
   - **`processIDs`** is a vector that will store the process IDs (PIDs) of all processes that match the `processName` we're looking for.

---

### Main Function

```cpp
int main()
{
    std::wstring processName = L"postgres.exe";
    std::wstring dllName = L"mbsbghelper.dll";
```
#### Purpose:
In the main function, we define the process name (`processName`) and DLL name (`dllName`) to search for.

- **`processName`**: We set it to `"postgres.exe"`, which is the name of the process we're looking for.
- **`dllName`**: We set it to `"mbsbghelper.dll"`, which is the DLL we want to check if it's loaded.

---

### Summary of Naming Conventions:

- **`pid`**: Stands for **process ID**. It's used to uniquely identify each process.
- **`dllName`**: The name of the **DLL** you're looking for in the process.
- **`hProcess`**: A **handle to the process** that lets us query information about it.
- **`modules`**: A vector holding the **module handles** (DLLs) loaded by the process.
- **`cbNeeded`**: The **number of bytes** needed to store the loaded modules.
- **`numModules`**: The **number of modules** loaded by the process (calculated from `cbNeeded`).
- **`moduleFileName`**: A buffer holding the **full path** of a loaded module.
- **`modulePath`**: A **wstring** containing the full path of a module, for easier manipulation.
- **`found`**: The position of the **DLL name** in the module path. It helps determine if the DLL is loaded in the process.
- **`aProcesses`**: An array that holds the **list of process IDs** for all processes.
- **`processCount`**: The number of **processes** returned by `EnumProcesses`.
- **`szProcessName`**: A buffer holding the **name of the process**.
- **`processIDs`**: A vector that stores the **process IDs** of processes that match the name you're looking for.



### 1. **`DWORD`**
- **Definition**: `DWORD` stands for **Double Word**. It is a data type used in Windows programming to represent a **32-bit unsigned integer**.
- **Why we use it**: In Windows API functions, many times we deal with process IDs (PIDs), memory sizes, and other values that require a 32-bit unsigned integer. `DWORD` is specifically designed for those types of values.
- **Example Usage**:
  ```cpp
  DWORD pid = aProcesses[i];
  ```
  Here, `pid` is a process ID, which is an unsigned 32-bit integer (since a process ID can't be negative).

### 2. **`wchar_t`**
- **Definition**: `wchar_t` is a **wide character type** that stores characters using 2 bytes (16 bits) instead of the regular `char` type which uses 1 byte (8 bits). It’s used for **wide characters**, which are typically used to represent characters in Unicode encoding.
- **Why we use it**: `wchar_t` is used to handle **wide characters** or **Unicode characters** (like those used in many international languages). Windows functions often require `wchar_t` instead of `char` because they are designed to work with **wide character sets**.
- **Example Usage**:
  ```cpp
  wchar_t szProcessName[MAX_PATH];
  ```
  This buffer will store a wide-character string representing the process name. Since many modern operating systems, including Windows, use Unicode encoding, `wchar_t` is appropriate for handling characters from many languages beyond just the English alphabet.

### 3. **`std::wstring`**
- **Definition**: `std::wstring` is a **C++ Standard Library type** that represents a **wide-character string** (essentially an array of `wchar_t`s). It is the wide-character counterpart to the standard `std::string`, which holds characters encoded in the ASCII or extended Latin character sets (using `char`).
- **Why we use it**: Since Windows often deals with wide characters (e.g., for Unicode support), the C++ Standard Library provides `std::wstring` to easily handle such strings. It makes it easier to work with wide-character data and includes built-in functions for manipulation.
- **Example Usage**:
  ```cpp
  std::wstring processName = L"postgres.exe";
  ```
  Here, we define the name of the process as a **wide string** (prefixed with `L` for wide-string literals in C++), because Windows API functions like `EnumProcesses` or `GetModuleBaseName` often return or expect `wchar_t`-based strings.

### 4. **`size_t`**
- **Definition**: `size_t` is an unsigned data type that is typically used to represent the **size of objects** in memory. It's used in situations where we need to store sizes or counts that are non-negative, and it is platform-dependent (i.e., 32-bit on 32-bit systems and 64-bit on 64-bit systems).
- **Why we use it**: `size_t` is the appropriate type for sizes, such as the size of arrays, the number of elements, and memory allocations, because it is guaranteed to be large enough to hold the size of any object on the platform. It’s particularly useful for **array indices** and **memory management**.
- **Example Usage**:
  ```cpp
  size_t numModules = cbNeeded / sizeof(HMODULE);
  ```
  Here, we use `size_t` to store the number of loaded modules, because it’s a **size-related** calculation.

### 5. **`HMODULE`**
- **Definition**: `HMODULE` is a Windows data type used to represent **module handles**. A module in this context can refer to either a loaded dynamic link library (DLL) or an executable (EXE).
- **Why we use it**: In the Windows API, when you query information about loaded modules (like DLLs), functions like `EnumProcessModules` return an array of `HMODULE` values. This is simply a handle that allows the program to identify and interact with the loaded module.
- **Example Usage**:
  ```cpp
  std::vector<HMODULE> modules(1024);
  ```
  Here, `modules` is a vector of module handles, which will be used to store the modules (DLLs or EXEs) loaded by a specific process.

---

### Summary: Why These Types Instead of `char`, `string`, etc.?

#### 1. **`char` vs `wchar_t`**:
- **`char`** is fine for representing single-byte characters (ASCII) but is **limited** to 256 characters.
- **`wchar_t`** allows handling **Unicode characters**, making it much more versatile for modern applications that need to support multiple languages or special characters.

#### 2. **`std::string` vs `std::wstring`**:
- **`std::string`** works with ASCII or other single-byte encodings.
- **`std::wstring`** is used for **wide-character strings**, which are necessary for working with **Unicode** text. Since many Windows API functions work with wide strings, we use `std::wstring` to align with these expectations.

#### 3. **`DWORD`**:
- `DWORD` is **specifically used for Windows programming**, where you need to represent 32-bit unsigned integers (e.g., process IDs, memory sizes, and other system-specific values).
- It is more **meaningful** than just using an `int` because it clearly indicates the Windows-specific 32-bit nature of the value.

#### 4. **`size_t`**:
- **`size_t`** is more appropriate than `int` for dealing with sizes, counts, or memory addresses, because it’s platform-dependent and guaranteed to be large enough to hold any size, making it safer and more flexible than `int` for these purposes.

---

### Recap of Key Types:
- **`DWORD`**: 32-bit unsigned integer used in Windows for things like process IDs.
- **`wchar_t`**: Wide character type used for Unicode characters, typically used in Windows API.
- **`std::wstring`**: C++ string type for working with wide-character strings (supports Unicode).
- **`size_t`**: Unsigned integer type used for sizes and counts, ensuring platform independence and correct memory handling.
- **`HMODULE`**: Represents a module handle used for working with loaded DLLs or executables.

These types are used in the code to ensure proper handling of wide-character strings, memory sizes, and Windows-specific values. By using them, we can ensure that our code is **platform-appropriate** and can handle the complexities of Unicode, memory management, and Windows system calls correctly.
