# Maze Game 🎮

A console-based maze navigation game developed in C with a focus on Test-Driven Development (TDD). Challenge yourself by navigating through complex mazes or let the game generate one for you!

## Table of Contents
- [Game Objective](#game-objective-)
- [Features](#features-)
- [Getting Started](#getting-started-)
  - [Prerequisites](#prerequisites)
  - [Building the Game](#building-the-game)
  - [Running the Game](#running-the-game)
- [Controls](#controls-)
- [Maze Options](#maze-options)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Technical Details](#technical-details)
- [What I Learned](#what-i-learned-)

## Game Objective 🎯

Navigate through the maze from the start point (S) to the end point (E). Stay within the maze boundaries and avoid walls (#) to successfully complete the challenge!

## Features ✨

- **Dual Maze Modes**: Choose between loading a premade maze or auto-generating a new one
- **Auto-Generation**: Dynamic maze generation using recursive backtracking algorithm
- **Customizable Dimensions**: Generate mazes from 5x5 up to 100x100
- **Input Validation**: Comprehensive error handling for files and user input
- **Visual Feedback**: ASCII art messages and clear navigation feedback
- **Map Display**: View the entire maze at any time during gameplay

## Getting Started 🚀

### Prerequisites

- GCC compiler
- Make utility
- Unix-like environment (Linux, macOS, or WSL on Windows)

### Building the Game

```bash
make maze
```

To clean build artifacts:
```bash
make clean
```

### Running the Game

**Option 1: Interactive Script**
```bash
./run.sh
```

**Option 2: Direct Execution with Premade Maze**
```bash
./maze <mazefile_path>
```

**Option 3: Direct Execution with Auto-Generation**
```bash
./maze
# Then select option 2 when prompted
```

## Controls 🎮

| Key | Action |
|-----|--------|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `M` | Display the map |

Controls are case-insensitive!

## Maze Options

### Premade Mazes

Load from existing maze files

### Auto-Generated Mazes

The game uses a **recursive backtracking algorithm** to generate perfect mazes:
1. Select option 2 at the main menu
2. Enter desired dimensions (5-100 for both height and width)
3. The algorithm ensures all mazes have a valid solution path from S to E

**Maze Format Requirements:**
- Valid characters: `#` (wall), ` ` (space), `S` (start), `E` (end)
- Dimensions: 5-100 rows/columns
- Exactly one start and one end point
- Consistent line lengths

## Project Structure

```
maze-game/
├── maze.c                          # Main entry point
├── GameLogic.c/h                   # Core game loop and win condition
├── PlayerOperations.c/h            # Player movement and validation
├── MazeInit.c/h                    # Maze loading and validation
├── MazeGenerator.c/h               # Maze auto-generation
├── FileManipulationFunctions.c/h   # File I/O operations
├── GameMessages.c/h                # ASCII art and user messages
├── MazeStructs.h                   # Data structure definitions
├── MazeConstants.c/h               # Game constants and exit codes
├── makefile                        # Build configuration
├── test.sh                         # Automated test suite
├── run.sh                          # Interactive run script
└── testMazes/                      # Test maze files
    ├── valid/                      # Valid maze examples
    └── invalid/                    # Invalid maze examples for testing
```

## Testing

Run the automated test suite:

```bash
chmod +x test.sh
./test.sh
```

The test suite validates:
- ✅ Argument handling
- ✅ File operations and permissions
- ✅ Maze dimension constraints
- ✅ Start/end point validation
- ✅ Character validation
- ✅ User input handling

See [`test-plan.md`](test-plan.md) for detailed test cases.

## Technical Details

**Key Algorithms:**
- Recursive backtracking for maze generation (see [`MazeGenerator.c`](MazeGenerator.c))
- Fisher-Yates shuffle for randomization
- Path validation for player movement

**Memory Management:**
- Dynamic allocation for maze structures
- Proper cleanup on exit

## What I Learned 📚

### Technologies & Tools
- **C Programming**: Low-level memory management, pointer arithmetic, and struct manipulation
- **Make**: Build automation and dependency management with makefiles
- **Bash Scripting**: Automated testing and helper scripts for development workflow

### Programming Concepts

#### Data Structures
- **Structs**: Designed custom data structures for Maze and Player entities
- **Pointers**: Extensive use of pointers for memory-efficient data manipulation

#### Algorithms
- **Recursive Backtracking**: Implemented maze generation algorithm with depth-first search
- **Fisher-Yates Shuffle**: Randomization algorithm for unbiased direction selection
- **Path Validation**: Boundary checking and collision detection logic

#### Software Engineering Practices
- **Test-Driven Development (TDD)**: Wrote tests before implementation to ensure code quality
- **Modular Design**: Separated concerns into distinct files for maintainability
- **Error Handling**: Comprehensive validation with meaningful error messages and exit codes
- **Memory Management**: Proper allocation/deallocation to prevent memory leaks
- **Code Documentation**: Clear comments and structured code for readability

#### File I/O
- **File Operations**: Reading, parsing, and validating external maze files
- **Permission Handling**: Checking file permissions and handling access errors
- **Buffer Management**: Safe string handling with `fgets()` and `sscanf()`

#### Development Methodologies
- **Incremental Development**: Built features step-by-step with continuous testing
- **Defensive Programming**: Input validation at every user interaction point
- **Code Refactoring**: Iteratively improved code structure and efficiency

### Key Challenges Overcome
1. **Dynamic Memory Allocation**: Managing 2D arrays with variable dimensions
2. **Recursive Algorithms**: Implementing and debugging recursive backtracking
3. **Input Validation**: Handling edge cases in user input and file parsing
5. **Automated Testing**: Creating robust bash scripts for comprehensive test coverage

---

**Developed with Test-Driven Development principles**