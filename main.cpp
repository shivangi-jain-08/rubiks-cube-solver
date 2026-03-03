#include <iostream>
#include <bits/stdc++.h>

#include "Model/RubiksCube3dArray.cpp"
// #include "Model/RubiksCube1dArray.cpp"
// #include "Model/RubiksCubeBitboard.cpp"
#include "Solver/DFSSolver.h"
#include "Solver/BFSSolver.h"
#include "Solver/IDDFSSolver.h"
#include "Solver/IDAStarSolver.h"
#include "PatternDatabases/DBMaker.h"


int main()
{
    // RubiksCube3dArray object3DArray;
    // RubiksCube1dArray object1dArray;
    // RubiksCubeBitboard objectBitboard;

    // DFS Solver Testing __________________________________________________________________________________________
    // RubiksCube3dArray cube;
    // cube.print();
    // //
    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(6);
    // for (auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();
    //
    // DFSSolver<RubiksCube3dArray, Hash3d> dfsSolver(cube, 8);
    // vector<RubiksCube::MOVE> solve_moves = dfsSolver.solve();
    //
    // for (auto move: solve_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // dfsSolver.rubiksCube.print();


    //BFS Solver -----------------------------------------------------------------------------------------------------
    // RubiksCubeBitboard cube;
    // cube.print();
    //
    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(6);
    // for(auto move: shuffle_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();
    //
    // BFSSolver<RubiksCubeBitboard, HashBitboard> bfsSolver(cube);
    // vector<RubiksCube::MOVE> solve_moves = bfsSolver.solve();
    //
    // for(auto move: solve_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // bfsSolver.rubiksCube.print();

    // IDDFS Solver ----------------------------------------------------------------------------------------------------
    // RubiksCubeBitboard cube;
    // cube.print();
    //
    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(9);
    // for (auto move : shuffle_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // cube.print();
    //
    // IDDFSSolver<RubiksCubeBitboard, HashBitboard> iddfsSolver(cube, 7);
    // vector<RubiksCube::MOVE> solve_moves = iddfsSolver.solve();
    //
    // for (auto move : solve_moves) cout << cube.getMove(move) << " ";
    // cout << "\n";
    // iddfsSolver.rubiksCube.print();

    // IDA* SOLVER ---------------------------------------------------------------------------------------------------
    // RubiksCubeBitboard cube;
    // cube.print();
    //
    // vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(6);
    //
    // cout << "Shuffle: ";
    // for (auto move : shuffle_moves)
    //     cout << RubiksCube::getMove(move) << " ";
    // cout << "\n";
    //
    // cube.print();
    //
    // IDAstarSolver<RubiksCubeBitboard> solver(cube);
    //
    // vector<RubiksCube::MOVE> solve_moves = solver.solve();
    //
    // cout << "Solution: ";
    // for (auto move : solve_moves)
    //     cout << RubiksCube::getMove(move) << " ";
    // cout << "\n";
    //
    // for (auto move : solve_moves)
    //     cube.move(move);
    //
    // cout << "After solving:\n";
    // cube.print();

    // Making the database

    // DBMaker maker("Databases/corner_db.bin", 0xF);
    // maker.bfsAndStore();
    // return 0;

    //
    // DBMaker dbMaker(fileName, 0x99);
    // dbMaker.bfsAndStore();

    // IDA* Solver with pattern databases----------------------------------------------------------------------------------
    string fileName = "D:\\acad data\\pvt_projects\\rubiks-cube\\Repos\\rubiks-cube-solver\\Databases\\cornerdb.txt";
    RubiksCubeBitboard cube;
    cube.print();

    vector<RubiksCube::MOVE> shuffle_moves = cube.randomShuffle(8);

    cout << "Shuffle: ";
    for (auto move : shuffle_moves)
        cout << RubiksCube::getMove(move) << " ";
    cout << "\n\n";

    cube.print();

    IDAstarSolver<RubiksCubeBitboard> solver(cube, fileName);

    vector<RubiksCube::MOVE> solution = solver.solve();

    cout << "Solution (" << solution.size() << " moves): ";
    for (auto move : solution)
        cout << RubiksCube::getMove(move) << " ";
    cout << "\n\n";

    for (auto move : solution)
        cube.move(move);

    cout << "After solving:\n";
    cube.print();
}
