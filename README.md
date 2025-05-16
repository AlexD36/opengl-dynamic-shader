# OpenGL Dynamic Shader

![OpenGL](https://img.shields.io/badge/OpenGL-3.3+-blue?style=flat-square)
![GLFW](https://img.shields.io/badge/GLFW-3.x-green?style=flat-square)
![GLEW](https://img.shields.io/badge/GLEW-2.x-orange?style=flat-square)

## Overview

This project demonstrates a dynamic particle effect shader built with OpenGL. The application features interactive controls that allow users to modify the visual appearance of the shader in real-time. The shader showcases continuous color transitions and particle effects, creating a dynamic and engaging visualization.



https://github.com/user-attachments/assets/d0c195fe-1586-4285-a18a-62088a579e3b


---

## Features

1. **Dynamic Shader:**
   - Particle effects with continuously varying colors.
   - Parameters like zoom, intensity, and duration dynamically adjust based on user input.

2. **Interactivity:**
   - **Keyboard Controls:**
     - Arrow keys to adjust zoom and intensity.
     - `W`/`S` to change animation duration.

3. **Performance:**
   - Runs smoothly at 60 FPS (hardware permitting).

---

## Requirements

### Software
- OpenGL 3.3+ compatible environment.
- Libraries:
  - [GLFW](https://www.glfw.org/) for window management.
  - [GLEW](http://glew.sourceforge.net/) for OpenGL function loading.
- C++ Compiler: GCC, Clang, or MSVC.

### Hardware
- GPU supporting OpenGL 3.3+.
- At least 4 GB RAM.

---

## Project Structure

```
OpenGL-Dynamic-Shader/
├── src/
│   ├── main.cpp               # Main application source code
│   └── shaders/
│       ├── vertex_shader.glsl # Vertex shader
│       └── fragment_shader.glsl # Fragment shader
├── include/                   # External library headers
└── build/                     # Build files
```

---

## Installation

### Clone the Repository
```bash
git clone https://github.com/AlexD36/opengl-dynamic-shader.git
cd opengl-dynamic-shader
```

### Install Dependencies

#### On Linux (Ubuntu/Debian):
```bash
sudo apt-get install libglfw3-dev libglew-dev
```

#### On Windows/macOS:
Download and install the required libraries from their official websites.

### Build the Project

#### On Linux/macOS:
```bash
g++ -o main src/main.cpp -lGL -lGLEW -lglfw -std=c++11
```

#### On Windows (using MinGW):
```bash
g++ -o main.exe src/main.cpp -lglew32 -lglfw3 -lopengl32 -std=c++11
```

### Run the Application

#### On Linux/macOS:
```bash
./main
```

#### On Windows:
```bash
main.exe
```

---

## Usage

1. Start the application from your terminal or IDE.
2. Use the following controls to interact:
   - **Keyboard:**
     - Adjust zoom and intensity with arrow keys.
     - Change animation duration with `W`/`S`.
3. Enjoy the dynamic particle effect in the OpenGL window.

---

## Troubleshooting

### Common Issues

1. **Error 0xc000007b (Windows):**
   - Ensure GLEW and GLFW libraries are installed correctly.
   - Check if you are using the appropriate versions (32-bit or 64-bit) matching your system.

2. **OpenGL Version Unsupported:**
   - Update your GPU drivers to the latest version.


---
   ## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

4. **Shader Compilation Errors:**
   - Check for detailed error messages in the console.
