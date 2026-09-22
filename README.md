# MARP1 Problems

## Overview

This repository is an **academic coursework and problem collection** for data
structures and algorithms. It contains standalone C++ solutions associated
with numbered judge exercises (`juez1.cpp` through `juez40.cpp`), together
with compiled artifacts for most of those exercises.

The source code is educational rather than production software. Several files
include course headers referring to the Facultad de Informática and the
Universidad Complutense de Madrid, and comments are primarily in Spanish.

## What is included

The collection covers implementations and applications of common data
structures and algorithmic techniques, including:

- binary trees and tree traversals;
- AVL-based ordered sets;
- binary heaps and priority queues;
- indexed priority queues;
- undirected, directed, and weighted graphs;
- breadth-first search (BFS) and depth-first search (DFS);
- disjoint-set union (union-find);
- minimum spanning tree solutions using Kruskal's algorithm;
- shortest-path solutions using Dijkstra's algorithm; and
- sorting-based and greedy problem solutions.

These topics are visible in the numbered source files themselves. For
example, `juez2.cpp` contains an AVL set, `juez8.cpp` and `juez9.cpp` contain
priority-queue implementations, `juez22.cpp` uses disjoint sets, and
`juez25.cpp`–`juez30.cpp` contain weighted-graph, minimum-spanning-tree, and
shortest-path work.

## Repository organisation

Each `juezN.cpp` file is a separate program intended to be compiled and run
independently. The numbering is retained from the original judge/course
workflow; this repository does not currently provide problem statements or a
topic manifest for every exercise.

At the repository root you will find:

- `juez1.cpp` … `juez40.cpp`: C++ source files for the exercises;
- files named `juez1` … `juez40`: compiled artifacts checked in alongside
  many of the sources; and
- `tempCodeRunnerFile.cpp`: an auxiliary editor-generated source file.

There is no shared build system, package manifest, or automated test suite in
the repository. Reusable data-structure implementations are repeated or
adapted in several exercise files because the programs are standalone
coursework submissions.

## Language and requirements

- **Language:** C++
- **Standard-library facilities used:** streams, containers, smart pointers,
  queues, stacks, and related standard utilities
- **Compiler:** a C++ compiler with C++11 support or later

The repository does not declare a single required compiler version or
platform. The examples below use `g++`, but an equivalent compiler command
can be used.

## Build and run an exercise

Compile one exercise at a time from the repository root:

```sh
g++ -std=c++11 -O2 -Wall -Wextra juez27.cpp -o juez27
```

Then run the resulting executable and provide the input expected by that
exercise:

```sh
./juez27 < input.txt
```

Input and output formats are exercise-specific and are not documented in this
repository. Consult the corresponding source file and the original course or
online-judge statement when available.

## Limitations and scope

This is an educational archive, not a maintained algorithms library. In
particular:

- there is no README-level mapping from each number to an official problem
  title;
- original statements, sample cases, and correctness explanations are not
  included;
- complexity guarantees and edge-case coverage are not uniformly documented;
- the checked-in executables may be platform- or compiler-specific; and
- the solutions have not been presented as a single reusable API.

The repository should therefore be read as a record of coursework exercises
and implementation practice. Any use beyond that scope should begin with
independent review and testing of the relevant source file.
