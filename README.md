# 3D Medical Data Visualizer

A real-time 3D prototype built with **Godot 4** and **C++ (GDExtension)** 
that visualizes vascular geometry and hemodynamic data interactively.

## Motivation
Inspired by Mixed Reality (MxR) use cases in surgical planning — 
mapping clinical measurements onto 3D geometry so surgeons can 
intuitively interpret patient data at a glance.

## Features
- Color-coded vessel segments driven by real-time pressure data
- Diameter-scaled 3D geometry reflecting actual vessel measurements
- Interactive orbit camera (rotate, zoom) written in C++
- Data overlay UI showing segment information on click

## Tech Stack
- Godot 4.3
- C++17 via GDExtension
- SCons build system

## How to Build
```bash
scons
```
Then open the `demo/` folder in Godot 4.

## Architecture
```
src/
├── vessel.cpp       # 3D vessel node — data-driven mesh + color
├── camera.cpp       # Orbit camera controller
└── register.cpp     # GDExtension entry point
demo/
├── scenes/          # Godot scene files
└── bin/             # Compiled .so library (git-ignored)
```