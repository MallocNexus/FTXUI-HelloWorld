#include "app.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>
#include <fstream>
using namespace ftxui;

App::App(AppState& state, std::function<void()> on_quit) : state(state), on_quit(on_quit) {
    auto top_menu = Menu(&top_menu_entries, &top_menu_selected, MenuOption::HorizontalAnimated());

    InputOption main_input_option = InputOption::Default();
    main_input_option.content = &this->state.main_text_content;
    main_input_option.placeholder = "Type your text here...";
    main_input_option.cursor_position = &this->state.main_cursor_position;
    main_input_option.transform = [](InputState state) {
        if (state.is_placeholder) {
            state.element |= dim;
        }
        if (state.focused) {
            state.element |= color(Color::Green);
        } else {
            state.element |= color(Color::White);
        }
        return state.element;
    };
    auto main_text_input_base = Input(main_input_option);
    auto main_text_input = CatchEvent(main_text_input_base, [this](Event event) {
        bool is_start_of_line = (event == Event::Home || event == Event::ArrowLeftCtrl || event == Event::CtrlA || event == Event::Special("\x1b[1;9D") || event == Event::Special("\x1b[1;3D"));
        bool is_end_of_line = (event == Event::End || event == Event::ArrowRightCtrl || event == Event::CtrlE || event == Event::Special("\x1b[1;9C") || event == Event::Special("\x1b[1;3C"));

        if (is_start_of_line) {
            int& pos = this->state.main_cursor_position;
            const std::string& text = this->state.main_text_content;
            int start = pos - 1;
            while (start >= 0 && text[start] != '\n') {
                start--;
            }
            pos = start + 1;
            return true;
        }

        if (is_end_of_line) {
            int& pos = this->state.main_cursor_position;
            const std::string& text = this->state.main_text_content;
            int end = pos;
            while (end < (int)text.size() && text[end] != '\n') {
                end++;
            }
            pos = end;
            return true;
        }

        return false;
    });

    auto filename_input = Input(&this->state.save_filename, "filename.txt");

    MenuOption file_option = MenuOption::HorizontalAnimated();
    file_option.on_enter = [this] {
        if (file_selected == FILE_SAVE) { show_save_modal = true; }
        else if (file_selected == FILE_QUIT) { this->on_quit(); }
    };
    auto file_menu = Menu(&file_entries, &file_selected, file_option);

    MenuOption edit_option = MenuOption::HorizontalAnimated();
    edit_option.on_enter = [this] {
        if (edit_selected == EDIT_COPY) { clipboard = this->state.main_text_content; }
        else if (edit_selected == EDIT_PASTE) { this->state.main_text_content += clipboard; }
    };
    auto edit_menu = Menu(&edit_entries, &edit_selected, edit_option);

    MenuOption help_option = MenuOption::HorizontalAnimated();
    help_option.on_enter = [this] {
        if (help_selected == HELP_VERSION) { show_version_modal = true; }
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
