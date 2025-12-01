# A5-biquadris

## How to Compile?

# Compile
make clean
make

# Run
./biquadris
```

### On Mac OS (Local Development)
If working locally on Mac, you'll need XQuartz installed:

1. **Install XQuartz**: Download from https://www.xquartz.org/
2. **Restart your Mac** after installation
3. **Launch XQuartz** before compiling/running
```bash
# Compile with Mac-specific paths
make clean
make

# Or manually:
clang++ -std=c++20 *.cc -o biquadris -I/opt/X11/include -L/opt/X11/lib -lX11

# Run (XQuartz must be running)
./biquadris
```

## Command-Line Options

- **-text** — run in text-only mode (no graphics)
- **-seed xxx** — set random seed to `xxx`
- **-scriptfile1 xxx** — use custom sequence file for player 1 (default: `sequence1.txt`)
- **-scriptfile2 xxx** — use custom sequence file for player 2 (default: `sequence2.txt`)
- **-startlevel n** — start at level `n` (default: 0)

**Example:**
```bash
./biquadris -seed 42 -startlevel 2 -text
```

## Command List / Instructions

### Movement
- **left**, **lef** — move block left  
- **right**, **ri** — move block right  
- **down**, **do** — move block down  

### Rotation
- **clockwise**, **cw** — rotate 90° clockwise  
- **counterclockwise**, **ccw** — rotate 90° counterclockwise  

### Block Control
- **drop**, **dr**, **dro** — drop current block instantly  
- **I**, **J**, **L**, **O**, **S**, **T**, **Z** — replace current block (testing only)

### Level Control
- **levelup**, **levelu** — increase level  
- **leveldown**, **leveld** — decrease level  

### Random / Sequence
- **random** — restore randomness (levels 3-4)
- **norandom <file>** — use block sequence from file (levels 3-4)
- **sequence <file>** — read and execute commands from file  

### Game Control
- **restart** — clear board and restart game  
- **EOF** (Ctrl+D) — terminate game  

---

## Command Features

### Minimal Unique Prefixes
Commands accept the shortest unique prefix:
- `lef` = `left` (distinguishes from `levelup`)
- `ri` = `right`
- `cw` = `clockwise`
- `levelu` = `levelup`

### Numeric Multipliers
Most commands accept numeric prefixes:
```
3left     # move left 3 times
2drop     # drop current block + next 2 blocks
5down     # move down 5 times (or until blocked)
```

**Multipliers NOT allowed for:**
- `restart`
- `hint`
- `random`
- `norandom`

---

## Game Mechanics

### Levels (0-4)
- **Level 0**: Sequential from file (non-random, for testing)
- **Level 1**: Random with S/Z blocks less common (1/12 each)
- **Level 2**: All blocks equally likely (1/7 each)
- **Level 3**: S/Z more common (2/9 each) + **heavy blocks** (auto-drop after move)
- **Level 4**: Level 3 + 1×1 brown blocks drop every 5 placements without row clears

### Special Actions (Clear 2+ rows)
When you clear multiple rows simultaneously, choose one effect on your opponent:
- **blind** — obscure rows 3-12, columns 3-9 with `?` until next drop
- **heavy** — opponent's blocks drop 2 rows after each left/right move
- **force <block>** — force opponent's next block (e.g., `force I`)

### Scoring
- **Line clears**: (current level + lines cleared)²
- **Block removal**: (level when block generated + 1)²
- Hi-score persists across restarts (until program exits)

### Block Types
```
I-block: IIII

J-block: J
         JJJ

L-block:   L
         LLL

O-block: OO
         OO

S-block:  SS
         SS

Z-block: ZZ
          ZZ

T-block: TTT
          T
```

### Board Layout
- **11 columns × 15 rows** (visible)
- **3 extra rows** at top for rotation space
- Blocks spawn at top-left, just below reserve rows
- Game ends if block can't fit in spawn position

---

## Troubleshooting

### Graphics Not Displaying
- **Linux**: Make sure you SSH'd with `-Y` flag
- **Mac**: Ensure XQuartz is running before launching the game
- **Test X11**: Run `xeyes` — if it doesn't work, neither will graphics

### Compilation Errors
- **`g++20` not found**: Check if aliases are set or use `g++-12` directly
- **`X11/Xlib.h` not found**: Verify X11 paths with `-I` and `-L` flags
- **Module errors**: Ensure using a compiler with C++20 module support (g++-12 or later)

### Cannot Execute Binary
- You likely compiled on Mac and tried to run on Linux (or vice versa)
- Recompile on the target machine

### XQuartz Won't Open (Mac)
- XQuartz doesn't show a window — it runs in the background
- Look for the **X icon** in your menu bar
- If not running: `open -a XQuartz`

---

## Notes
- Commands accept **minimal unique prefixes** (e.g., `lef` = `left`)
- **Numeric prefixes** allowed for most commands (e.g., `3left` moves left three times)
  - NOT allowed for: `restart`, `hint`, `random`, `norandom`
- Invalid input **must not crash** the program
- Both text and graphical displays update after each command
- Use `sequence` files for reproducible testing
- Make sure `sequence1.txt` and `sequence2.txt` are in the working directory

---

## Testing Tips

### Level 0 Testing
Create custom sequence files for predictable block order:
```
I
J
L
O
S
T
Z
```

### Command Sequence Files
Test complex scenarios with command files:
```bash
# commands.txt
3right
clockwise
2down
drop
```

Run with:
```bash
sequence commands.txt
```

### Quick Test Commands
```bash
# Test in text mode with custom seed
./biquadris -text -seed 123

# Start at higher level with custom sequences
./biquadris -startlevel 3 -scriptfile1 test1.txt -scriptfile2 test2.txt
```

---

## Project Structure
```
A5-biquadris/
├── README.md
├── Makefile
├── sequence1.txt          # Level 0 blocks for player 1
├── sequence2.txt          # Level 0 blocks for player 2
├── *.cc                   # Source files
├── *.h                    # Header files
└── graphics_demo/         # X11 graphics example
    ├── README.txt
    ├── window.cc
    ├── window-impl.cc
    └── graphicsdemo.cc
```

## Authors
- Joshua Stein
- Taim Alsaadi
- Linh Tran

**Course**: CS 246 — Fall 2025  
**Assignment**: A5 - Biquadris (Group Project)
