#include "app.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>

int main(void) {
    using namespace ftxui;
    auto screen = ScreenInteractive::Fullscreen();
    AppState state;
    App app(state, [&] { screen.ExitLoopClosure()(); });

    screen.Loop(app.GetComponent());
    return EXIT_SUCCESS;
}
