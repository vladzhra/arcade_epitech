/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-charles.fassel-ashley
** File description:
** arcade_ncurses
*/

#include "arcade_ncurses.hpp"

NcursesModule::NcursesModule() {
    _key = -1;
    initscr();
    clear();
    noecho();
    keypad(stdscr, TRUE);
    timeout(0);
}

NcursesModule::~NcursesModule() {
    endwin();
}

void NcursesModule::display(const std::vector<std::string>& game_map, const std::string &score) {
    int screen_rows, screen_cols;
    getmaxyx(stdscr, screen_rows, screen_cols);
    int start_row = (screen_rows - game_map.size()) / 2;
    int start_col = (screen_cols - game_map[0].size()) / 2;

    mvprintw(0, 0, "Score: %s", score.c_str());
    displayGraphicName();
    for (size_t row = 0; row < game_map.size(); ++row) {
        for (size_t col = 0; col < game_map[row].size(); ++col) {
            mvprintw(start_row + row, start_col + col, "%c", (game_map[row][col]));
        }
    }
    refresh();
    _key = getch();
    if (_key == ERR) {
        _key = -1;
    }
}

void NcursesModule::displayGameName(std::string name)
{
    mvprintw(2, 0, name.c_str());
}

void NcursesModule::displayGraphicName()
{
    mvprintw(1, 0, getName().c_str());
}

void NcursesModule::run(void)
{
    handle_events();
}

std::string NcursesModule::handle_events() {
    if (_key == KEY_RIGHT)
        return "RIGHT";
    if (_key == KEY_LEFT)
        return "LEFT";
    if (_key == KEY_UP)
        return "UP";
    if (_key == KEY_DOWN)
        return "DOWN";
    if (_key == 32)
        return "SPACE";
    if (_key == 108)
        return "L";
    if (_key == 27) {
        endwin();
        return "ESCAPE";
    }
    if (_key == 10)
        return "ENTER";
    if (_key == 103)
        return "G";
    if (_key == 114)
        return "R";
    return "";
}

void NcursesModule::updateTexture(const std::string& direction) {
    (void)direction;
}

void NcursesModule::drawMenu(const std::vector<std::string>& gameNames, int selectedIndex) {
    int menuWidth = 30;
    int menuHeight = gameNames.size() + 2;
    int menuStartY = (LINES - menuHeight) / 2;
    int menuStartX = (COLS - menuWidth) / 2;

    box(stdscr, 0, 0);

    for (size_t i = 0; i < gameNames.size(); ++i) {
        int itemY = menuStartY + i + 1;
        int itemX = menuStartX + (menuWidth - gameNames[i].length()) / 2;
        if (i == static_cast<size_t>(selectedIndex)) {
            attron(A_REVERSE);
            for (size_t j = 0; j < gameNames[i].length(); ++j) {
                mvprintw(itemY, itemX + j, "%c", (gameNames[i][j]));
            }
            attroff(A_REVERSE);
        } else {
            for (size_t j = 0; j < gameNames[i].length(); ++j) {
                mvprintw(itemY, itemX + j, "%c", (gameNames[i][j]));
            }
        }
    }

    refresh();
    _key = getch();
}
