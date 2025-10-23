# Snake Game

A small Windows console Snake game written in C++.

Features
- Console-based rendering using Win32 `SetConsoleCursorPosition` and colored text.
- Keyboard input via `_getch()` and `GetAsyncKeyState` for responsive controls.
- Background music (looping `snakebg.wav`) and a small beep effect when eating.
- High score saved to `highscore.txt`.

Build & run (Windows, PowerShell)
1. Open PowerShell and change to the project directory:

```powershell
cd "C:\Users\User\OneDrive\Desktop\C++\Snake_Game"
```

2. Build with g++ (MinGW or similar):

```powershell
g++ snake.cpp -o snake.exe
```

3. Run from the terminal (must be a real console):

```powershell
.\snake.exe
```

Notes & troubleshooting
- The game requires an interactive console to receive key input and to support cursor repositioning. If you run it in VS Code, enable "Run In Terminal" for Code Runner or run it from the integrated terminal.
- Ensure `snakebg.wav`, `gameover.wav` are in the same folder as the executable for audio to work.
- If sounds don’t play, make sure you have the Windows multimedia APIs available; `PlaySound` is used from winmm.

Controls
- Arrow keys: move
- X: exit

