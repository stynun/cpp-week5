#include "tetromino.h"
#include "console/console.h"
#include <iostream>

Tetromino::Tetromino(std::string name, int size, std::string shape) {
    name_ = name;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            shape_[i][j] = false;
        }
    }
    int k = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (shape[k++] == 'O') {
            shape_[i][j] = true;
            }
        }
    }
}

void Tetromino::drawAt(std::string s, int x, int y) {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (shape_[i][j]) {
                std::cout << std::endl << shape_[i][j];
                console::draw(x + i, y + j, s);
            }
        }
    }

   /*
    if (s == "BLOCK_STRING") {
        console::draw(x, y, BLOCK_STRING);
    }
    */
   
}

Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");