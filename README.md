# summonsh

A minimal Unix shell built from scratch in C.

## Build

```
make
./soshell
```

## Features

- Execute external commands via `fork()`/`execvp()`
- Built-in commands: `sair`, `cd`, `obterinfo`, `quemsoueu`, `socp`
- Custom prompt with `PS1=` (supports `\h` for hostname)
- Background execution with `&`
- I/O redirection: `<`, `>`, `>>`, `2>`
- File copy with low-level I/O (`socp src dst`)

## Files

| File | Purpose |
|------|---------|
| `shell.h` | Headers and prototypes |
| `main.c` | Main loop + built-in commands |
| `parse.c` | Tokenizer |
| `execute.c` | fork/exec + background |
| `redirects.c` | I/O redirection |
| `socp.c` | Built-in file copy |
| `Makefile` | Build rules |

## Clean

```
make clean
```