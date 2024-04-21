#include "game.h"
#include "tetromino.h"
#include "console/console.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Tetromino I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino O("0", 2, "OOOO");
Tetromino T("T", 3, "XOXOOOXXX");
Tetromino S("S", 3, "XOOOOXXXX");
Tetromino Z("Z", 3, "OOXXOOXXX");
Tetromino J("J", 3, "OXXOOOXXX");
Tetromino L("L", 3, "XXOOOOXXX");

Tetromino currentTetromino = I;
Tetromino nextTetromino = I;
Tetromino holdingTetromino = I;

bool hold_empty = true;
bool is_hold = false;

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
        y = s_y;
    }
    if (console::key(console::K_DOWN)) {
        y++;
    }
    if (console::key(console::K_Z)) {
        currentTetromino = currentTetromino.rotatedCCW();
    }
    if (console::key(console::K_X)) {
        currentTetromino = currentTetromino.rotatedCW();
    }
    if (console::key(console::K_SPACE)) {
            if (hold_empty) {
                hold_empty = false;
                is_hold = true;
                holdingTetromino = *currentTetromino.original();
                currentTetromino = nextTetromino;
                makeNewTetromino(1);
            }
            if (!is_hold && !hold_empty) {
                is_hold = true;
                Tetromino temp = *currentTetromino.original();
                currentTetromino = holdingTetromino;
                holdingTetromino = temp;
            } 
        }
}

void Game::hitbox() {
    int x_min = 10;
    int x_max = 0;
    for (int i = 0; i < currentTetromino.size(); i++) {
        for (int j = 0; j < currentTetromino.size(); j++) {
            if(currentTetromino.check(i, j)) {
                if(j < x_min) {
                    x_min = j;
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < currentTetromino.size(); i++) {
        for (int j = currentTetromino.size(); j >= 0; j--) {
            if(currentTetromino.check(i, j)) {
                if(j > x_max) {
                    x_max = j;
                }
                break;
            }
        }
    }
    
    hit_x_min = x_min + x;
    hit_x_max = x_max + x;

    int y_min = 20;
    int y_max = 0;
    for (int i = 0; i < currentTetromino.size(); i++) {
        for (int j = 0; j < currentTetromino.size(); j++) {
            if(currentTetromino.check(i, j)) {
                if(i < y_min) {
                    y_min = i;
                }
                break;
            }
        }
    }
    
    for (int i = 0; i < currentTetromino.size(); i++) {
        for (int j = currentTetromino.size(); j >= 0; j--) {
            if(currentTetromino.check(i, j)) {
                if(i > y_max) {
                    y_max = i;
                }
                break;
            }
        }
    }
    
    hit_y_min = y_min + y;
    hit_y_max = y_max + y;
}

void Game::setShadow() {
    s_x = x;
    int tmp = 20;
    for (int i = hit_x_min - 2; i <= hit_x_max - 1; i++) {
        for (int j = BOARD_HEIGHT - 1; j >= 0; j--) {
            if (board_[i][j] == true) {
                if (j < tmp) {
                    tmp = j;
                    break;
                }   
            }
        }
    }
    s_y = tmp - (hit_y_max - hit_y_min);
}

void Game::build() {
    is_hold = false;
    x = 5;
    y = 1;
    hit_x_min = 0;
    hit_x_max = 0;
    s_x, s_y = 20;

    int xx, yy = 0;
    for (int i = x; i < currentTetromino.size() - 1; i++) {
        for (int j = y; j < currentTetromino.size() - 1; j++) {
            if (currentTetromino.check(xx++ % currentTetromino.size(), yy++ % currentTetromino.size())) {
                board_[i][j] = true;
            }
        }
    }
    currentTetromino = nextTetromino;
    makeNewTetromino(1);
}

void Game::makeNewTetromino(int num) {
        int shape = rand()%7;
        switch (shape)
        {
        case 0:
            if (num == 0)
                currentTetromino = I;
            else
                nextTetromino = I;
            break;
        case 1:
            if (num == 0)
                currentTetromino = O;
            else
                nextTetromino = O;
            break;
        case 2:
            if (num == 0)
                currentTetromino = T;
            else
                nextTetromino = T;
            break;
        case 3:
            if (num == 0)
                currentTetromino = S;
            else
                nextTetromino = S;
            break;
        case 4:
            if (num == 0)
                currentTetromino = Z;
            else
                nextTetromino = Z;
            break;
        case 5:
            if (num == 0)
                currentTetromino = J;
            else
                nextTetromino = J;
        case 6:
            if (num == 0)
                currentTetromino = L;
            else
                nextTetromino = L;
            break;
        default:
            break;
        }
    }

void Game::update() {
    playtime++;
    timer++;
    handleInput();
    hitbox();
    setShadow();
    if (y == s_y) {
        build();
    }

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

    for (int i = BOARD_WIDTH - 1; i >= 0; i--) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if (board_[i][j] == true) {
                console::draw(i + 1, j + 1, BLOCK_STRING);
            }
        }
    }

    currentTetromino.drawAt(BLOCK_STRING, x, y);
    currentTetromino.drawAt(SHADOW_STRING, s_x, s_y);
    nextTetromino.drawAt(BLOCK_STRING, BOARD_WIDTH + 4, 1); // 다음 테트로미노
    if (!hold_empty) {
        holdingTetromino.drawAt(BLOCK_STRING, BOARD_WIDTH + 10, 1); // 홀딩 테트로미노
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
    srand(time(NULL));

    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            board_[i][j] = false;
        }
    }

    for (int i = 0; i < BOARD_WIDTH; i++) {
        board_[i][BOARD_HEIGHT - 1] = true;
    }
    for (int i = 3; i < 6; i++) {
        board_[i][BOARD_HEIGHT - 2] = true;
    }
    board_[4][BOARD_HEIGHT - 3] = true;

    timer = 0;
    left_lines = LINES;
    playtime = 0;
    x = 5;
    y = 1;
    hit_x_min = 0;
    hit_x_max = 0;
    s_x, s_y = 20;

    currentTetromino = J;
    nextTetromino = I;
    makeNewTetromino(0);
    makeNewTetromino(1);
    holdingTetromino = I;

}