# shade_it
Live OpenGL shader coding playground written in C89, nostdlib in a single file and tiny executable (~28kb).

It allows you to **live edit GLSL** fragment **shaders** file and when changes saved to the file it automatically displays the changes.

## Watch the demo video
https://github.com/user-attachments/assets/ac3f5131-83a1-4043-a2ae-b103240e10bc

> [!WARNING]
> THIS PROJECT IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS PROJECT AT YOUR OWN RISK!

## Download the executable
<p align="center">
  <a href="https://github.com/nickscha/shade_it/releases/latest/download/win32_shade_it.exe">
    <img src="https://img.shields.io/badge/Windows%20x64-green?style=flat-square" alt="Windows x64">
  </a>
  <a href="https://github.com/nickscha/shade_it/releases">
    <img src="https://img.shields.io/github/v/release/nickscha/shade_it?style=flat-square&color=blue" alt="Latest Release">
  </a>
  <a href="https://github.com/nickscha/shade_it/releases">
    <img src="https://img.shields.io/github/downloads/nickscha/shade_it/total?style=flat-square&color=brightgreen" alt="Downloads">
  </a>
  <a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square" alt="License">
  </a>
  <img src="https://img.shields.io/badge/Standard-C89-orange?style=flat-square" alt="C Standard">
  <img src="https://img.shields.io/badge/nolib-nostdlib-lightgrey?style=flat-square" alt="nostdlib">
</p>

## Features
- **Hot GLSL Shader reloading** - Saved changes to the GLSL file will be immediatly visible
- **Minimal binary size** — around **28kb** binary
- **Zero dependencies** — own win32 layer implementation, own OpenGL context creation
- **Debug UI** - Press F1 to see performance metrics and GLSL compilation errors/logs
- **Screen Recording** - Press F2 to start/stop recording the screen to a raw video file
- **C89 compliant** — portable and legacy-friendly  
- **nostdlib** — no dependency on the C Standard Library
- **no memory allocation** — There is **no memory allocation** by the tool itself. It only uses the memory Windows is acquiring for the OpenGL Framebuffers, ...
- **Strict compilation** — built with aggressive warnings & safety checks  

## Quick Start

### Download Windows Executable (Prebuilt)

Download the latest Windows executable from the **Latest Release**:
- https://github.com/nickscha/shade_it/releases/latest

### Building From Source

Clone the repository and build manually.
Either GCC or Clang is required to run the build script.

```bash
git clone https://github.com/nickscha/shade_it.git
cd shade_it
win32_shade_it_build.bat
```

You can now run the `win32_shade_it.exe` program.

### Running the program

```bat
REM This expects a file named "shade_it.fs" to be present
win32_shade_it.exe

REM Alternativly you can define your own fragment shader file
win32_shade_it.exe examples\shade_it_star_nest.fs
```

While **running** you can **edit** and save the fragment shader source file and shade_it will immediatly **hot-reload** the code.

If you want to create your own **GLSL fragment shader from scratch** you can use this **template** providing all uniforms `shade_it` hands over to the fragment shader:

### GLSL Fragment Shader Template

If you want to start writing your own fragment shader from scratch you can use this template containing all uniforms provided by the tool.

```glsl
#version 330 core

out vec4 FragColor;

/* Uniforms provided */
uniform vec3  iResolution;  // viewport width and height
uniform float iTime;        // time elapsed in seconds
uniform float iTimeDelta;   // render time in seconds
uniform int   iFrame;       // total frame counter
uniform float iFrameRate;   // current frames per second
uniform vec4  iMouse;       // mouse position (x,y)
uniform vec4  iTextureInfo; // texture width, height, cell width, cell height
uniform sampler2d iTexture; // texture slot

/* DEMO: Render gradient colors accross the entire screen */
void mainImage(out vec4 outColor, in vec2 fragCoord)
{
  vec2 uv = fragCoord / iResolution.xy;
  float t = iTime;
  outColor = vec4(uv, 0.5 + 0.5 * sin(t), 1.0);
}

void main()
{
  vec2 fragCoord = gl_FragCoord.xy;
  mainImage(FragColor, fragCoord);
}
```

Under the **examples** folder you can find different kinds of fragment shaders for inspiration that you can run directly.

### Show Debug UI

Press **F1** to show/hide the debug information, performance metrics and GLSL compilation errors/logs.

<a href="https://github.com/nickscha/shade_it"><img src="assets/shade_it_debug_ui.png"></a>

### Screen Recording

Press **F2** to start/stop recording the screen to a RAW video file named **shade_it_capture.raw**.

> [!WARNING]
> Since it is a RAW video output the size of the **file size can be huge**.

<a href="https://github.com/nickscha/shade_it"><img src="assets/shade_it_record_ui.png"></a>

After the recording has been stopped you can use a tool like **FFMPEG** or similar to **convert** it to a **video** format.

Example of creating a **MP4** video using **FFMPEG**:

```bat
ffmpeg -f rawvideo -pix_fmt rgb24 -s 800x600 -r 60 -i shade_it_capture.raw -vf vflip out.mp4
```

Note that the **size** (here 800x600) and the **FPS** (here 60) **have to match** with your recorded data.


## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.
