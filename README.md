# SFML Asteroids 🚀

A tiny **Asteroids-style** game in **C++17** with **SFML 2.5**.  
Rotate and thrust your ship, blast rocks that split into smaller ones, and survive wave after wave.

![Asteroids Game Screenshot](assets/AsteroidsScreenshot.png)

<p>
  <a href="https://en.cppreference.com/"><img alt="C++17" src="https://img.shields.io/badge/C%2B%2B-17-00599C.svg?logo=c%2B%2B&logoColor=white"></a>
  <a href="https://www.sfml-dev.org/"><img alt="SFML" src="https://img.shields.io/badge/SFML-2.6-8CC445.svg"></a>
  <img alt="Build" src="https://img.shields.io/badge/build-CMake-blue.svg">
  <img alt="License" src="https://img.shields.io/badge/license-MIT-lightgrey.svg">
</p>

---

## ✨ Features

- Smooth ship rotation (**A/D**) and forward with (**W**)
- Left-click to shoot (fire-rate limited; bullets have TTL)
- Asteroid waves spawn from screen edges and **wrap** across the screen
- **Splitting** asteroids: Large → Medium → Small
- Bullet ↔ Asteroid collisions
- Player ↔ Asteroid collisions with health & optional knockback
- Player stays in-bounds of screen
- Realistic movement physics

---

## 🎮 Controls

| Key / Mouse  | Action              |
| ------------ | ------------------- |
| **A / D**    | Rotate left / right |
| **W**        | Thrust forward      |
| **SpaceBar** | Fire bullet         |

---

## ⚙️ Requirements

- **C++17** compiler (GCC 9+)
- **CMake 3.16+**
- **SFML 2.5.1**

---

## 🛠️ Build & Run

cmake -S . -B build
cmake --build build --config Release

./build/asteroids # (Linux/macOS)
or build/Release/asteroids.exe (Windows)
