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

    int search(T &cube, int g, int bound, int lastMove, int heuristic)
    {
        int h = heuristic >= 0 ? heuristic : cornerDB.getNumMoves(cube);
        int f = g + h;

        if (f > bound)
            return f;

        if (cube.isSolved())
            return FOUND;

        int minNextBound = INT_MAX;

        struct Candidate
        {
            int moveIdx;
            int heuristic;
        };

        vector<Candidate> candidates;
        candidates.reserve(18);

        for (int i = 0; i < 18; i++)
        {
            if (lastMove != -1)
            {
                if (isInverse(lastMove, i))
                    continue;

                if (RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(i)) ==
                    RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(lastMove)))
                    continue;

                if (!enforceOppositeOrdering(lastMove, i))
                    continue;
            }

            auto moveEnum = static_cast<RubiksCube::MOVE>(i);
            cube.move(moveEnum);
            int childHeuristic = cornerDB.getNumMoves(cube);
            cube.invert(moveEnum);

            candidates.push_back({i, childHeuristic});
        }

        sort(candidates.begin(), candidates.end(), [](const Candidate &a, const Candidate &b)
             {
            if (a.heuristic == b.heuristic)
                return a.moveIdx < b.moveIdx;
            return a.heuristic < b.heuristic; });

        for (const auto &candidate : candidates)
        {
            auto moveEnum = static_cast<RubiksCube::MOVE>(candidate.moveIdx);
            cube.move(moveEnum);
            moves.push_back(moveEnum);

            int t = search(cube, g + 1, bound, candidate.moveIdx, candidate.heuristic);

            if (t == FOUND)
                return FOUND;

            if (t < minNextBound)
                minNextBound = t;

            moves.pop_back();
            cube.invert(moveEnum);
        }

        return minNextBound;
    }

    static bool isInverse(int lastMove, int currMove)
    {
        if (lastMove == -1)
            return false;

        auto lastFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(lastMove));
        auto currFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(currMove));

        if (lastFace != currFace)
            return false;

        int lastType = lastMove % 3;
        int currType = currMove % 3;

        if (lastType == 2 && currType == 2)
            return true;

        return (lastType == 0 && currType == 1) || (lastType == 1 && currType == 0);
    }

    static bool isOpposite(int lastMove, int currMove)
    {
        static constexpr std::array<int, 6> oppositeFaces = {5, 3, 4, 1, 2, 0};

        int lastFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(lastMove));
        int currFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(currMove));

        return oppositeFaces[lastFace] == currFace;
    }

    static bool enforceOppositeOrdering(int lastMove, int currMove)
    {
        if (!isOpposite(lastMove, currMove))
            return true;

        int lastFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(lastMove));
        int currFace = RubiksCube::faceOf(static_cast<RubiksCube::MOVE>(currMove));

        return currFace < lastFace;
    }

public:
    T rubiksCube;

    IDAstarSolver(T cube, const string &dbFile)
        : rubiksCube(cube)
    {
        if (!cornerDB.fromFile(dbFile))
            throw runtime_error("Failed to load Corner Pattern Database file.");
    }

    vector<RubiksCube::MOVE> solve()
    {
        int rootHeuristic = cornerDB.getNumMoves(rubiksCube);
        int bound = rootHeuristic;

        while (true)
        {
            moves.clear();
            int t = search(rubiksCube, 0, bound, -1, rootHeuristic);

            if (t == FOUND)
                return moves;

            bound = t;
        }
    }
};

#endif // RUBIKS_CUBE_SOLVER_IDASTARSOLVER_H
