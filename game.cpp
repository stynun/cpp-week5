#include "game.h"
#include "console/console.h"

void Game::printLines() {
    std::string str_lines = std::to_string(left_lines);
    str_lines.append(" lines left");
    console::draw(0, BOARD_HEIGHT + 2, str_lines);
}

void Game::printPlaytime() {
    int m, s, ss;
    ss = playtime % 100;
    playtime /= 100;
    s = playtime % 60;
    playtime /= 60;
    m = playtime;

    std::string str_m = std::to_string(m);
    std::string str_s = std::to_string(s);
    std::string str_ss = std::to_string(ss);

    if (m < 10) {
        str_m.insert(0, "0");
    }
    if (s < 10) {
        str_s.insert(0, "0");
    }
    if (ss < 10) {
        str_ss.insert(0, "0");
    }

    std::string str_playtime = str_m + ":" + str_s + "." + str_ss; 
    console::draw(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT + 3, str_playtime);
}

void Game::draw() {
    console::drawBox(0, 0, BOARD_WIDTH + 1, BOARD_HEIGHT + 1);
    printLines();
      
}

void Game::update() {
    playtime++;
    timer++;
    printPlaytime();
    if (timer == DROP_DELAY) {
        timer = 0;

        draw();
    }
}

bool Game::shouldExit() {
    if (console::key(console::K_ESC)) {
            return true;
    }
    else {
        return false;
    }
}

Game::Game() {
    timer = 0;
    left_lines = LINES;
    playtime = 0;
}