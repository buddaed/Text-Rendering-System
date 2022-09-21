# Text Rendering System
A system for rendering any given string to screen

uses data output from BMfont to build its internal representation

Given a tab delimited file with keywords and phrases, the system will organize this info and will be able to render any phrase that is associated with a keyword

Supports English and french

supports horizontal and vertical alginment

Horizontal: Left (defualt), centered, and right Vertical: Top to bottom (defualt), centered, and bottom to top

# Install Instructions

## Windows

### Setting up Dev Environment

If dev environment not set up yet from other samples or TechLab 2050, follow these steps:

1) Install Visual Studio Community Edition 
2) Install Visual Studio Code
3) Install CMake
4) Ensure CMake is on your PATH
5) Install C/C++ VS Code Extension (0.28.3 or above)
6) Install CMake Tools VS Code extension (version 1.4.1 or above)
7) Install CMake VS Code extension (0.0.17 or above)
8) Install TortoiseGit (or another Git client, but I'll assume tortoise git)

### Building samples

1) Clone or download this repository.
2) Open the folder in VS Code
3) Ctrl+Shift+P then type/choose CMake: Configure
4) Choose one of the available options (e.g. Visual Studio Community 2017 Release - amd64)
5) Ctrl+Shift+P then type/choose CMake: Build
6) Hit F5 to run in debugger if all compiled well
7) You may need to choose "sample" from the dropdown the first time

## Linux

### Setting up Dev Environment

If dev environment not set up yet from other samples or TechLab 2050, follow these steps:

1) Install gcc or clang
2) Install Visual Studio Code
3) Install CMake
4) Ensure CMake is on your PATH
5) Install C/C++ VS Code Extension (0.28.3 or above)
6) Install CMake Tools VS Code extension (version 1.4.1 or above)
7) Install CMake VS Code extension (0.0.17 or above)
8) Install git

### Building samples

1) Clone or download this repository.
2) Open the folder in VS Code
3) Ctrl+Shift+P then type/choose CMake: Configure
4) Choose one of the available options (e.g. gcc)
5) Ctrl+Shift+P then type/choose CMake: Build
6) Hit F5 to run in debugger if all compiled well
7) You may need to choose "sample" from the dropdown the first time
