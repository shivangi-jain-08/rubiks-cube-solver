//
// Created by Shivangi on 03-03-2026.
//

#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "../PatternDatabases/CornerPatternDatabase.h"

using namespace std;

#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

template <typename T>
class IDAstarSolver
{
private:
    CornerPatternDatabase cornerDB;

    vector<RubiksCube::MOVE> moves;

    static constexpr int FOUND = -1;

    int search(T& cube, int g, int bound, int lastMove)
    {
        int h = cornerDB.getNumMoves(cube);
        int f = g + h;

        if (f > bound)
            return f;

        if (cube.isSolved())
            return FOUND;

        int minNextBound = INT_MAX;

        for (int i = 0; i < 18; i++)
        {
            // Korf pruning: avoid same face repetition
            if (lastMove != -1 &&
                RubiksCube::faceOf(RubiksCube::MOVE(i)) ==
                RubiksCube::faceOf(RubiksCube::MOVE(lastMove)))
                continue;

            cube.move(RubiksCube::MOVE(i));
            moves.push_back(RubiksCube::MOVE(i));

            int t = search(cube, g + 1, bound, i);

            if (t == FOUND)
                return FOUND;

            if (t < minNextBound)
                minNextBound = t;

            moves.pop_back();
            cube.invert(RubiksCube::MOVE(i));
        }

        return minNextBound;
    }

public:
    T rubiksCube;

    IDAstarSolver(T cube, const
                  string& dbFile)
        : rubiksCube(cube)
    {
        if (!cornerDB.fromFile(dbFile))
            throw
                runtime_error("Failed to load Corner Pattern Database file.");
    }


    vector<RubiksCube::MOVE> solve()
    {
        int bound = cornerDB.getNumMoves(rubiksCube);

        while (true)
        {
            int t = search(rubiksCube, 0, bound, -1);

            if (t == FOUND)
                return moves;

            bound = t;
        }
    }
};

#endif //RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
