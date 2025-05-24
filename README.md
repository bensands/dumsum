# `dumsum` – a simple sum of bytes

`dumsum` will compute for you the dumbest possible checksum: a sum of all bytes mod 256 (or 2^16, or 2^32, if you like).

---

## Example Usage

```bash
# Compute an 8-bit hex checksum (default)
./dumsum file.txt

# 16-bit checksum in decimal
./dumsum -b 16 -d file.txt

# Process multiple files, show filenames
./dumsum -v file1.txt file2.txt

# Read from stdin (e.g. piped input)
cat file.txt | ./dumsum

# Handle a file starting with '-'
./dumsum -- -weird.txt
```

---

## Options

| Option                | Description                                   |
|-----------------------|-----------------------------------------------|
| `-v`, `--verbose`     | Show file names in output                     |
| `-d`, `--decimal`     | Print checksum in decimal format              |
| `-b`, `--bits <n>`    | Bit width: must be 8, 16, or 32 (default: 8)  |
| `-h`, `--help`        | Display usage help and exit                   |
| `[files...]`          | One or more files to process (or stdin)       |

---

## Compilation

Use the provided makefile.

```bash
make
```

---

## 📝 Notes

- Use `--` before filenames that begin with `-`, to prevent them being interpreted as options.
- If no files are specified, `dumsum` reads from standard input.

---

## 📄 License

Apache License, Version 2.0

