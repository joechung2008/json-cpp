# json.cpp

## License

MIT

## Reference

[json.org](http://json.org)

## Building, Running, and Testing with Visual Studio 2022 Build Tools

1. Install [Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

2. Download and install [cmake](https://cmake.org/download/) from the official website.

3. Open the "x64 Native Tools Command Prompt for VS 2022".

4. Navigate to the project directory:

5. Generate build files with CMake:

```sh
cmake -S . -B build
```

6. Build the project:

To make a Debug build:

```sh
cmake --build build
```

To make a Release build:

```sh
cmake --build build --config Release
```

7. Run the executable (adjust path if needed):

To run a Debug build:

````sh
out\Debug\cli.exe

To run a Release build:

```sh
out\Release\cli.exe
````

8. Run unit tests:

Unit tests use [doctest](https://github.com/doctest/doctest) version 2.4.12.

To run tests in Debug build:

```sh
out\Debug\tests.exe
```

To run tests in Release build:

```sh
out\Release\tests.exe
```

## Building and Running on Linux (WSL/Ubuntu)

1. Install required tools:

```sh
sudo apt update
sudo apt install build-essential cmake
```

2. Navigate to the project directory.

3. Generate build files:

```sh
cmake -S . -B build
```

4. Build the project:

```sh
cmake --build build
```

5. Run the CLI executable:

```sh
./out/cli
```

6. Run unit tests:

```sh
./out/tests
```
