#include "game.h"
#include "tetromino.h"
#include "console/console.h"
#include <iostream>

Tetromino I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino O("0", 2, "OOOO");
Tetromino T("T", 3, "XOXOOOXXX");
Tetromino S("S", 3, "XOOOOXXXX");
Tetromino Z("Z", 3, "OOXXOOXXX");
Tetromino J("J", 3, "OXXOOOXXX");
Tetromino L("L", 3, "XXOOOOXXX");
Tetromino currentTetromino = I;

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

void Game::handleInput() {
    if (console::key(console::K_LEFT)) {
        x--;
    }
    if (console::key(console::K_RIGHT)) {
        x++;
    }
    if (console::key(console::K_UP)) {
        y++;
    }
    if (console::key(console::K_DOWN)) {
        y++;
    }
    if (console::key(console::K_Z)) {
        currentTetromino = currentTetromino.rotatedCCW();
        for (int x = 0; x < currentTetromino.size(); x++) {
            for (int y = 0; y < currentTetromino.size(); y--) {
                if (currentTetromino.check(x, y)) {
                    std::cout << "O";
                }
                else {
                    std::cout << "X";
                }
            }
        }
        std::cout << std::endl;
    }
    if (console::key(console::K_X)) {
        currentTetromino = currentTetromino.rotatedCW();
    }
}

void Game::update() {
    playtime++;
    timer++;
    handleInput();

    if (timer == DROP_DELAY) {
        timer = 0;
        y++;
    } 
}

void Game::draw() {
    console::drawBox(0, 0, BOARD_WIDTH + 1, BOARD_HEIGHT + 1);
    console::draw(BOARD_WIDTH / 2 - 3, BOARD_HEIGHT + 3, getPlaytime(playtime));
    printLines();

    console::drawBox(BOARD_WIDTH + 3, 0, BOARD_WIDTH + 8, 5);
    console::draw(BOARD_WIDTH + 4, 0, "Next");
    console::drawBox(BOARD_WIDTH + 9, 0, BOARD_WIDTH + 14, 5);
    console::draw(BOARD_WIDTH + 10, 0, "Hold");

    currentTetromino.drawAt(BLOCK_STRING, x, y);
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
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board_[i][j] = false;
        }
    }

    timer = 0;
    left_lines = LINES;
    playtime = 0;
    x = 5;
    y = 1;

    currentTetromino = I;
}