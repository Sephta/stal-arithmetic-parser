# Simple Arithmetic Parser

### Seth Tal

### 07.31.2021

---

Rudimentary arithmetic parser executable on the command line. Built with C++11 using standard libraries. Calculates simple arithmetic expressions of the form:

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

### Requirements

* Ubuntu 20.04.1 LTS
  * or Windows Subsystem for Linux (WSL) running Ubuntu 20.04.1 LTS
* g++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0
* GNU Make 4.2.1

### Step 1: Download and Extract the contents from the .ZIP file

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

### Step 2

Using the makefiles provided you can make the project which will produce the executable, `parser`, inside the `src` directory.

```sh
# Navigate to the root directory of the project and simply perform the following command:

make

# This will build the linux executable 'parser' inside the ./src directory
```

### Step 3

You can either navigate into the `src` directory or simply run the program from root like so:

```sh
# Expression should be enclosed in quotes

./src/parser -s "Expression to Parse"

# Or you can use a .txt file to parse multiple expressions...

./src/parser -f ./test.txt
```

#### Note about file input

The contents of the test file should like like the following:

```txt
1 + 1
(3 + 4) * 6
(1 * 4) + (5 * 2)
```

Where each expression is seperated onto its own line in the file.
