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

## AI Integration

The project includes a `GameAI` helper that invokes `scripts/ai_prompt.py` to
generate text using a local TinyLlama model.

1. Install the Python bindings:

   ```sh
   pip install llama-cpp-python
   ```

   Or build `llama.cpp` manually:

   ```sh
   git clone https://github.com/ggerganov/llama.cpp
   cd llama.cpp && make
   ```

2. Place the `TinyLlama.Q4_0.gguf` model in the `models/` directory.

The game calls the script at runtime to obtain generated text.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md).

## License

This project is licensed under the MIT License.
