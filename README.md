# Cinder Shell

A custom Unix-like command-line shell written in C for Linux.

Cinder Shell is a systems programming project focused on building a shell from scratch and understanding how command execution, process management, parsing, and other shell features work.

## Goals

- Provide an interactive command-line interface.
- Execute external Linux commands.
- Implement shell built-in commands.
- Support quoting, input/output redirection, and pipelines.
- Handle signals and process management.
- Add automated tests as features are implemented.

## Technology Stack

- **Language:** C (C11)
- **Operating System:** Linux
- **Compiler:** GCC
- **Build System:** GNU Make
- **Version Control:** Git

## Build

```bash
make
```

## Run

```bash
./cinder
```

## Clean Build Files

```bash
make clean
```

## Project Structure

```text
cinder-shell/
├── docs/       # Design notes and documentation
├── include/    # Header files
├── src/        # C source files
├── tests/      # Tests
├── Makefile
├── README.md
└── .gitignore
```

## Project Status

Under active development. Features will be implemented incrementally, with testing and documentation added along the way.
