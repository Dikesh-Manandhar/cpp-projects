# C++ Projects Workspace

This repository contains three small C++ example projects, each in its own folder:

- `Bank_Account_Simulation` — simple bank account console program
- `Snake_Game` — a small Windows console snake game (uses Win32 console APIs and sound)
- `Student_Manangement_System` — a basic student records console program

Each project has its own README with specific build/run instructions. This top-level README gives a quick overview and how to get started.

Getting started (Windows / PowerShell)
1. Open PowerShell and change to this repo folder:

```powershell
cd "C:\Users\User\OneDrive\Desktop\C++"
```

2. Build a project with g++ (example for Snake_Game):

```powershell
cd Snake_Game
g++ snake.cpp -o snake.exe
.\snake.exe
```

Notes
- The Snake game uses Win32 console APIs and PlaySound. Run it from a real terminal (PowerShell or cmd), not from an editor output pane. If using VS Code and Code Runner, enable `Run In Terminal` in Code Runner settings.
- Audio files (.wav) used by the Snake game must be present next to the executable (`snakebg.wav`, `gameover.wav`).
- `highscore.txt` and other runtime files are included here; you may delete or preserve them as needed.

Per-project READMEs below provide more details and troubleshooting tips.
