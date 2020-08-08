# MADD2
Don't ask about [MADD(1)](https://github.com/realliance/madd)

MADD2 is an ECS game engine currently in pre-alpha limbo.


## Developing
### PreReqs
* CMake 3.12+
* Clang
* include-what-you-use
* PkgConfig

### Building
* ``` mkdir build ```
* ``` cd build ```
###### Debug/With Tests
* ``` cmake .. -D CMAKE_BUILD_TYPE=Debug -DPACKAGE_TESTS=ON ```
###### Release
* ``` cmake -DCMAKE_BUILD_TYPE=Release .. ```
* ``` make ```

### Testing
* ``` make check ```

### Contributing
* TODO
