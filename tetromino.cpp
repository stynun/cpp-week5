#include "tetromino.h"
#include "console/console.h"
#include <iostream>

Tetromino Tetromino::I("I", 4, "XXXXOOOOXXXXXXXX");
Tetromino Tetromino::O("0", 2, "OOOO");
Tetromino Tetromino::T("T", 3, "XOXOOOXXX");
Tetromino Tetromino::S("S", 3, "XOOOOXXXX");
Tetromino Tetromino::Z("Z", 3, "OOXXOOXXX");
Tetromino Tetromino::J("J", 3, "OXXOOOXXX");
Tetromino Tetromino::L("L", 3, "XXOOOOXXX");

Tetromino::Tetromino(std::string name, int size, std::string shape) {
    name_ = name;
    size_ = size;

    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            shape_[i][j] = false;
        }
    }
    int k = 0;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (shape[k++] == 'O') {
            shape_[i][j] = true;
            }
        }
    }

    if (name == "I") {
        original_ = &I;
    }
    else if (name == "O") {
        original_ = &O;
    }
    else if (name == "T") {
        original_ = &T;
    }
    else if (name == "S") {
        original_ = &S;
    }
    else if (name == "Z") {
        original_ = &Z;
    }
    else if (name == "J") {
        original_ = &J;
    }
    else if (name == "L") {
        original_ = &L;
    }

    
}

Tetromino Tetromino::rotatedCW() {
    std::string rotatedShape = "";
    
    for (int x = 0; x < size_; x++) {
        for (int y = size_ - 1; y >= 0; y--) {
            if (check(x, y)) {
                rotatedShape.append("O");
            }
            else {
                rotatedShape.append("X");
            }
        }
    }
   
   return Tetromino(name_, size_, rotatedShape);
}

Tetromino Tetromino::rotatedCCW() {
    std::string rotatedShape = "";
    
    for (int x = size_; x >= 0; x--) {
        for (int y = size_ - 1; y >= 0; y--) {
            if (check(x, y)) {
                rotatedShape.append("O");
            }
            else {
                rotatedShape.append("X");
            }
        }
    }
   
   return Tetromino(name_, size_, rotatedShape);
}



void Tetromino::drawAt(std::string s, int x, int y) {
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            if (shape_[i][j]) {
                console::draw(x + i, y + j, s);
            }
        }
    }
}

