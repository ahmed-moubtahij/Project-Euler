## How do I use this?

**Requirements**
- **-std=c++20**
- **gcc 10.1**
    - `msvc` hasn't implemented `std::ranges` yet and `clang`'s `std::ranges`/`concepts` seem to be yet incomplete.
- External dependencies: `range-v3` and `fmtlib` (optional for output display).

**Build Instructions**
```
    cd path/to/your/folder
    git clone https://github.com/Ayenem/k-means.git --recursive
    cd k-means
    cmake -B build
    cmake --build build
```
You may then execute the provided example to ensure everything works e.g. `./build/src/demo`.
