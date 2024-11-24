# Nook CLI

Nook CLI is a command-line tool designed specifically to streamline the creation of game development projects using the Nook Engine. It automates project setup, scaffolds code templates, and configures assets to kickstart your game development process.

## Features

  - Nook Engine Integration: Automatically generates game project files compatible with the Nook Engine.
  - Pre-Defined Game Templates: Scaffold projects with templates for common game types like:
      -Platformer
      - Infinite Runner
      - Pong
  - Customizable Project Settings: Configure essential settings like resolution, gravity, and frame rate via interactive prompts.
  - Asset Organization: Automatically sets up directories for assets (Audio, Fonts, Sprites).
  - Build Support: Generates a CMakeLists.txt file for easy compilation with the Nook Engine.

## Prerequisites
  - Python: Python 3.7 or later.
  - CMake: For building the project files.
  - A C++ compiler (like GCC, Clang, or MSVC)

## Installation

1. Clone the repository:
```
  git clone https://github.com/ferstormblessed/nookcli.git
  cd nookcli
```

2. Install the required Python package:
```
  pip install click
```

3. Ensure the templates directory contains all required files:
  - main_template.cpp (starter file for the Nook Engine)
  - Templates for games (e.g., platformer_template.cpp, infinite_runner_template.cpp, pong_template.cpp)
  - CMakeLists_template.txt

## Usage

Run the CLI tool to scaffold a new Nook Engine project:
```
python nookcli.py --template [TEMPLATE]
```

### Examples

1. Interactive Mode: Omit the --template option to use interactive prompts:
```
python nookcli.py
```

Select a game template and configure settings such as window title, resolution, and physics parameters.

2. Predefined Template: Use a specific game template directly:
```
python nookcli.py --template platformer
```

## Output Structure
  - Main File: A main.cpp file tailored for the chosen game template.
  - Build File: A CMakeLists.txt file for compiling with the Nook Engine.
  - Config File: A config.txt file with settings such as resolution, gravity, and asset paths.
  - Assets Directory: Subdirectories for organizing game assets:
      - /Assets/Audio
      - /Assets/Fonts
      - /Assets/Sprites

## Default Configuration

Below are the default project settings, which can be customized during setup:

| Setting          | Default Value   | Description                        |
|-------------------|-----------------|------------------------------------|
| `WINDOW_TITLE`    | `NOOK`         | Title of the game window.          |
| `WIDTH`           | `1280`         | Window width (pixels).             |
| `HEIGHT`          | `720`          | Window height (pixels).            |
| `FRAMES`          | `60`           | Frame rate.                        |
| `GRAVITY`         | `10.0`         | Gravity strength for physics.      |
| `HIT_THRESHOLD`   | `0.01`         | Sensitivity for collision detection.|


## Contributing

Contributions to nookcli are welcome! If you'd like to improve its integration with the Nook Engine or add new features, please fork the repository and submit a pull request.

## License

The source code is dual licensed under Public Domain and MIT -- choose whichever you prefer.
