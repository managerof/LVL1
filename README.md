# Description

This project, **Unlocking Subconscious Thinking**, is a cognitive training tool designed to enhance the brain’s ability to solve problems subconsciously. The program presents a mental challenge in the morning and then evaluates later in the day to assess retention and subconscious processing of the solution.

## Features

- **Equation Generation**: Generates a new (addition, subtraction, multiplication or division) equation with random numbers based on the difficulty (number of digits).
- **State Management**: Saves and loads the current state of the program (equation, date, solved status) in a file (`app.dat`).
- **CLI Options**:
  - `-c`: Clears the state stored in `app.dat`.
  - `-d`: Deletes the `app.dat` file.
  - `-t OP:DIGITS`:  Create new task with operation OP and numbers with DIGITS digits
  
## Usage

### Without command-line arguments:

The program will load the state from `app.dat`, if available, and either:

1. If the previous task has been solved, it will prompt the user to set the operation and difficulty, and generate a new equation (e.g., `72 + 64 = ?`).  
   
   The user is meant to simply observe the equation and continue with their day without actively thinking about it. Later, at the end of the day, they will run the program again to provide the solution. If they answer correctly, it indicates that their subconscious mind solved the equation without conscious effort.

2. If an unsolved equation exists, the program will display it (e.g., `72 + 64 = ?`) and allow the user to solve it.

### With command-line arguments:

- To clear the state (set all values to zero):
  ./lvl1 -c

- To delete the `app.dat` file:
  ./lvl1 -d

- To specify the operation and the number of digits for the generated equation:
  ./lvl1 -t +:3

### Example
```
$ ./lvl1
28-02-2025
Welcome back!
Set difficulty (number of digits): 3
New equation for today: 971 + 436 = ?
```
---

## Files

- `app.dat`: Stores the current state of the program (equation, date, solved status).

---

## Requirements

- C Compiler (e.g., `gcc`)
- Make

## Compile

```
$ make
```

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
