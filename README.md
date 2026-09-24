# MARP1 problems

Academic C++ coursework and a collection of judge-style programming
solutions. The repository contains numbered, standalone programs developed
around data structures and algorithm exercises. It is best read as a personal
coursework archive rather than as a reusable library or a single application.

## What is covered

The source files visibly include implementations and exercises involving:

- binary-tree representations and traversals;
- ordered sets and tree rebalancing;
- binary heaps and minimum-priority queues;
- disjoint-set (union-find) structures;
- undirected and directed graphs stored with adjacency lists;
- breadth-first and depth-first traversal;
- connected-component and directed-graph analyses;
- weighted graphs, minimum-spanning-tree support, and shortest-path routines;
- Dijkstra's algorithm with indexed priority queues.

These topics are inferred from the code that is present. The numbered files
are not accompanied by problem statements, so this README intentionally does
not assign names, constraints, or expected outputs to individual exercises.

## Repository layout

| Path | Purpose |
| --- | --- |
| `juez1.cpp` ... `juez40.cpp` | Standalone C++ source files; each has its own `main` and reads/writes through standard streams. |
| `juez1` ... `juez40` | Pre-existing compiled artifacts in the repository. They are not required to rebuild the sources. |
| `juez8.dSYM.zip` | A debugger-symbol archive for one compiled artifact. |
| `tempCodeRunnerFile.cpp` | An editor-generated scratch file; it is not part of the numbered collection. |

Some implementations repeat course support code directly in the solution
file. There is no shared library, build system, dependency manifest, or
automated test suite in this repository.

## Prerequisites

- A C++ compiler with standard-library support. The sources have been
  syntax-checked with `g++ -std=c++17`.
- A shell for the command examples below.

No third-party libraries are required.

## Build and run

Compile one exercise into a separate build directory:

```sh
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic juez28.cpp -o build/juez28
./build/juez28 < input.txt
```

To compile the numbered sources without overwriting the checked-in binaries:

```sh
mkdir -p build
for source in juez[0-9]*.cpp; do
  g++ -std=c++17 -Wall -Wextra -pedantic "$source" \
    -o "build/${source%.cpp}"
done
```

Input formats and output conventions belong to the original exercise
statements, which are not included here. Supply input appropriate to the
selected program; without those statements, the repository cannot document
or validate each program's complete contract.

## Scope and limitations

- The programs are independent exercises, not a cohesive command-line tool.
- Filenames such as `juez28.cpp` identify repository order, not a public API
  or a problem title.
- The checked-in executables are platform-specific and may not run on another
  operating system or CPU architecture; rebuilding from source is preferred.
- There is no claim here that every exercise is complete, portable, or
  accepted by its original judge.
- No license or problem-statement bundle is included. Review the provenance
  and terms of individual source headers before redistributing code.

## Development note

When adding or revising an exercise, keep the source self-contained and
document any required input format near the program or in the corresponding
course materials. Preserve the numbered naming scheme unless the collection
is intentionally reorganized.
