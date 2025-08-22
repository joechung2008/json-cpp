# GitHub Copilot Instructions

## Project Overview

This project is a modular C++ JSON parser with a clear separation of concerns:

- **CLI entry point:** `src/cli/main.cpp`
- **Parsers:** `src/lib/parsers/` (modular files for each JSON type)
- **Token types:** `src/lib/types/` (object-oriented token classes inheriting from `Token`)

## Code Style

- Use modern C++ (C++11 or newer) features.
- Prefer smart pointers (`std::shared_ptr`) for memory management.
- Use `std::string` and STL containers.
- Follow consistent indentation (4 spaces).
- Place opening braces on the same line.

## Architectural Patterns

- Keep parsing logic modular: each JSON type has its own parser file/class.
- Token classes should inherit from the base `Token` class.
- Use the single-responsibility principle for classes and functions.
- Prefer composition over inheritance where possible.

## Naming Conventions

- Classes: `PascalCase` (e.g., `ArrayToken`)
- Functions: `camelCase` (e.g., `parseArray`)
- Variables: `camelCase`
- File names: lowercase with type (e.g., `array.cpp`, `arraytoken.hpp`)

## Important Files to Reference

- `src/cli/main.cpp`: CLI entry and argument handling.
- `src/lib/parsers/array.cpp`, `number.cpp`, etc.: Parsing logic for each JSON type.
- `src/lib/types/token.hpp`: Base token class.
- `src/lib/types/arraytoken.hpp`, etc.: Token implementations.

## Additional Guidance

- Write clear, concise comments for complex logic.
- Ensure code is testable and maintainable.
- Avoid global variables.
- Use exceptions for error handling.

Copilot should generate code that fits these patterns and conventions.
