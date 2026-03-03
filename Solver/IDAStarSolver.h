//
// Created by Shivangi on 03-03-2026.
//

#include "../Model/RubiksCube.h"
#include "../Model/PatternDatabase/PatternDatabase.h"

#ifndef RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H

template <typename T>
class IDAstarSolver
{
private:
    PatternDatabase<T> patternDB;
    vector<RubiksCube::MOVE> path;
    T cube;

    static constexpr int FOUND = -1;

    bool areOpposite(RubiksCube::MOVE a, RubiksCube::MOVE b)
    {
        int f1 = RubiksCube::faceOf(a);
        int f2 = RubiksCube::faceOf(b);

        return (f1 == 0 && f2 == 5) || (f1 == 5 && f2 == 0) ||
            (f1 == 1 && f2 == 3) || (f1 == 3 && f2 == 1) ||
            (f1 == 2 && f2 == 4) || (f1 == 4 && f2 == 2);
    }

    int search(int g, int bound, RubiksCube::MOVE lastMove, bool hasLast)
    {
        int h = patternDB.getEstimate(cube);
        int f = g + h;

        if (f > bound) return f;
        if (cube.isSolved()) return FOUND;

        int minNextBound = INT_MAX;

        for (int i = 0; i < 18; i++)
        {
            auto move = RubiksCube::MOVE(i);

            if (hasLast)
            {
                int f_curr = RubiksCube::faceOf(move);
                int f_last = RubiksCube::faceOf(lastMove);


                if (f_curr == f_last) continue;


                if (areOpposite(move, lastMove) && f_curr < f_last) continue;
            }

            cube.move(move);
            path.push_back(move);

            int t = search(g + 1, bound, move, true);

            if (t == FOUND) return FOUND;

            if (t < minNextBound) minNextBound = t;

            path.pop_back();
            cube.invert(move);
        }

        return minNextBound;
    }

public:
    IDAstarSolver(T startCube)
    {
        cube = startCube;
    }

    vector<RubiksCube::MOVE> solve()
    {
        int bound = patternDB.getEstimate(cube);
        cout << "Initial heuristic: " << patternDB.getEstimate(cube) << "\n";

        while (true)
        {
            int t = search(0, bound, RubiksCube::MOVE::U, false);

            if (t == FOUND)
                return path;

            if (t == INT_MAX)
                return {};

            bound = t;
        }
    }
};

#endif //RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
