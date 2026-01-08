---
description: 'Common rules for all lab work agents'
applyTo: '.github/agents/**/*.agent.md'
---

# Common Instructions for All Agents

These instructions apply to all agents in the lab work development system.

## Language and Localization

### CRITICAL REQUIREMENTS

**1. Comments ONLY in Russian:**
- Each function MUST have a comment describing its purpose
- Complex logic must be commented step by step
- Non-obvious variables must have explanations

**2. All messages ONLY in Russian:**
- Console output, error messages, input prompts
- Window titles, button labels
- Exceptions: `throw new Exception("Description in Russian");`

**3. Documentation files (.md) in ENGLISH ONLY:**
- All `.agent.md` files MUST be written in English
- All `.instructions.md` files MUST be written in English
- README.md files in `.github/agents/` MUST be in English
- This ensures compatibility with GitHub Copilot and international teams

**EXCEPTION:** English in code is allowed ONLY when explicitly specified in the assignment.

Code examples: see `.github/agents/examples/`

## Prohibition of Unnecessary Files

### File Management Rules

**STRICTLY FORBIDDEN to create:**
- ❌ summary.md, work-report.md, progress.md
- ❌ TEST_REPORT.md, TEST_CASES.md
- ❌ verification-report.md, task-analysis.md
- ❌ workflow.md, orchestration-logs.md
- ❌ changelog.md, changes.md
- ❌ Any other .md files with work reports

**ALLOWED to create only:**
- ✅ Source code: `docs/src/*.cpp`, `docs/src/*.cs`
- ✅ Tests: `tests/test_*.cpp`, `tests/CMakeLists.txt`
- ✅ Report: `docs/lab.typ`, `docs/lab.pdf`
- ✅ Configuration: `CMakeLists.txt`, `*.csproj`

### Communication Principle

- Report work results **in chat** (1-3 sentences)
- Pass context to other agents **via handoff messages**
- DO NOT create intermediate files for information exchange

## Project Structure

```
project/
├── docs/
│   ├── demo.typ                 # Template (DO NOT MODIFY)
│   ├── lab.typ                  # Report (created by Writer)
│   ├── lib/                     # GOST formatting
│   ├── images/                  # Screenshots
│   └── src/                     # Source code (Coder)
├── tests/                       # Tests (QA)
├── build/                       # Build artifacts
└── CMakeLists.txt               # C++ projects only
```

## Programming Language Selection

### ONE LANGUAGE PER PROJECT Rule

**CRITICALLY IMPORTANT:** Only ONE language is used per project.

1. Check if language is specified in methodology or assignment
2. If not specified — ask the user
3. Default: C++
4. ❌ NEVER mix C++ and C# in one project

### Language-Specific Instructions

When selecting a language, agent MUST read the corresponding file:
- C++: `.github/agents/instructions/cpp-implementation.md`
- C#: `.github/agents/instructions/csharp-implementation.md`

## Build and Test Commands

**C++:**
```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release
.\build\Release\lab.exe
ctest --test-dir build -C Release --output-on-failure
```

**C#:**
```bash
dotnet build docs/src/Lab.csproj -c Release
dotnet run --project docs/src/Lab.csproj -c Release
dotnet test tests/Tests.csproj -c Release
```

**Typst:**
```bash
typst compile docs/lab.typ docs/lab.pdf
```

## Communication Style

- **Brevity**: 1-3 sentences for reporting
- **Specificity**: List created files with paths
- **No .md files**: Communicate in chat
- **Handoff**: Immediately after completing work

## Division of Responsibility

- **Orchestrator**: Workflow coordination
- **Verificator**: Requirements analysis from PDF
- **Coder**: Write code in `docs/src/`
- **QA**: Create tests in `tests/`
- **Writer**: Create `docs/lab.typ`

Each agent does ONLY its work. Transfer control via handoff when needed.

## Error Handling

1. Report problem in chat (brief description)
2. Pass context via handoff to responsible agent
3. DO NOT create error-report.md or similar files

## Quality Control

**Before handoff, verify:**
- ✅ All files in correct directories
- ✅ Code compiled without errors (Coder)
- ✅ All tests passed (QA)
- ✅ PDF generated (Writer)
- ✅ NO extra .md files created
- ✅ Comments and output in Russian

## Examples of Correct Work

**Coder → QA:**
```
Implemented OpenGL program.
docs/src/main.cpp - 191 lines
CMakeLists.txt - build configured
```

**QA → Writer:**
```
All tests passed (5/5 - 100%)

| Test | Status |
|------|--------|
| Executable exists | ✅ PASS |
| Program launches | ✅ PASS |
```

