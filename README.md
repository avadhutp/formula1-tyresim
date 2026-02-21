🏎️ F1 Race Strategy & Tyre Degradation Simulator

A high-performance simulation tool designed to model realistic Formula 1 tyre wear and lap time evolution.

🛠️ The Tech Stack

Data Scout: Python 3.14 + FastF1 API (Extracting real-world telemetry and lap data).

The Bridge:

 SQLite3 (Relational database for storing historical race data and compound coefficients).

Physics Engine:

 C++17 (MSYS2/GCC) (Core simulation logic, fuel weight scaling, and tyre wear curves).

📈 Current Physics Implementation

The simulator currently utilizes a V-Curve (Polynomial/Power) model to represent the life of a tyre stint:

- Warm-up Phase: Initial lap time penalty for cold tyres.

- Stable Phase: The "sweet spot" where fuel burn-off compensates for initial rubber wear.

- Degradation Phase: Exponential lap time increase as the tyre carcass reaches the end of its life.

💻 Local Development

(This project is optimized for VS Code)

Build Shortcut: Ctrl + Shift + B 

How to Setup the Build Shortcut:

1. Open the Command Palette: Press Ctrl + Shift + P.

2. Find Build Task: Type Tasks: Configure Default Build Task and select it.

3. Choose Compiler: Select C/C++: g++.exe build active file.

4. Edit for Multi-file Support: To make it work for the F1 Sim (linking time.cpp and tyredegsim.cpp), you just need to change the args line from ${file} to ${fileDirname}/*.cpp.

Dependencies: 

Requires lsqlite3 for database connectivity.