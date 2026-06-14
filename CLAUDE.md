# Project Instructions for AI Agents

## Tech Stack
* Language: C++17
* UI Framework: FTXUI (Functional Terminal (X) User Interface)
* Testing Framework: Catch2 v3
* Build System: CMake (with Ninja generator recommended)

## Important Commands
* **Configure:** `cmake -S . -B build -G Ninja`
* **Build:** `cmake --build build` (or use `Shift-Cmd-B` in VS Code)
* **Run Tests:** `./build/run_tests`
* **Run App:** `./build/hello_world`

## Architecture Notes
* The main UI application logic is encapsulated inside the `App` class in `app.hpp` and `app.cpp`.
* The submenus (File, Edit, Help) are configured as **Horizontal Animated** menus. To simulate user navigation in tests, use `Event::ArrowRight` and `Event::ArrowLeft` when focus is inside a submenu.
* The main text input field has a custom `InputOption` transform that captures `Cmd+Left` and `Cmd+Right` equivalents to navigate to the start and end of the current line.

## General Guidelines
* When adding new menu items, update the `MenuIndex` enum in `app.hpp` to prevent hardcoded indices.
* The Google C++ Style Guide MUST be used to rate code format quality. Reference: https://google.github.io/styleguide/cppguide.html. **Exception:** We use 4 spaces for indentation instead of 2.
* Skills are available in the `.claude/skills` folder.
