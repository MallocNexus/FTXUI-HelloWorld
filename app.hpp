#pragma once
#include <ftxui/component/component.hpp>
#include <string>
#include <functional>

struct AppState {
    std::string main_text_content;
    std::string save_filename = "filename.txt";
    int main_cursor_position = 0;
};

enum MenuIndex {
    FILE_QUIT = 0,
    FILE_SAVE = 1,
    EDIT_COPY = 0,
    EDIT_PASTE = 1,
    HELP_VERSION = 0
};

class App {
public:
    App(AppState& state, std::function<void()> on_quit);
    ftxui::Component GetComponent();

private:
    AppState& state;
    std::function<void()> on_quit;

    std::vector<std::string> top_menu_entries = {"File", "Edit", "Help"};
    int top_menu_selected = 0;

    std::vector<std::string> file_entries = {"Quit", "Save"};
    int file_selected = 0;

    std::vector<std::string> edit_entries = {"Copy", "Paste"};
    int edit_selected = 0;
    std::string clipboard = "";

    std::vector<std::string> help_entries = {"Version"};
    int help_selected = 0;

    bool show_version_modal = false;
    bool show_save_modal = false;

    ftxui::Component component;
};
