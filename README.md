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

## 🚀 About

**ToolCL** is a lightweight framework written in **C**, focused on providing simple and reusable components for application development.

The project is designed to remain small, portable, modular, and easy to understand.

## ✨ Features

- ⚡ Lightweight architecture
- 🧩 Modular structure
- 🔧 Written in pure C
- 📐 C99 standard
- 🌍 Cross-platform design
- 📦 Minimal dependencies
- 📚 Reusable components
- 🏗️ Static library support

## 💡 Philosophy

ToolCL follows a simple principle:

> **Keep it small, keep it portable, keep it simple.**

The goal is to provide useful building blocks without unnecessary complexity.

## 🧩 Main Modules

- Logger
- Math utilities
- Vec2
- String

> [!NOTE]
> New modules may be introduced in future versions.

## 🧪 Examples

ToolCL currently includes:

- `hello_logger`
- `hello_math`
- `hello_vec2`
- `hello_string`
- `hello_world`
- `hello_random`

## 🔧 Build System

ToolCL uses **CMake** as its official build system.

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Disable Examples

```bash
cmake -DTOOLCL_BUILD_EXAMPLES=OFF ..
cmake --build .
```

> [!TIP]
> Disabling examples can be useful when ToolCL is being built only as a library.

## 📁 Project Structure

```text
ToolCL/
├── include/
│   └── toolcl/
├── src/
├── examples/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

## 🌍 Platforms

- 🐧 Linux
- 🪟 Windows — Coming Soon
- 🌎 Other platforms — depending on the environment

## 🏢 ToolGits

ToolCL is maintained by the **ToolGits** organization.

- Organization: https://github.com/ToolGits
- Creator: https://github.com/enzobobdevvideos04-ctrl
- Discord: https://discord.gg/NJY5BaxMZq

## 📜 License

ToolCL is licensed under the **MIT License**.

See [`LICENSE`](LICENSE) for the full license text.

---

<p align="center">
  <strong>ToolCL — Keep it small, keep it portable, keep it simple. ⚙️</strong>
</p>