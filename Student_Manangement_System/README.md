# Student Management System

A simple console-based student record manager that stores records in a binary file.

Files
- `student.cpp` — main program source
- `student.bin` — binary data file (created at runtime)

Build & run (Windows, PowerShell)

```powershell
cd "C:\Users\User\OneDrive\Desktop\C++\Student_Manangement_System"
# build
g++ student.cpp -o student.exe
# run
.\student.exe
```

Notes
- The program writes a `student.bin` file in the same folder. If you want to start fresh, delete the file before running.
- The program uses a fixed-size name buffer for easy binary read/write. If you change the structure, existing `student.bin` files may become incompatible.

Improvements:
- Add a CSV/text mode for easier manual editing and portability.
- Add a managed CLI (menus) or a small GUI.
