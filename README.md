# Madd2
![GitHub](https://img.shields.io/github/license/realliance/madd2) ![GitHub commit activity](https://img.shields.io/github/commit-activity/m/realliance/madd2)

*Don't ask about [Madd1](https://github.com/realliance/madd)*

Madd2 is an [entity component system](https://en.wikipedia.org/wiki/Entity_component_system) game engine currently in pre-alpha limbo.

## Developing
### Prerequisites
- git
- CMake 3.12+
- clang
- clang-tidy
- include-what-you-use
- PkgConfig

### Environment Setup
```
# Clone the repo
git clone ...
cd madd2/

# Setup Build Directory
mkdir build
cd build/

# Bootstrap CMake 
# The following command additionally enables debug building and unit test building
cmake .. -D CMAKE_BUILD_TYPE=Debug -DPACKAGE_TESTS=ON

# Build Madd2
make

# Run Tests
make check
```

## Contributing
Interested in contributing to Madd2? See our [CONTRIBUTING.md](https://github.com/realliance/madd2/blob/mainline/CONTRIBUTING.md) before getting started.
