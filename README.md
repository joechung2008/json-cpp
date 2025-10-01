# json.cpp

## License

MIT

## Reference

[json.org](http://json.org)

## Dependencies

- [doctest](https://github.com/doctest/doctest) v2.4.12 (automatically downloaded via CMake FetchContent)

## Prerequisites

### Win32 (Windows) Builds

- **Visual Studio 2022 Build Tools**
  - Install the "Desktop development with C++" workload.
  - Ensure the following components are selected:
    - MSVC v143 - VS 2022 C++ x64/x86 build tools
    - Windows 10 SDK (or newer)
    - CMake tools for Windows
- **CMake** (https://cmake.org/download/)

### glibc (Linux) Builds

- **glibc** (provided by most Linux distributions)
- **build-essential** (for GCC, g++, make, etc.)
- **CMake**

Install on Ubuntu:

```sh
sudo apt update
sudo apt install build-essential cmake
```

## Building, Running, and Testing with Visual Studio 2022 Build Tools

1. Open the "x64 Native Tools Command Prompt for VS 2022".

2. Navigate to the project directory:

3. Generate build files with CMake:

```sh
cmake -S . -B build
```

4. Build the project:

To make a Debug build:

```sh
cmake --build build
```

To make a Release build:

```sh
cmake --build build --config Release
```

5. Run the executable (adjust path if needed):

To run a Debug build:

````sh
out\Debug\cli.exe

To run a Release build:

```sh
out\Release\cli.exe
````

6. Run unit tests:

Unit tests use [doctest](https://github.com/doctest/doctest).

To run tests in Debug build:

```sh
out\Debug\tests.exe
```

To run tests in Release build:

```sh
out\Release\tests.exe
```

## Building and Running on Linux (WSL/Ubuntu)

1. Navigate to the project directory.

2. Generate build files:

```sh
cmake -S . -B build
```

3. Build the project:

```sh
cmake --build build
```

4. Run the CLI executable:

```sh
./out/cli
```

5. Run unit tests:

```sh
./out/tests
```
