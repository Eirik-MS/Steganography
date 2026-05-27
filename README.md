# PixlHide, a steganography tool
A practical implementation of Steganography

## Tasks and Requirements
The requirements for the project is translated and put into a markdown file [Practical Work Assignment](Docs/Practical_Work_Assignment_2026.md). In the [./Docs](Docs) folder you will find the documnetation from blackboard and original Spanish text for the work. 
**Due: June 8, 2026**


## Nesacary programs
* [GCC](https://gcc.gnu.org) or [Clang](https://releases.llvm.org/download.html) compiler 
* [MAKE](https://www.gnu.org/software/make/#download) make build system, migth go over to CMake if Windows compatibillity becomes a requirement.
* [Valgrind](https://valgrind.org/downloads/), Tool for cheking for memory leaks (Probably best to download from a package manager).  

Install on Ubuntu/Debian:
```bash
sudo apt install gcc make valgrind
```
Windows users should use [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install).


# Make and run program 

### Targets

To run this program you will need Make and gcc (or similar) compiler. 
To see avaliable compile targets use the command ```make```, and use ```make run``` to execute program rigth after compilation. ```make clean``` deleates all build-files.

```
Available targets:

  all          Build the program with debug symbols and verbose output (default)
  release      Build with optimizations (no debug symbols, no verbose) 
               Do make clean before this to remove old debug builds.
  run          Build and run the program with default arguments
  santest      Quick sanitizer run (fast, catches most memory + UB issues)
  memtest      Run with Valgrind to test for memmory leaks 
               (slower, but very thorough)
  roundtrip    Distribute then recover, to verify the round-trip works
  help         Show this help message

Override test arguments with ARGS="..."
  Example: make memtest ARGS="-r -secret out.bmp -k 2 -dir Images"
Add extra debug prints with CFLAGS+="-DVERBOSE_DEBUG" after a command
  Example: make clean
	       make run CFLAGS+="-DVERBOSE_DEBUG
```
### Flags and example runs
| Flag | Required | Description |
|------|----------|-------------|
| `-d` / `-r` | Yes | Distribute or Recover mode |
| `-secret` | Yes | Input image (distribute) or output path (recover) |
| `-k` | Yes | Minimum shadows needed to recover (2–10) |
| `-n` | No | Total shadows to create 
| `-dir` | No | Working directory to find/put images (defaults to current directory) |

Example commands for distribute and recovery of images
``` bash
pixlhide -d -secret Evassd.bmp -k 2 -n 3 -dir Images

pixlhide -r -secret Out.bmp -k 2 -dir Images/shadowes
```

# Documentation
I've Started adding doxygen style comments, but I dont think there is any need to acutually generate the docs. The comment type is just nice tooltips when hovering over functions in VS Code. 

## TODO List
A little list of things that remains to do ([TODO tree](https://marketplace.visualstudio.com/items?itemName=Gruntfuggly.todo-tree) can help finding TODO's left in the code): 

- [x] Parse arguments correctly and do error checking on them
- [x] Be able to read and parse bmp files
- [ ] Be able to write bmp files to disk
- [ ] Be able to distribute pictures
- [ ] Be able to recover imges