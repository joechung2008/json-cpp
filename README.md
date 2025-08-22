# json.cpp

## License

MIT

## Reference

[json.org](http://json.org)

## Building and Running with Visual Studio 2022 Build Tools

1. Install [Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

2. Download and install [cmake](https://cmake.org/download/) from the official website.

3. Open the "x64 Native Tools Command Prompt for VS 2022".

4. Navigate to the project directory:

5. Generate build files with CMake:

```sh
cmake -S . -B build
```

6. Build the project:

```sh
cmake --build build --config Release
```

7. Run the executable (adjust path if needed):

```sh
out\Release\cli.exe
```
