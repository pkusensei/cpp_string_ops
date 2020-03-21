This is a backup repo for mainly 2 purposes. 

1. Provide some common string operations that should be in C++ STL but not. Well some are coming to C++20.

    - __PITFALL__ To avoid unnecessary allocation/copy, `std::string_view` is used as much as possible instead of `std::string`. But the former is a view and may be dangling when its actual content gets moved/destroyed. 

2. Provide a template config to compile, run, and debug C++ code in VS Code. 