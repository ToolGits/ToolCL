# ToolCL

ToolCL is a lightweight framework written in C, focused on simplicity, portability, and modular development.

The project provides a small collection of reusable components for building applications without unnecessary complexity.

## Official Maintainer

ToolCL is maintained by the **ToolGits** organization:

- ToolGits: https://github.com/ToolGits
- Created by: https://github.com/enzobobdevvideos04-ctrl
- Discord server: https://discord.gg/NJY5BaxMZq (ToolGits SV)

## Features

- Lightweight architecture
- Written in pure C
- C99 standard
- Cross-platform design
- Modular structure
- Minimal dependencies
- Static library support

## Philosophy

ToolCL follows a simple principle:

> Keep it small, keep it portable, keep it simple.

The goal is to provide useful building blocks while remaining easy to understand and maintain.

## Main Modules

- Logger
- Math utilities
- Vec2
- String

New modules may be introduced in future versions.

## Examples

ToolCL currently includes the following examples:

- `hello_logger`
- `hello_math`
- `hello_vec2`
- `hello_string`
- `hello_world`
- `hello_random`

## Build System

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

## Project Structure

```text
ToolCL/
├── include/
├── src/
├── examples/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

## Platforms

- Linux
- Windows (Coming Soon)
- Cross-platform support depending on the environment

## License

MIT License