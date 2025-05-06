# PCCList

PCCList is a dynamic, Python-style list implementation in C++ capable of storing multiple types using `std::any`, including support for C-style strings, `std::string`, and various fundamental types. It also supports intuitive indexing, mutation, iteration, and formatted output.

## What it supports?

The list supports:
[x] Indexed access: `L[0]`
[x] Mutation: `L[1] = 99`
[x] Iteration: `for (auto v : L)`
[x] Type-safe retrieval via `.get<T>(index)` and `.try_get<T>(index)`

## How to use it?

Examples are in the `example` directory feel free to read around

## Compilation

For building (Modify the CMakeLists to point to your main.cc for custom usage):

```bash
cmake -B build -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build build
```

To run tests:

```bash
./build/tests/test_pcclist
```

## How it works?

PCCList internally stores elements in a `std::vector<std::any>`, allowing heterogeneous types. It supports construction from any mix of copyable/movable types, including C-style strings, which are converted to `std::string` internally. Access through `operator[]` returns a proxy ValueRef, which supports implicit casting, assignment, and printing via operator<<. Type safety is ensured through `.get<T>()` or `.try_get<T>()` APIs, which safely cast the value at a given index.

## TODOS for future

[] Support for nested lists (e.g., lists of lists)
[] JSON-style output or serialization
[] Optional typed mode with compile-time enforcement
[] Lots of Optimizations
[] Fuzz Testing using LibFuzzer

## Contributing

Feel free to contribute if you wanna add any interesting features or help speeding up the TODOs, if you implement something make sure to add the respective gtest for the feature on `tests/test_pcclist.cc`
