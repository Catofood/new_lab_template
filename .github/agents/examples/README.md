# Code Examples for Agents

This directory contains code templates referenced by instruction files.

## C++ Examples

| File | Purpose |
|------|---------|
| **cpp-opengl-template.cpp** | Complete Windows OpenGL application template with WinMain |
| **cpp-test-template.cpp** | Test template for C++ with Windows API |
| **cpp-class-template.cpp** | Class declaration example with Russian comments |

## C# Examples

| File | Purpose |
|------|---------|
| **csharp-class-template.cs** | Class with validation and XML documentation in Russian |
| **csharp-record-template.cs** | Record type with calculated property |

## Usage

Instructions in `.github/agents/instructions/` reference these files instead of duplicating large code blocks.

**Example reference in instructions:**
```markdown
**Complete template**: see [examples/cpp-opengl-template.cpp](../examples/cpp-opengl-template.cpp)
```

## Rules

- All examples MUST contain comments in Russian
- All messages and output in Russian
- Examples should be complete and functional
- Do NOT modify existing examples without updating references in instructions
