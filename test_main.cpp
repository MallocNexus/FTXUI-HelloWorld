#include <catch2/catch_test_macros.hpp>
#include "app.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <fstream>
#include <filesystem>

using namespace ftxui;

TEST_CASE("Main Application Flow", "[app]") {
    AppState state;
    bool quit_called = false;
    App app(state, [&] { quit_called = true; });
    auto comp = app.GetComponent();

    SECTION("Type text, Copy, Paste") {
        state.main_text_content = "Hello";

        // Start at top menu. Move right to "Edit"
        comp->OnEvent(Event::ArrowRight);

        // Move down to Edit sub-menu. "Copy" is focused.
        comp->OnEvent(Event::ArrowDown);

        // Trigger "Copy"
        comp->OnEvent(Event::Return);

        // Move down to "Paste"
        comp->OnEvent(Event::ArrowDown);

        // Trigger "Paste"
        comp->OnEvent(Event::Return);

        // Verify paste appended text
        REQUIRE(state.main_text_content == "HelloHello");
    }

    SECTION("Save and Quit") {
        state.main_text_content = "Test File Content";
        state.save_filename = "test.txt";

        // Start at top menu ("File"). Move down to File sub-menu. "Save" is focused.
        comp->OnEvent(Event::ArrowDown);

        // Trigger "Save" to open modal
        comp->OnEvent(Event::Return);

        // Inside modal, focus is on filename Input. Move to "Save" button using Tab.
        comp->OnEvent(Event::Tab);

        // Focus is on "Save" button. Trigger it.
        comp->OnEvent(Event::Return);

        // Verify file is saved
        std::ifstream file("test.txt");
        REQUIRE(file.is_open());
        std::string content;
        std::getline(file, content);
        REQUIRE(content == "Test File Content");
        file.close();

        // Modal closed, focus is back on "Save". Move down to "Quit".
        comp->OnEvent(Event::ArrowDown);

        // Trigger "Quit"
        comp->OnEvent(Event::Return);
        
        REQUIRE(quit_called == true);
    }
}
