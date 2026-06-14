#include "app.hpp"
#include <ftxui/dom/elements.hpp>
#include <fstream>

using namespace ftxui;

App::App(AppState& state, std::function<void()> on_quit) : state(state), on_quit(on_quit) {
    auto top_menu = Menu(&top_menu_entries, &top_menu_selected, MenuOption::HorizontalAnimated());

    auto main_text_input = Input(&this->state.main_text_content, "Type your text here...");

    auto filename_input = Input(&this->state.save_filename, "filename.txt");

    MenuOption file_option;
    file_option.on_enter = [this] {
        if (file_selected == 0) { show_save_modal = true; }
        else if (file_selected == 1) { this->on_quit(); }
    };
    auto file_menu = Menu(&file_entries, &file_selected, file_option);

    MenuOption edit_option;
    edit_option.on_enter = [this] {
        if (edit_selected == 0) { clipboard = this->state.main_text_content; }
        else if (edit_selected == 1) { this->state.main_text_content += clipboard; }
    };
    auto edit_menu = Menu(&edit_entries, &edit_selected, edit_option);

    MenuOption help_option;
    help_option.on_enter = [this] {
        if (help_selected == 0) { show_version_modal = true; }
    };
    auto help_menu = Menu(&help_entries, &help_selected, help_option);

    auto tab_container = Container::Tab({file_menu, edit_menu, help_menu}, &top_menu_selected);
    
    auto main_container = Container::Vertical({
        top_menu,
        tab_container,
        main_text_input
    });

    auto main_renderer = Renderer(main_container, [this, top_menu, tab_container, main_text_input] {
        return vbox({
            top_menu->Render(),
            separator(),
            tab_container->Render(),
            separator(),
            main_text_input->Render() | flex,
        }) | border;
    });

    auto version_close_button = Button("Close", [this] { show_version_modal = false; });
    auto version_modal = Renderer(version_close_button, [this, version_close_button] {
        return vbox({
            text("Version 1.0") | center,
            separator(),
            version_close_button->Render() | center,
        }) | size(WIDTH, GREATER_THAN, 30) | border | clear_under | center;
    });

    auto save_button = Button("Save", [this] {
        std::ofstream file(this->state.save_filename);
        if (file.is_open()) {
            file << this->state.main_text_content;
            file.close();
        }
        show_save_modal = false;
    });
    auto save_cancel_button = Button("Cancel", [this] { show_save_modal = false; });
    auto save_buttons_container = Container::Horizontal({save_button, save_cancel_button});
    auto save_modal_container = Container::Vertical({filename_input, save_buttons_container});
    
    auto save_modal = Renderer(save_modal_container, [this, filename_input, save_button, save_cancel_button] {
        return vbox({
            text("Enter filename:") | center,
            separator(),
            filename_input->Render(),
            separator(),
            hbox({
                save_button->Render(),
                text("  "),
                save_cancel_button->Render(),
            }) | center,
        }) | size(WIDTH, GREATER_THAN, 40) | border | clear_under | center;
    });

    auto combined = Modal(main_renderer, version_modal, &show_version_modal);
    component = Modal(combined, save_modal, &show_save_modal);
}

ftxui::Component App::GetComponent() {
    return component;
}
