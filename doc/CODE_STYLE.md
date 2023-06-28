# Code Style

Consistent code style is important for readability and maintainability of the project's codebase. Please follow these guidelines when writing code for i8080-core:

## Indentation
Use a consistent indentation of **4 spaces** for each level of indentation. Avoid using tabs for indentation.

**Do this:**
```c
    extern int placeholder_variable;
```

**Not this:**
```c
  extern int placeholder_variable;
```

## Braces
Place opening braces on the **same line** as the corresponding control statement or function declaration. Place closing braces on a new line, aligned with the opening statement. We live in the 21th century so please place your braces according to this.

**Do this:**
```c
    void code_like_a_young_person() {
        // ...
    }
```

**Not this:**
```c
    void code_like_a_ww1_veteran()
    {
        // ...
    }
```

## Line Length
Limit lines to a maximum of **80 characters**. This helps maintain code readability across different environments and reduces the need for horizontal scrolling.

## Naming Conventions
Use descriptive and meaningful names for variables, functions, and types. Use **underscores** for variable and function names. Avoid using single-letter variable names except for loop counters or other well-known conventions.

**Do this:**
```c
    extern int placeholder_variable;
```

**Not this:**
```c
  extern int placeholderVariable;
```

## Comments
Include helpful and explanatory comments to document the code's functionality, but **only** for complex logic or to explain non-obvious decisions. Use inline comments sparingly and only when necessary. Remember that code should document itself.

## Function Length
Keep functions concise and focused. Aim for shorter functions that perform a specific task. If a function becomes too long or complex, consider refactoring it into smaller, reusable functions.

## File Organization
Organize code files logically and keep them focused on a single responsibility. Use proper directory structure and modularization to separate concerns and improve maintainability.

<hr>

Remember, these guidelines are meant to enhance code consistency and readability across the project. Feel free to refer to existing code for examples and follow the existing style conventions.

By following these code style guidelines, we can maintain a clean and readable codebase that is easier to understand and maintain.