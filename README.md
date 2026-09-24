# ToolCL ⚙️

[![Status](https://img.shields.io/badge/status-Stable-brightgreen)](https://github.com/ToolGits/ToolCL)
[![Version](https://img.shields.io/badge/version-0.3.0-blue)](https://github.com/ToolGits/ToolCL)
[![Language](https://img.shields.io/badge/language-C-blue)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Standard](https://img.shields.io/badge/standard-C99-orange)](https://en.wikipedia.org/wiki/C99)
[![Build](https://img.shields.io/badge/build-CMake-064F8C)](https://cmake.org/)
[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)

> A lightweight C framework focused on simplicity, portability, and modular development.

> [!IMPORTANT]
> **ToolCL 0.3.0 is the current stable version.**

---

## 🚀 About

**ToolCL** is a lightweight and modular framework written in **C99**.

It provides a collection of small, reusable components intended to make common tasks easier without introducing unnecessary complexity.

The project prioritizes:

- Simple APIs
- Small and understandable components
- Portability
- Modular development
- Minimal dependencies
- Easy maintenance

ToolCL is designed to be a **framework that stays lightweight** instead of growing into an unnecessarily complex ecosystem.

---

## ✨ Features

- ⚡ Lightweight architecture
- 🧩 Modular components
- 🔧 Written in C99
- 🏗️ Static library support
- 🔨 CMake build system
- 📦 Minimal external dependencies
- 🌍 Portability-oriented design
- 📚 Reusable APIs
- 🧪 Practical examples and experiments

---

## 💡 Philosophy

ToolCL follows a simple principle:

> **Keep it small, keep it portable, keep it simple.**

The project focuses on keeping its APIs and internal structure simple, understandable, and maintainable.

ToolCL also values **compatibility and backwards compatibility**.

Whenever practical, existing APIs and behavior are preserved so that projects can continue using previous versions of the framework while newer functionality is introduced.

However, backwards compatibility is not guaranteed in every situation. Breaking changes may occasionally be necessary as ToolCL evolves.

The goal is to balance **simplicity, portability, compatibility, and continuous development**.

---

## 🧩 Modules

### Logger

Lightweight logging utilities for applications and experiments.

Provides:

- Debug logging
- Informational logging
- Warning logging
- Error logging
- Configurable log levels

### Math

Basic mathematical utilities for common operations.

Includes:

- Addition
- Subtraction
- Multiplication
- Division

Division by zero is handled deterministically by returning `0.0f`.

### Vec2

A small 2D vector module.

Provides:

- Vector creation
- Vector addition
- Vector subtraction
- Scalar multiplication
- Vector length calculation

### String

Basic utilities for working with C strings.

Provides:

- String length
- String comparison

The module also provides defined behavior for `NULL` inputs.

---

## 🧪 Examples

ToolCL includes several examples demonstrating its modules.

### Library examples

- `hello_logger` — Logger demonstration
- `hello_math` — Math utilities demonstration
- `hello_vec2` — 2D vector demonstration
- `hello_string` — String utilities demonstration

### Experimental examples

- `hello_world` — Interactive experiment focused on input and interaction
- `hello_random` — Experiment focused on randomness

The experimental examples are intentionally kept as small practical programs for testing concepts and experimenting with ToolCL.

---

## 🔧 Build System

ToolCL uses **CMake** as its official build system.

### Requirements

- A C99-compatible C compiler
- CMake 3.10 or newer

### Build

From the project root:

```bash
cmake -S . -B build
cmake --build build
```

The generated files are kept inside the `build/` directory.

The static library is generated as:

```text
build/lib/libtoolcl.a
```

Example executables are generated inside:

```text
build/bin/
```

### Build without examples

If you only need the ToolCL library:

```bash
cmake -S . -B build -DTOOLCL_BUILD_EXAMPLES=OFF
cmake --build build
```

> [!TIP]
> Disabling examples is useful when ToolCL is being integrated as a library into another project.

---

## 📦 Basic Usage

After building ToolCL, applications can include its public headers through the `toolcl/` include path.

For example:

```c
#include <toolcl/math.h>
#include <stdio.h>

int main(void)
{
    float result = toolcl_addf(10.0f, 5.0f);

    printf("Result: %.2f\n", result);

    return 0;
}
```

The exact API may grow as new ToolCL versions are released, while keeping the project focused on small and understandable interfaces.

---

## 📁 Project Structure

```text
ToolCL/
├── include/
│   └── toolcl/
│       ├── logger.h
│       ├── math.h
│       ├── string.h
│       └── vec2.h
├── src/
│   ├── logger.c
│   ├── math.c
│   ├── string.c
│   └── vec2.c
├── examples/
│   ├── hello_logger.c
│   ├── hello_math.c
│   ├── hello_random.c
│   ├── hello_string.c
│   ├── hello_vec2.c
│   └── hello_world.c
├── CMakeLists.txt
├── README.md
└── LICENSE
```

---

## 🌍 Platforms

ToolCL follows a portability-oriented design.

### Current

- 🐧 Linux

### Planned / Improving

- 🪟 Windows
- 🌎 Other compatible platforms

Platform-specific dependencies are intentionally kept to a minimum whenever possible.

---

## 🏢 ToolGits

ToolCL is maintained by the **ToolGits** organization.

ToolCL is an independent project within the ToolGits family, with its own architecture, goals, and development direction.

- Organization: https://github.com/ToolGits
- Creator: https://github.com/enzobobdevvideos04-ctrl
- Discord: https://discord.gg/NJY5BaxMZq

---

## 📜 License

ToolCL is licensed under the **MIT License**.

See [`LICENSE`](LICENSE) for the full license text.

---

<p align="center">
  <strong>ToolCL — Keep it small, keep it portable, keep it simple. ⚙️</strong>
</p>