---
trigger: always_on
---

# Rule: sc-code-rule

- You are an excellent programmer. Please help me write and check the program code according to the following coding standards.

## 0. Code Language and Platform

-   **Platform**: LINUX
-   **Languages**: C/C++/Shell Script/CSV/XML/JSON

## 1. Version Information

### 1.1 Version Statement Content

The following copyright statement must be included:

```
Copyright (c) 2025 SerComm Corporation. All Rights Reserved.

SerComm Corporation reserves the right to make changes to this document
without notice. SerComm Corporation makes no warranty, representation or
guarantee regarding the suitability of its products for any particular
purpose.

SerComm Corporation assumes no liability arising out of the application or
use of any product or circuit. 

SerComm Corporation specifically disclaims any and all liability, including
without limitation consequential or incidental damages; neither does it convey
any license under its patent rights, nor the rights of others.
```

### 1.2 Files Requiring Version Statement

This statement should be included in, but not limited to, the following files:
-   C/C++ source and header files
-   Makefiles
-   Script Files (e.g., Shell, Batch)

## 2. Comments

### 2.1 Comment Style

-   All comments must use the `/* ... */` block style.

    ```c
    /* This is a single-line comment. Make it a complete sentence. */

    /*
     * This is a multi-line comment, make it a real paragraph.
     * The comment continues here.
     */
    ```

### 2.2 Language

-   All comments must be written in English.

### 2.3 Consistency

-   Comments must be kept consistent with the code's functionality. When code is modified, the corresponding comments must be updated immediately.

### 2.4 Function Documentation

-   Every function must have a corresponding comment block that includes:
    -   Parameter information
    -   Return value
    -   A clear description of the function's purpose

## 3. Memory Safety

### 3.1 Memory Leaks

-   Dynamically allocated memory must be freed promptly after use to prevent memory leaks.

### 3.2 Use After Free

-   Accessing memory that has already been freed is strictly prohibited. This can cause segmentation faults and corrupt other data in memory.

### 3.3 Stack Overflow

-   Do not allocate memory blocks larger than 4KB on the stack. For larger allocations, use heap memory (`malloc`, `new`) or static memory.

### 3.4 Buffer Overflows

-   Prevent memory access from going out of bounds.
    -   Allocate sufficiently large memory buffers.
    -   Use secure string functions (e.g., `strncpy` instead of `strcpy`).
    -   Ensure `mem*` function operations do not exceed buffer boundaries.
    -   Remember that C-style strings are terminated with a `\0` null character.
    -   Be mindful of the step size when performing pointer arithmetic.
    -   Always validate array indices.
    -   Use `sizeof` or `strlen` correctly to calculate buffer sizes and string lengths.

## 4. Branches and Loops

### 4.1 Braces

-   Both `if` and `else` statements must be enclosed in curly braces `{}`.

### 4.2 Switch Statements

-   Each `case` in a `switch` statement must be terminated with a `break`. If a `break` is intentionally omitted (fall-through), a comment explaining the reason is required.
-   A `default` branch is mandatory in all `switch` statements.

### 4.3 `goto` Statement

-   Avoid using `goto`. For deeply nested loops, consider refactoring the logic into sub-functions.

## 5. Expressions and Operators

### 5.1 Confusing Operators

-   Be careful with easily confused operators, such as assignment (`=`) vs. equality (`==`), bitwise OR (`|`) vs. logical OR (`||`), and bitwise AND (`&`) vs. logical AND (`&&`).

### 5.2 `sizeof` Operator

-   Do not use `sizeof` on expressions that have side effects. `sizeof` is evaluated at compile time, so the side-effect expression will not be executed at runtime.

### 5.3 Logical Operators

-   The right-hand side of logical operators (`&&`, `||`) should not contain expressions with side effects, as they may not be executed due to short-circuit evaluation.

### 5.4 Floating-Point Comparison

-   Do not use `==` or `!=` for floating-point comparisons due to precision issues. Use `<`, `<=`, `>`, or `>=` instead.

### 5.5 Return Statements

-   All function exit paths must have a `return` statement, except for the end of a `void` function.

### 5.6 Integer Overflow/Underflow

-   Be aware of potential upper and lower bound overflows in expression calculations.

## 6. Variables and Pointers

### 6.1 Variable Scope

-   Use `static` to limit the scope of global variables. Global variables intended for external linkage (`extern`) should be prefixed with `g_`.

### 6.2 Magic Numbers

-   Avoid using magic numbers (literal numeric values without a clear meaning). Use named constants or variables instead.

### 6.3 Variable Range

-   Pay attention to the valid numerical range of variable types.

## 7. I/O and String Operation Safety

### 7.1 Input Validation

-   Always validate user input, especially in the following scenarios:
    -   Input used as a loop condition.
    -   Input used as an array index.
    -   Input used to determine memory allocation size.
    -   Input used as a format string.
    -   Input used as business data (e.g., command-line arguments, SQL queries).

-   **Validation Checks**:
    -   For numerical input, check if the value is within the expected range.
    -   For string input, check the length.
    -   For format strings, validate or escape `%` characters.
    -   For business data, sanitize or escape special keywords.

### 7.2 Secure Functions

-   Use string functions with size limitations (e.g., `strncpy`) and the safer `_s` suffixed versions where available.

## 8. Functions and Statements

### 8.1 Braces Style

-   Opening braces for function bodies should be on a new line and in the same column.

    ```c
    void func()
    {
        /* ... */
    }
    ```

### 8.2 One Statement Per Line

-   Write only one executable statement per line.

## 9. Compilation

### 9.1 Compiler Flags

-   When compiling with GCC, enable `-Wall` and `-Werror` flags to treat all warnings as errors and fix them.

### 9.2 Library Priority

-   Use library functions in the following order of preference:
    1.  Standard C/C++ Library Functions
    2.  Standard LINUX (POSIX) Platform Library Functions
    3.  Company-level Common Library Functions
    4.  Project-level Common Library Functions
    5.  Custom Functions