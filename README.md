# TextUI Editor

A highly testable, minimal text editor interface built in C++ using [FTXUI](https://github.com/ArthurSonzogni/FTXUI).

## Overview

This project serves as a foundational scaffold for building terminal-based user interfaces. It demonstrates how to decouple the core FTXUI component tree from the blocking `ScreenInteractive::Loop` to enable deep, headless integration testing.

### Features
* **Horizontal Top Menus:** Seamlessly navigate between File, Edit, and Help tabs.
* **Modals:** Includes interactive popup dialogs for saving files and viewing version details.
* **Clipboard Simulation:** Demonstrates local state mutation with functional "Copy" and "Paste" actions within a text area.
* **100% Testable Architecture:** The UI is wrapped in an `App` class, allowing an automated Catch2 test runner to simulate keyboard events (`ArrowRight`, `Tab`, `Return`) and assert layout state changes without launching the terminal.

## Requirements

* C++17 Compatible Compiler (e.g., Apple Clang, GCC, Clang)
* CMake >= 3.14
* Ninja (Optional, but recommended)

*Note: Both FTXUI and Catch2 are automatically fetched via CMake `FetchContent`.*

## Build Instructions

To build the project natively using CMake:

```bash
mkdir build && cd build
cmake .. -G Ninja
cmake --build .
```

## Running the App

After compiling, run the executable to launch the text editor UI:

```bash
./hello_world
```

## Running Tests

This project includes an integration test suite built with **Catch2 v3**. The tests autonomously navigate the UI components and assert behaviors (like copying text or saving files to disk).

To execute the tests:

```bash
./run_tests
```

## Appendix

### Ninja

Ninja is used as the primary build system generator for this project because it is designed for maximum speed. Unlike traditional Makefiles, Ninja evaluates dependencies almost instantly and efficiently parallelizes the compilation process. For a modern C++ project that pulls in external libraries like FTXUI and Catch2, using Ninja significantly reduces both the initial setup time and incremental recompilation times, resulting in a much smoother and faster development experience.

### FTXUI

[FTXUI](https://github.com/ArthurSonzogni/FTXUI) (Functional Terminal (X) User Interface) is a modern, cross-platform C++ library for building terminal-based user interfaces. It provides a highly declarative and functional approach to defining UI layouts. In this project, FTXUI powers the entire visual interface—handling the rendering of menus, input areas, and modals, as well as smoothly managing keyboard navigation and terminal escape sequences.

### Catch2

[Catch2](https://github.com/catchorg/Catch2) is a popular, modern, and macro-free C++ testing framework. It is designed to be extremely easy to use, allowing developers to write tests with natural, expressive assertions. For this project, Catch2 drives our integration tests. It allows us to instantiate the UI components headlessly, simulate user keyboard events, and verify that the underlying application state responds correctly.
