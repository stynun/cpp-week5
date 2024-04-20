#include "game.h"
#include "console/console.h"
#include <iostream>

void Game::printLines() {
    std::string str_lines = std::to_string(left_lines);
    str_lines.append(" lines left");
    console::draw(0, BOARD_HEIGHT + 2, str_lines);
}

std::string Game::getPlaytime(int time) {
    int m, s, ss;
    ss = time % 100;
    time /= 100;
    s = time % 60;
    time /= 60;
    m = time;

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
    return str_playtime;
}

void Game::printWin() {
    console::clear();
    draw();
    console::draw(BOARD_WIDTH / 2 - 2, BOARD_HEIGHT / 2, "You Win");
    console::draw(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT / 2 + 1, getPlaytime(playtime));
    console::wait();
}

void Game::subLines() {
    left_lines--;
}

void Game::update() {
    playtime++;
    timer++;
}

void Game::draw() {
    console::draw(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT + 3, getPlaytime(playtime));
    console::drawBox(0, 0, BOARD_WIDTH + 1, BOARD_HEIGHT + 1);
    printLines();

    if (timer == DROP_DELAY) {
        timer = 0;
    } 
}

bool Game::shouldExit() {
    if (console::key(console::K_UP)) {
        subLines();
    }
    if (console::key(console::K_ESC)) {
            return true;
    }
    if (left_lines <= 0) {
        printWin();
        return true;
    }

    return false;
}

Game::Game() {
    timer = 0;
    left_lines = LINES;
    playtime = 0;
}