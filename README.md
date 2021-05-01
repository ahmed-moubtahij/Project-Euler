## How do I use this?

**Requirements**
- **-std=c++20**
- **gcc 10.1**
    - `msvc` hasn't implemented `std::ranges` yet and `clang`'s `std::ranges`/`concepts` seem to be yet incomplete.
- External dependencies: `range-v3` and `fmtlib` (optional for output display).

**Build Instructions**
```
cd path/to/your/folder
git clone https://github.com/Ayenem/Project-Euler.git --recursive
cd Project-Euler
cmake -B build
```
If you wish to build all targets:
```
cmake --build build/
```
If you wish to build a specific target e.g. P1:
```
cmake --build build/ --target P1
```
You may then execute the target with `./build/src/P1`.
