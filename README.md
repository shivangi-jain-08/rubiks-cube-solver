# Rubik’s Cube Optimal Solver (C++)

A high-performance Rubik’s Cube solver implemented in modern C++ that combines multiple state representations, classical search algorithms, and a Korf-style **IDA*** search powered by a **corner pattern database**.

The project focuses on algorithmic depth, heuristic design, and memory-efficient state abstraction.

---

## Overview

This repository implements:

* Multiple cube state representations (3D array, 1D array, bitboard)
* DFS, BFS, and Iterative Deepening DFS
* Iterative Deepening A* (IDA*)
* Corner Pattern Database (8! × 3⁷ states)
* Nibble-packed heuristic storage
* Combinatorial permutation ranking
* Database generation tooling
* End-to-end shuffle → solve → verify pipeline

The solver returns **optimal solutions** under the quarter-turn metric.

---

## Architecture

```
Model/
    RubiksCube.h                 -> Abstract cube interface
    RubiksCube3dArray.cpp        -> Sticker-accurate model
    RubiksCube1dArray.cpp        -> Flattened 54-element model
    RubiksCubeBitboard.cpp       -> 6×64-bit optimized representation

Solver/
    DFSSolver.h
    BFSSolver.h
    IDDFSSolver.h
    IDAStarSolver.h              -> Heuristic optimal solver

PatternDatabases/
    CornerPatternDatabase.*
    DBMaker.*
    NibbleArray.*
    PermutationIndexer.h
    math.*
```

---

## Cube Representations

### 1. 3D Sticker Model

* Intuitive layout
* Useful for debugging and validation

### 2. 1D Flattened Model

* 54-byte compact representation
* Faster comparisons and hashing

### 3. Bitboard Model (Primary)

* 6 × 64-bit integers
* Efficient move execution
* Compact memory layout
* Used for pattern database generation and IDA*

---

## Search Algorithms

### Depth-First Search (DFS)

* Depth-bounded search
* Full branching factor exploration

### Breadth-First Search (BFS)

* Optimal for shallow scrambles
* Uses hashing for visited state tracking

### Iterative Deepening DFS (IDDFS)

* Memory-efficient alternative to BFS
* Gradually increases search depth

### Iterative Deepening A* (IDA*)

The primary solver implements:

* Iterative deepening on `f = g + h`
* Corner pattern database heuristic
* Korf-style pruning:

    * No inverse moves
    * No repeated face turns
    * Opposite face ordering constraint
* Move ordering based on heuristic value
* In-place cube mutation with backtracking

This guarantees optimal solutions under the quarter-turn metric.

---

## Corner Pattern Database

The heuristic abstracts the cube to its corner configuration:
```
8! × 3⁷ = 88,179,840 states
```

### Indexing Strategy

* Corner permutation ranked using Lehmer code
* Corner orientation encoded as base-3 number
* Final index:
```
index = (permRank × 2187) + orientation
```

### Storage

* 4-bit nibble-packed array
* ~50MB memory footprint
* Serialized to disk
* Efficient lookup during IDA*

Database generation is performed via BFS from the solved state.

---

## Database Generation

The `DBMaker` tool builds and serializes the corner pattern database.

Example usage:

```cpp
DBMaker maker("Databases/cornerdb.txt", 0xF);
maker.bfsAndStore();
```

The database file is then loaded by the IDA* solver at runtime.

---

## Running the Solver

Example workflow in `main.cpp`:

```cpp
RubiksCubeBitboard cube;
vector<RubiksCube::MOVE> shuffle = cube.randomShuffle(8);

IDAstarSolver<RubiksCubeBitboard> solver(cube, "Databases/cornerdb.txt");
vector<RubiksCube::MOVE> solution = solver.solve();
```

Build Requirements:

* C++20
* CMake 3.x+

---

## Technical Highlights

* Combinatorial permutation ranking (Lehmer code)
* Base-3 orientation encoding
* Nibble-level memory packing
* Heuristic admissibility preservation
* Pruned move generation
* Multi-representation design for experimentation
* Optimal search implementation

This project demonstrates practical application of:

* State-space search theory
* Heuristic design
* Memory-efficient abstraction
* Algorithmic pruning techniques
* Systems-level C++ implementation

---

## Future Improvements

Moving forward, I am planning to add: 

* Edge pattern databases for stronger heuristics
* Multi-pattern heuristic combination
* Performance instrumentation and benchmarking
* Parallelized search
* Additional symmetry reductions

---

## Author

Shivangi Jain
