//
// Created by Shivangi on 03-03-2026.
//

#ifndef RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
#define RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H

template <typename T>
class PatternDatabase
{
public:
    int getEstimate(const T& cube) const
    {
        int misplaced = 0;

        for (int i = 0; i < 8; i++)
        {
            if (cube.getCornerIndex(i) != i)
                misplaced++;
            else if (cube.getCornerOrientation(i) != 0)
                misplaced++;
        }

        return (misplaced + 3) / 4;
    }
};

#endif //RUBIKS_CUBE_SOLVER_PATTERNDATABASE_H
