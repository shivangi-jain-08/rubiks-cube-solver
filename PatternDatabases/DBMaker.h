//
// Created by Shivangi on 03-03-2026.
//

#ifndef RUBIKS_CUBE_SOLVER_DBMAKER_H
#define RUBIKS_CUBE_SOLVER_DBMAKER_H


#include "CornerPatternDatabase.h"
#include "../Model/RubiksCubeBitboard.cpp"

using namespace std;

class DBMaker {
private:
    string fileName;
    CornerPatternDatabase cornerDB;

public:
    DBMaker(string _fileName);
    DBMaker(string _fileName, uint8_t init_val);

    bool bfsAndStore();
};


#endif //RUBIKS_CUBE_SOLVER_DBMAKER_H