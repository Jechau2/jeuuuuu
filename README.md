# jeuuuuu

Simple SDL2/SDL2_ttf project example.

## Requirements

- SDL2
- SDL2_ttf
- CMake 3.10+

## Build

```sh
./scripts/build.sh [Debug|Release]
```

Artifacts are placed in `build/` and the executable in `bin/jeuuuuu`.

## Run

```sh
./scripts/run.sh
```

## Lint

```sh
./scripts/lint.sh
```

## Project layout

```
bin/          - built executable
build/        - CMake build directory (ignored)
include/      - public headers
lib/          - external libraries (optional)
scripts/      - helper scripts
src/          - source files
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

This project is licensed under the MIT License.
