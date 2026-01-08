---
description: 'C++ implementation guidelines for lab assignments with CMake build system'
applyTo: 'docs/src/*.cpp, docs/src/*.hpp'
---

# C++ Implementation Guidelines

## Project Context

- **Language**: C++23 (Visual Studio `/std:c++latest`)
- **Build**: CMake 3.20+
- **Location**: All source files in `docs/src/`

## Best Practices

- Use RAII, prefer smart pointers over raw pointers
- Use standard library: `std::vector`, `std::string`, `std::array`
- Throw exceptions for errors: `std::invalid_argument`, `std::runtime_error`
- Mark no-throw functions with `noexcept`

## Code Standards

**Naming:**
- Classes/Types: `PascalCase`
- Functions: `camelCase`
- Variables: `snake_case`
- Constants: `UPPER_CASE`
- Private members: `m_` prefix

**Formatting:**
- Indentation: 2 spaces
- Line length: under 100 characters

**Comments:** See examples in `.github/agents/examples/cpp-class-template.cpp`

## Build System (CMake)

**Basic CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.20)
project(Lab)
set(CMAKE_CXX_STANDARD 23)
set(SOURCES docs/src/main.cpp)
add_executable(lab Length{SOURCES})
```

**For GUI with OpenGL:**
```cmake
add_executable(lab WIN32 Length{SOURCES})
target_link_libraries(lab opengl32 glu32)
```

**Build commands:**
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release
build\Release\lab.exe
ctest --test-dir build -C Release --output-on-failure
```

## Windows OpenGL Application Pattern

**Complete template**: See `.github/agents/examples/cpp-opengl-template.cpp`

**Key points:**
- Use ANSI strings (`"text"`), NOT wide strings (`L"text"`)
- WinMain  register window class  create window  main loop
- `EnableOpenGL()` / `DisableOpenGL()` for context initialization

## Testing Patterns

**Complete template**: See `.github/agents/examples/cpp-test-template.cpp`

**CRITICAL:**
- CTest runs from `build/tests/`, use relative path `..\\Release\\lab.exe`
- ALWAYS `#include <vector>` when using `std::vector`
- Use ANSI strings with CreateProcessA (NOT `L"..."`)

**tests/CMakeLists.txt:**
```cmake
add_executable(lab_tests test_main.cpp)
enable_testing()
add_test(NAME Lab_Validation COMMAND lab_tests)
```

## Report Integration

Reference code in Typst reports:

```typst
#figure(
  raw(read("src/main.cpp"), lang: "cpp", block: true),
  caption: [Source file main.cpp],
) <file-main>
```
