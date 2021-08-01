# Simple Arithmetic Parser

### Seth Tal

### 07.31.2021

---

Rudimentary command line arithmetic parser. Calculates simple arithmetic expressions of the form:

* *EXPRESSION* : `(2 + 2) | (3 * 7) | (4 / 2) | (5 - 2)`
* *VALUE* : `NUMBER` (i.e. within the set of integers)
* *OPERATION* : `3 + 9` (i.e. Expression without parenthesis)

All of which can be chained together.

```sh
# This will evaluate to -> 9
./parser -s "1 + (4 * 10) / (7 - 2)"
```

## How to Compile and Run

This program was made using Windows Subsystem for Linux in a Ubuntu 20.04.1 LTS install. This program was written and compiled using the following flags:

```sh
-g -W -Wall -std=c++11
```

### Step 1. Download and Extract the contents from the .ZIP file

```sh
# File Structure
.
├── _.vscode
│   ├── settings.json
├── _src
│   ├── main.cpp
│   ├── Makefile
│   ├── parser.cpp
│   └── parser.h
├── .gitignore
├── clean.sh
├── LICENSE
├── Makefile
├── README.md
└── test.txt
```
