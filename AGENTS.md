# Agent Guidelines for Lab Template

Technical guidelines for GitHub Copilot Custom Agents working with this lab template.

## Custom Agents

Located in `.github/agents/`:

| Agent | Purpose | Key Responsibilities |
|-------|---------|---------------------|
| **Orchestrator** | Workflow coordination | Manages multi-agent workflow from verification to report |
| **Verificator** | Task extraction from PDF | Validates task requirements, extracts report structure |
| **Coder** | Code implementation | Writes C++ or C# code in `docs/src/` with Russian comments |
| **QA** | Testing and validation | Creates test directory, writes unit tests, validates code |
| **Writer** | Report generation | Creates Typst report with code listings and screenshots |

## Shared Instructions

All agents follow common rules from `.github/agents/instructions/`:

| File | Purpose | Key Content |
|------|---------|-------------|
| **common.instructions.md** | Common rules for all agents | Russian language (comments/output), prohibition of .md files, project structure, build commands |
| **cpp-implementation.md** | C++ specific guidelines | Windows OpenGL patterns, CMake, testing patterns |
| **csharp-implementation.md** | C# specific guidelines | .NET patterns, project structure |

Each agent references `common.instructions.md` to avoid duplication and ensure consistency.

## Project Structure

```
project/
├── .github/agents/     # Copilot agents
├── docs/
│   ├── demo.typ        # Template example (DO NOT MODIFY)
│   ├── lab.typ         # Lab report (created by Writer)
│   ├── lib/            # ГОСТ formatting
│   │   ├── gost.typ
│   │   └── titlepage.typ
│   ├── images/         # Screenshots
│   └── src/            # Source code
│       └── main.cpp
└── AGENTS.md
```

## Build Commands

### Compile Code (Console App)
```
# Configure
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run (note: Release subdirectory for Visual Studio)
.\build\Release\lab.exe
```

### Compile Code (Windows GUI with OpenGL)
```
# Configure for Visual Studio 2022 (32-bit)
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32

# Build
cmake --build build --config Release

# Run
.\build\Release\lab.exe
```

### Run Tests
```
# Build tests
cmake --build build --config Release

# Run with CTest (runs from build/tests/)
ctest --test-dir build -C Release --output-on-failure
```

### Compile Report
```
typst compile docs/lab.typ docs/lab.pdf
```

### Watch Mode
```
typst watch docs/lab.typ docs/lab.pdf
```

## Code Style

- **C++**: Standard C++17+, 2 spaces indentation
- **C#**: .NET 8+, 4 spaces indentation
- **Comments**: Russian (mandatory)
- **Output**: Russian (mandatory)
- Location: `docs/src/`

## Report Format (Typst)

- Main file: `docs/lab.typ`
- Template: `docs/demo.typ`
- Import: `#import "lib/gost.typ": *`
- Init: `#show: init`
- Code: `raw(read("src/main.cpp"), lang: "cpp", block: true)`
- Images: Leave commented, user adds manually

## PDF Extraction

```
pdftotext -layout "filename.pdf" -
```

## Workflow

1. **Verificator** → Extract task from PDF
2. **Coder** → Implement in `docs/src/`
3. **QA** → Test and validate
4. **Writer** → Create `docs/lab.typ`
5. **Build** → `typst compile docs/lab.typ docs/lab.pdf`
