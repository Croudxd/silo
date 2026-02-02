# silo

An easier way to move files using buffers.

https://github.com/user-attachments/assets/bf6e85ed-b7d6-4dd0-9e1e-7143eb80dd85

This program might contain bugs as its in active development.

I want to be able to integrate this into yazi and neovim. For now its just a CLI command.

## To build

``` 
git clone https://github.com/Croudxd/silo.git
cd silo && mkdir build
cd build && cmake .. && make -j
```

## To use

To use simple type in shell:
```
silo stash (s) <buffer> <path>    Push a file into a buffer
silo pop (p) <buffer> [file...]   Restore all files, or specific ones
silo list [buffer]                List all buffers or files in a buffer
silo help                         Show this message
```
