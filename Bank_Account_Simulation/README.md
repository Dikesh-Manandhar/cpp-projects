# Bank Account Simulation

A simple console program demonstrating file-backed bank account operations.

Files
- `bank.cpp` — main program source
- `accounts.txt` — sample data file

Build & run (Windows, PowerShell)

```powershell
cd "C:\Users\User\OneDrive\Desktop\C++\Bank_Account_Simulation"
# build
g++ bank.cpp -o bank.exe
# run
.\bank.exe
```

Notes
- The program reads/writes `accounts.txt` in the same folder. Keep a backup if you want to preserve sample data.
- You can open the file in a text editor to verify account entries.

Want improvements?
- I can add argument parsing, nicer menus, or a small JSON-based persistence layer.
