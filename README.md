# Description

This project, **Unlocking Subconscious Thinking**, is a cognitive training tool designed to enhance the brain’s ability to solve problems subconsciously. The program presents a mental challenge in the morning and then evaluates later in the day to assess retention and subconscious processing of the solution.

## Features

- **Equation Generation**: Generates a new addition equation with random numbers based on the difficulty (number of digits).
- **State Management**: Saves and loads the current state of the program (equation, date, solved status) in a file (`app.dat`).
- **CLI Options**:
  - `-c`: Clears the state stored in `app.dat`.
  - `-d`: Deletes the `app.dat` file.
  - `-n NUMBER`: Allows setting the difficulty level (number of digits) for the equation (currently not fully implemented in CLI).
  
## Usage

### Without command-line arguments:

1. The program will load the state from `app.dat`, if available, and either:
   - Present a new equation if the previous one has been solved.
   - Ask the user to solve the current equation if it hasn’t been solved.

2. The user will be prompted to solve the equation (e.g., `a + b = ?`).

3. After solving the equation correctly, the state is saved and a new equation is generated for the following day.

### With command-line arguments:

- To clear the state (set all values to zero):
  ./lvl1 -c

- To delete the `app.dat` file:
  ./lvl1 -d

- To specify the number of digits for the generated equation (not yet fully implemented):
  ./lvl1 -n 3

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

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
