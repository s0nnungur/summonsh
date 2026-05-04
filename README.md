# summonsh

A Unix shell interpreter written in C, built incrementally across OS lab sessions at UBI.

## Build & Run

```bash
make
./soshell
```

## Features

- Command execution (foreground & background with `&`)
- I/O redirection: `<`, `>`, `>>`, `2>`
- Single pipes: `cmd1 | cmd2`, including `cmd1 < f | cmd2 > out`
- Built-ins: `sair`, `cd`, `obterinfo`, `quemsoueu`, `PS1=` (with `\h`)
- Built-ins: `socp`, `calc`, `bits`, `epsilon`, `displayBitOps`
- Built-ins: `openfile`, `closefd`, `readfd`, `fileinfo`, `isValid`, `isjpeg`, `isgif`

## Files

| File | Role |
|---|---|
| `main.c` | Main loop, built-ins |
| `parse.c` | Tokeniser |
| `execute.c` | fork/exec, pipes, bg/fg |
| `redirects.c` | `dup2`-based I/O redirection |
| `socp.c` | Low-level file copy |
| `calc.c` | Arithmetic + bitwise built-ins |
| `bitops.c` | Binary/hex display helpers |
| `files.c` | File descriptor built-ins, magic number detection |
| `shell.h` | Shared prototypes and constants |

## Course

Sistemas Operativos — Universidade da Beira Interior, 2026