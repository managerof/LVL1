#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

#define STORAGE_FILENAME "app.dat"

/* Structure to hold an equation (a + b = c) */
typedef struct
{
    int a;
    int b;
    int c;
    char operation;
} equation_t;

/* Structure to store a date */
typedef struct 
{
    int year;
    int month;
    int day;
} date_t;

/* Structure to maintain program state */
typedef struct
{
    equation_t eq;
    date_t     date;
    int        solved;
} state_t;

/* Function to get today's date */
void get_today_date(date_t *today)
{
    time_t t;
    struct tm tm;

    t = time(NULL);
    tm = *localtime(&t);

    today->year = tm.tm_year + 1900;
    today->month = tm.tm_mon + 1;
    today->day = tm.tm_mday;
}

/* Function to check if a given date is today */
int is_today(date_t date)
{
    date_t today;
    get_today_date(&today);

    return (date.day == today.day &&
            date.month == today.month &&
            date.year == today.year);
}

/* Function for safe user input */
void myinput(const char *input_format, void *buffer)
{
    while (scanf(input_format, buffer) != 1)
    {
        while (getchar() != '\n');  /* Clear input buffer */
        printf("Invalid input! Try again: ");
    }
}

/* Load previous state from file */
void load_state(state_t *state)
{
    FILE *file;
    
    file = fopen(STORAGE_FILENAME, "r");
    if (file == NULL)
    {
        printf("No previous state found. Starting fresh.\n");
        state->solved = 0;
        state->eq.a = 0;
        state->eq.b = 0;
        state->eq.c = 0;
        state->eq.operation = 0;
        state->date.year = 0;
        state->date.month = 0;
        state->date.day = 0;
        return;
    }

    fread(state, sizeof(state_t), 1, file);
    fclose(file);
}

/* Save the current state to file */
void save_state(state_t *state)
{
    FILE *file;
    get_today_date(&state->date);

    file = fopen(STORAGE_FILENAME, "w");
    if (file == NULL)
    {
        printf("Error opening file for writing!\n");
        exit(1);
    }

    fwrite(state, sizeof(state_t), 1, file);
    fclose(file);
}

int is_valid_operation(char op)
{
    switch (op)
    {
        case '+':
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '*':
            return 1;
            break;
        case '/':
            return 1;
            break;
        default:
            return 0;
    }
}

char input_operation()
{
    char operation;
    int  is_valid;

    /* Prompt until a valid operation (+ or -) is provided */
    while (1) {
        printf("Choose arithmetic operation (+, -, *, /): ");
        myinput(" %c", &operation); /* The space before %c is to skip any whitespace */
        
        is_valid = is_valid_operation(operation);

        if (is_valid)
        {
            return operation;
        }

        printf("Invalid operation. Please enter ('+', '-', '*', '/').\n");
    };
}

int input_difficulty()
{
    int difficulty;

    /* Prompt until a valid difficulty (number of digits, minimum 1) is provided */
    do {
        printf("Set difficulty (number of digits, must be >= 1): ");
        myinput("%d", &difficulty);
        if (difficulty < 1) {
            printf("Difficulty must be at least 1 digit.\n");
        }
    } while (difficulty < 1);

    return difficulty;
}

void handle_operation(equation_t* eq)
{
    switch (eq->operation)
    {
        case '+':
            eq->c = eq->a + eq->b;
            break;
        case '-':
            eq->c = eq->a - eq->b;
            break;
        case '*':
            eq->c = eq->a * eq->b;
            break;
        case '/':
            eq->c = eq->a / eq->b;
            break;
        default:
            exit(1);
    }
}

/* Generate a new equation based on difficulty and operation preferences */
void new_task(state_t *state)
{
    char operation;
    int difficulty, mod, iter;
    equation_t new_eq;

    operation  = input_operation();
    difficulty = input_difficulty();

    /* Compute modulus based on difficulty (e.g., difficulty 3 => mod = 1000) */
    mod = 1;
    for (iter = 0; iter < difficulty; iter++)
    {
        mod *= 10;
    }

    /* Seed the random number generator (ideally do this once in your program) */
    srand(time(NULL));

    /* Generate random operands within the computed range */
    new_eq.a = rand() % mod;
    new_eq.b = rand() % mod;
    new_eq.operation = operation;

    /* Compute the result based on the selected operation */
    handle_operation(&new_eq);

    /* Update state and save the new equation */
    state->eq = new_eq;
    state->solved = 0;
    save_state(state);

    /* Display the new equation (using new_eq.operation for clarity) */
    printf("New equation for today: %d %c %d = ?\n", new_eq.a, new_eq.operation, new_eq.b);
}

/* Function to attempt solving the equation */
void attempt_task(state_t *state)
{
    int input = -1;
    int attempts = 4;

    while (input != state->eq.c && attempts > 0) 
    {
        printf("%d %c %d = ", state->eq.a, state->eq.operation, state->eq.b);
        myinput("%d", &input);
    
        if (input == state->eq.c) 
        {
            printf("Correct!\n");
            state->solved = 1;
            save_state(state);
            break;
        }
        else 
        {
            printf("WRONG! Try again\n");
        }

        attempts--;
    }
}

/* Function to zero out a file */
void zero_file(const char *filename, size_t size)
{
    FILE *file;
    char buffer[8];
    size_t iter, remaining;

    file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    memset(buffer, 0, sizeof(buffer));
    remaining = size;

    for (iter = 0; iter < (remaining / sizeof(buffer)); iter++)
    {
        fwrite(buffer, sizeof(buffer), 1, file);
    }

    fwrite(buffer, 1, remaining % sizeof(buffer), file);
    fclose(file);
}

void new_addition_task(state_t *state, char operation, int digits)
{
    int difficulty, mod, iter;
    equation_t new_eq;

    operation  = operation;
    difficulty = digits;

    /* Compute modulus based on difficulty (e.g., difficulty 3 => mod = 1000) */
    mod = 1;
    for (iter = 0; iter < difficulty; iter++)
    {
        mod *= 10;
    }

    /* Seed the random number generator (ideally do this once in your program) */
    srand(time(NULL));

    /* Generate random operands within the computed range */
    new_eq.a = rand() % mod;
    new_eq.b = rand() % mod;
    new_eq.operation = operation;

    /* Compute the result based on the selected operation */
    handle_operation(&new_eq);

    /* Update state and save the new equation */
    state->eq = new_eq;
    state->solved = 0;

    save_state(state);
}
/* Handle command-line arguments */
void handle_cli(int argc, char *argv[])
{
    int opt;
    char *task_arg = NULL;
    char operation;
    int digits = 0;
    
    while ((opt = getopt(argc, argv, "hcdt:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                printf("Usage: %s [-c] [-d] [-t operation:digits]\n", argv[0]);
                printf("Options:\n");
                printf("    -c            Zero \"%s\" file\n", STORAGE_FILENAME);
                printf("    -d            Delete \"%s\" file\n", STORAGE_FILENAME);
                printf("    -t OP:DIGITS  Create new task with operation OP and numbers with DIGITS digits\n");
                break;
            case 'c':
                zero_file(STORAGE_FILENAME, sizeof(state_t));
                break;
            case 'd':
                if (remove(STORAGE_FILENAME) == 0)
                    printf("Deleted file: %s\n", STORAGE_FILENAME);
                else
                    printf("Error deleting file: %s\n", STORAGE_FILENAME);
                break;
            case 't':
                task_arg = optarg;
                if (sscanf(task_arg, "%c:%d", &operation, &digits) == 2)
                {
                    state_t state;
                    new_addition_task(&state, operation, digits);
                }
                else
                {
                    fprintf(stderr, "Invalid format for -t. Use: operation:digits (e.g., +:3)\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c!\n", optopt);
                break;
            default:
                fprintf(stderr, "Usage: %s [-c] [-d] [-t OP:DIGITS]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }


}

/* Main function */
int main(int argc, char *argv[]) 
{
    state_t state;

    if (argc > 1)
    {
        handle_cli(argc, argv);
        return 0;
    }

    load_state(&state);

    printf("%02d-%02d-%04d\n", state.date.day, state.date.month, state.date.year);
    printf("Welcome back!\n");

    if (state.solved)
    {
        new_task(&state);
    } 
    else
    {
        attempt_task(&state);
    }

    return 0;
}