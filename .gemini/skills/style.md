<skill>
  <description>
    When the user invokes `/style`, perform a comprehensive review of all `.cpp` and `.hpp` files in the workspace.
  </description>

  <instructions>
    <step>Find all `.cpp` and `.hpp` files in the workspace (excluding external libraries like `_deps`).</step>
    <step>Evaluate their formatting and style strictly against the Google C++ Style Guide.</step>
    <step>Point out any deviations (e.g., naming conventions, bracket placements, missing headers, or spacing issues). Present them using the exact format shown in the `example_output` section below.</step>
    <step>Provide a per-file rating table and an overall assessment, following the format in `example_output`.</step>
    <step>Save the final report in markdown format in the `review/style/` directory, using the current date and time in the file name (e.g., `review/style/style_report_YYYY-MM-DD_HH-MM-SS.md`). Create the directory if it does not exist.</step>
  </instructions>

  <critical_rules>
    <rule>EXCEPTION TO GOOGLE STYLE: You MUST ensure that exactly 4 spaces are used for indentation instead of Google's default 2 spaces. If a file uses 2 spaces, flag it as a formatting error.</rule>
    <rule>The output format MUST exactly match the structure shown in `example_output` — including the header block, Issues Found table (with File, Line(s), Issue Description, Corrected Snippet columns), Per-File Ratings table, and Overall Assessment section with emoji bullet points.</rule>
  </critical_rules>

  <example_output>
# C++ Style Review Report

**Date:** YYYY-MM-DD HH:MM:SS
**Standard:** Google C++ Style Guide (exception: 4-space indentation)
**Files reviewed:**
- `app.hpp`
- `app.cpp`
- `main.cpp`
- `test_main.cpp`

---

## Issues Found

| File | Line(s) | Issue Description | Corrected Snippet |
|------|---------|-------------------|-------------------|
| `app.cpp` | 6 | **`using namespace` in global scope.** Google Style strongly discourages `using namespace` at file scope. It pollutes the namespace and hides symbol origins. Use explicit `ftxui::` prefixes or scope the `using` inside functions. | Remove: `using namespace ftxui;` — use explicit `ftxui::` prefixes or scope it inside functions. |
| `app.cpp` | 17 | **Lambda parameter shadows member variable.** The lambda parameter `state` shadows the `App` member `state_`. Google Style warns against shadowing; rename the parameter. | `[](InputState input_state) { if (input_state.is_placeholder) { ...` |
| `app.cpp` | 55 | **C-style cast `(int)`.** Google Style requires C++ casts. Replace `(int)text.size()` with `static_cast<int>(text.size())`. | `while (end < static_cast<int>(text.size()) && text[end] != '\n') {` |
| `app.hpp` | 1 | **`#pragma once` vs. `#ifndef` guard.** Google Style historically specifies `#define` include guards. `#pragma once` is a non-standard compiler extension. This is advisory — many modern Google projects accept it. | `#ifndef FTXUI_HELLOWORLD_APP_HPP_` / `#define FTXUI_HELLOWORLD_APP_HPP_` / `#endif // FTXUI_HELLOWORLD_APP_HPP_` |
| `app.hpp` | 37 | **Redundant empty-string initialiser.** `std::string clipboard = ""` is redundant — `std::string` default-constructs to empty. | `std::string clipboard;` |
| `main.cpp` | 5 | **`main(void)` C idiom.** Modern C++ and Google Style prefer `int main()` over `int main(void)`. | `int main() {` |
| `test_main.cpp` | 1–6 | **Include order violates Google Style.** Google Style requires: related `.h` first, then C system headers, then C++ standard library, then third-party library headers. Catch2 should come after `"app.hpp"`. | `#include "app.hpp"` then `#include <catch2/catch_test_macros.hpp>` then FTXUI headers then `<filesystem>` / `<fstream>` |
| `test_main.cpp` | 70 | **Trailing whitespace.** Line 70 has trailing whitespace after the statement. | Remove trailing whitespace. |

---

## Per-File Ratings

| File | Rating | Notes |
|------|--------|-------|
| `app.hpp` | ⭐⭐⭐⭐ (4/5) | Very clean. Minor: `#pragma once` vs include guard, redundant `= ""` initialiser. |
| `app.cpp` | ⭐⭐⭐ (3/5) | Good structure. Three issues: `using namespace` at file scope, lambda parameter shadowing, C-style cast. |
| `main.cpp` | ⭐⭐⭐⭐ (4/5) | Tiny and clean. Only `main(void)` idiom to address. |
| `test_main.cpp` | ⭐⭐⭐⭐ (4/5) | Well-structured tests. Include order and trailing whitespace need attention. |

---

## Overall Assessment

The codebase is **well-written and largely conforms** to the Google C++ Style Guide.

- ✅ Indentation consistently uses **4 spaces** as required by the project exception.
- ✅ `MenuIndex` enum is used correctly — no hardcoded indices found.
- ✅ Naming conventions are consistent and clear.
- ⚠️ Most impactful fix: remove **`using namespace ftxui`** at file scope in `app.cpp`.
- ⚠️ Replace the C-style cast with `static_cast<int>`.
- ℹ️ Remaining issues are minor polish items.

**Overall Style Rating: ⭐⭐⭐⭐ (4/5) — Good, with a few targeted fixes needed.**
  </example_output>
</skill>
