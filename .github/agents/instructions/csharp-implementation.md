---
description: 'C# implementation guidelines for lab assignments with .NET build system'
applyTo: 'docs/src/*.cs, docs/src/*.csproj'
---

# C# Implementation Guidelines

## Project Context

- **Language**: C# 12+ (.NET 8 LTS)
- **Build**: .NET CLI / MSBuild
- **Location**: All project files in `docs/src/`

## Best Practices

- Enable nullable reference types: `<Nullable>enable</Nullable>`
- Use pattern matching and modern C# features
- Validate parameters with `ArgumentNullException.ThrowIfNull`
- Throw specific exceptions: `ArgumentException`, `InvalidOperationException`

## Code Standards

**Naming:**
- Classes/Methods/Properties: `PascalCase`
- Local variables/parameters: `camelCase`
- Private fields: `_camelCase`
- Interfaces: `I` + `PascalCase`

**Formatting:**
- Indentation: 4 spaces
- Braces: Allman style (new line)
- Line length: under 120 characters

**Comments:** See examples in `.github/agents/examples/csharp-class-template.cs`

## Build System (.NET)

**Project file (Lab.csproj):**
```xml
<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net8.0</TargetFramework>
    <Nullable>enable</Nullable>
    <ImplicitUsings>enable</ImplicitUsings>
  </PropertyGroup>
</Project>
```

**Build commands:**
```bash
dotnet build docs/src/Lab.csproj -c Release
dotnet run --project docs/src/Lab.csproj -c Release
dotnet test tests/Tests.csproj -c Release
```

## Modern C# Features

- File-scoped namespaces: `namespace Lab;`
- Top-level statements in Program.cs
- Record types: `record Person(string Name, int Age);`
- Init properties: `public int Value { get; init; }`
- Pattern matching: `if (obj is MyClass { Value: > 0 })`

## Standard Library

- Dynamic arrays: `List<T>`
- Key-value pairs: `Dictionary<TKey, TValue>`
- Sets: `HashSet<T>`
- String building: `StringBuilder`
- File I/O: `System.IO.File`, `StreamReader`

## Report Integration

Reference code in Typst reports:

```typst
#figure(
  raw(read("src/Program.cs"), lang: "csharp", block: true),
  caption: [Source file Program.cs],
) <file-program>
```
