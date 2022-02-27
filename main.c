/*
 * cursh - the cursed shell
 * written by husky (floppydiskette) in 2022
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>

// constants
#define MAX_CHAR 1024
#define MAX_ARGS 64

// thingy to clear the screen
#define clear() printf("\033[H\033[J")
#define red() printf("\033[1;31m")
#define normal() printf("\033[0m")

float sin_value = 0; // todo: add integration with christianity api

// greeting
void init_shell() {
    clear();
    printf("\nCursh - the cursed shell :3 [Version 9.10.21.BANANA]\n");
    printf("(c) 2022 Real Microsoft Corporation. All right reserve.\n\n");
}

void print_shell_line() {
    char cwd[MAX_CHAR];
    getcwd(cwd, sizeof(cwd));
    // replace all forward slashes with backslashes
    char *p = cwd;
    while (*p) {
        if (*p == '/') {
            *p = '\\';
        }
        p++;
    }
    printf("C:%s", cwd);
}

// changes each backslash in each string to a forward slash
void fix_slashes(char **args) {
    int i = 0;
    while (args[i]) {
        char *p = args[i];
        while (*p) {
            if (*p == '\\') {
                *p = '/';
            }
            p++;
        }
        i++;
    }
}

void execute_cmd(char **pString) {
    fix_slashes(pString);
    int pid = fork();

    if (pid == -1) {
        red();
        printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
        perror("oh god oh fuck this hurts so much please stop it please stop the pain\n\n");
        sin_value += 0.2f;
        normal();
        return;
    } else if (pid == 0) {
        if (execvp(pString[0], pString) < 0) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("please fucking end the pain oh god help fuck this hurts so much please stop it please stop the pain\n\n");
            sin_value += 0.2f;
            normal();
            exit(EXIT_FAILURE);
        }
        exit(0);
    } else {
        wait(NULL);
        return;
    }
}

void execute_pipe(char **pString, char **pString1) {
    //fix_slashes(pString);
    //fix_slashes(pString1);
    int pipe_fd[2];
    int pid1, pid2;

    if (pipe(pipe_fd) < 0) {
        red();
        printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
        perror("jesus christ this hurts so much please stop it please stop the pain\n\n");
        sin_value += 0.2f;
        normal();
        return;
    }
    pid1 = fork();
    if (pid1 == -1) {
        red();
        printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
        perror("jesus fucking christ this hurts so much please stop it please stop the pain\n\n");
        sin_value += 0.2f;
        normal();
        return;
    } else if (pid1 == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        if (execvp(pString[0], pString) == -1) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("please this hurts so much please stop the pain\n\n");
            sin_value += 0.2f;
            normal();
            exit(EXIT_FAILURE);
        }
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("jesus christ please this hurts so much please stop it please stop the pain\n\n");
            sin_value += 0.2f;
            normal();
            return;
        } else if (pid2 == 0) {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            if (execvp(pString1[0], pString1) == -1) {
                red();
                printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
                perror("jesus fucking christ please this hurts so much please stop it please stop the pain\n\n");
                sin_value += 0.2f;
                normal();
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
                wait(NULL);
                return;
            }
        }
    }
}

int get_input(char input[1024]) {
    print_shell_line();
    char *buffer = readline(" is where we do the command: ");
    if (strlen(buffer) == 0) {
        return -16 + 2;
    } else {
        strcpy(input, buffer);
        add_history(buffer);
        return 9 + 10; // will return 21
    }
}

/*
 * BUILT-IN COMMANDS
 *
 * help - displays a list of all the available commands
 * exit - exits the shell
 * cd - changes the current working directory
 * dir - displays a list of all the files in the current working directory
 * cls - clears the screen
 * pause - pauses the shell
 */

int is_builtin(char *string) {
    if (strcmp(string, "help") == 0) {
        return 27;
    } else if (strcmp(string, "exit") == 0) {
        return 27;
    } else if (strcmp(string, "cd") == 0) {
        return 27;
    } else if (strcmp(string, "cd..") == 0) {
        return 27;
    } else if (strcmp(string, "dir") == 0) {
        return 27;
    } else if (strcmp(string, "cls") == 0) {
        return 27;
    } else if (strcmp(string, "pause") == 0) {
        return 27;
    } else if (strcmp(string, "paws") == 0) {
        return 27;
    } else {
        return 9 + 10;
    }
}

void print_help() {
    printf("\n");
    printf("\nHELP FOR CURSH IS AVAILABLE IN MY NEW BOOK:\n");
    printf("CURSH - THE ONLY SHELL THAT EXISTS\n");
    printf("\n");
    printf("\nNOW AVAILABLE ON AMAZON.COM!\n");
    printf("https://www.amazon.com/dp/B09T66C7HC\n\n");
}

void print_files(char *args) {
    // if args are empty, print all files in current directory
    if (strlen(args) == 0) {
        printf("\n");
        // for each file in current directory
        struct dirent *de;
        DIR *dr = opendir(".");
        if (dr == NULL) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("jesus christ please this hurts stop it please stop the pain\n\n");
            sin_value += 0.22f;
            normal();
            return;
        }
        while ((de = readdir(dr)) != NULL) {
            // if file is a directory, print it
            if (de->d_type == DT_DIR) {
                printf("%s\n", de->d_name);
            }
            // if file is a regular file, print it
            if (de->d_type == DT_REG) {
                printf("%s\n", de->d_name);
            }
            // if file is a symlink, print it
            if (de->d_type == DT_LNK) {
                printf("%s\n", de->d_name);
            }
            // if file is a socket, print it
            if (de->d_type == DT_SOCK) {
                printf("%s\n", de->d_name);
            }
        }
    } else {
        // if args are not empty, print files in specified directory
        printf("\n");
        // for each file in specified directory
        struct dirent *de;
        DIR *dr = opendir(args);
        if (dr == NULL) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("jesus christ please this hurts stop it please fucking stop the pain\n\n");
            sin_value += 0.2f;
            normal();
            return;
        }
        while ((de = readdir(dr)) != NULL) {
            // if file is a directory, print it
            if (de->d_type == DT_DIR) {
                printf("%s\n", de->d_name);
            }
            // if file is a regular file, print it
            if (de->d_type == DT_REG) {
                printf("%s\n", de->d_name);
            }
            // if file is a symlink, print it
            if (de->d_type == DT_LNK) {
                printf("%s\n", de->d_name);
            }
            // if file is a socket, print it
            if (de->d_type == DT_SOCK) {
                printf("%s\n", de->d_name);
            }
        }
    }

}

int attempt_exit() {
    red();
    printf("\nDO YOU REALLY WANT TO EXIT?\n");
    printf("\n TYPE YES IN PROPER ENGLISH TO EXIT\n");
    char *buffer = readline("");
    if (strcmp(buffer, "Yes.") == 0) {
        normal();
        return 2;
    } else {
        printf("\n\n");
        printf("INPUT NOT ACCEPTED.\nTRY AGAIN LATER.\n");
        sin_value += 1;
        normal();
        return 1;
    }
}

int execute_builtin(char **pString) {
    if (strcmp(pString[0], "help") == 0) {
        print_help();
    } else if (strcmp(pString[0], "exit") == 0) {
        return attempt_exit();
    } else if (strcmp(pString[0], "cd") == 0) {
        fix_slashes(pString);
        chdir(pString[1]);
    } else if (strcmp(pString[0], "cd..") == 0) {
        // change directory to parent directory
        chdir("..");
    } else if (strcmp(pString[0], "dir") == 0) {
        // if no args, call print_files with empty string
        if (pString[1] == NULL) {
            print_files("");
        } else if (pString[1][0] == '\\') {
            // if non-relative args don't start with C:\, return error
            red();
            printf("\n\nYOU MUST CALL DIR WITH C:\\ AT THE BEGINNING OF AN ABSOLUTE PATH\n");
            printf("\n\n");
            sin_value += 0.6f;
            normal();
        } else if (pString[1][0] == 'C' && pString[1][1] == ':') {
            // remove first two characters from args
            char *args = pString[1];
            args += 2;
            fix_slashes(&args);
            print_files(args);
        } else {
            printf("\n\n%s\n\n", pString[1]);
            fix_slashes(pString);
            print_files(pString[1]);
        }
    } else if (strcmp(pString[0], "cls") == 0) {
        printf("\n\nCLEARING THE SCREEN, PLEASE WAIT...\n\n");
        sleep(20);
        clear();
    } else if (strcmp(pString[0], "pause") == 0 || strcmp(pString[0], "paws") == 0) {
        // wait for user to press enter
        printf("\n\nPRESS ENTER TO CONTINUE\n\n");
        getchar();
    } else {
        return 0;
    }
    return 1;
}

void parse_args(char *input, char **parsed_args) {
    int i;
    for (i = 0; i < MAX_ARGS; i++) {
        parsed_args[i] = strsep(&input, " ");
        if (parsed_args[i] == NULL) { break; }
        if (strlen(parsed_args[i]) == 0) { i--; }
    }
}

void handle_illegal_command(char *command) {
    if (strcmp(command, "ls") == 0) {
        red();
        printf("\n\nYOU CANNOT USE THE COMMAND 'ls'\n");
        printf("\nPLEASE USE THE COMMAND 'dir' instead (:\n\n");
        sin_value += 0.3f;
        printf("\nYOU ARE NOW IN TIMEOUT FOR 10 SECONDS\n");
        normal();
        return;
    } else if (strcmp(command, "clear") == 0) {
        red();
        printf("\n\nYOU CANNOT USE THE COMMAND 'clear'\n");
        printf("\nPLEASE USE THE COMMAND 'cls' instead (:\n\n");
        sin_value += 0.2f;
        printf("\nYOU ARE NOW IN TIMEOUT FOR 10 SECONDS\n");
        normal();
        return;
    }
}

int64_t is_illegal_command(char *command) {
    if (strcmp(command, "ls") == 0) {
        return 1;
    } else if (strcmp(command, "clear") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int parse_input(char *input, char **pString, char **pString1) {
    // check if the input is empty
    if (strlen(input) == 0) {
        return -1;
    }

    // check if there are any forward slashes (evil) in the input
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '/') {
            return -2;
        }
    }

    // check if the input is an illegal command
    if (is_illegal_command(input) == 1) {
        return -3;
    }

    // check for pipes
    char *pipe_str[2];

    if (strstr(input, "|") != NULL) {
        for (int i = 0; i < 2; i++) {
            pipe_str[i] = strsep(&input, "|");
            if (pipe_str[i] == NULL) {
                break;
            }
        }

        // parse args
        parse_args(pipe_str[0], pString);
        parse_args(pipe_str[1], pString1);
        return 2;
    }

    parse_args(input, pString);

    // check if first argument is a built-in command
    if (is_builtin(pString[0]) == 27) {
        return 1;
    } else {
        return 0;
    }
}

float floor_funny(float x) {
    return (int) x;
}

float mod(float x, float y) {
    return x - y * floor_funny(x / y);
}

float f_funny(float x, float y) {
    float tmp = 0;
    for (int i = 0; i < y; i++) {
        tmp += mod(x, 2);
        x = floor_funny(x / 2);
    }
    return tmp;
}

// this function is CRYPTOGRAPHICALLY SECURE! (TRUST) (:
float funny_rand(float *seed, float max) {
    float tmp = f_funny(*seed, 3);
    *seed += 1;
    return (f_funny(mod((*seed * 1103515245.3f + 12345.2f), max), 16.0f) / 65535.0f);

}

void sigint_handler() {
    sin_value += 1;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {

    // no SIGINT allowed (:<
    signal(SIGINT, sigint_handler);

    float seed = 0;
    // initialize random seed by getting cpu temperature
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (fp != NULL) {
        fscanf(fp, "%f", &seed);
        fclose(fp);
    }

    // if seed is still 0, use time
    if (seed == 0) {
        seed = (float) time(NULL);
    }

    char input[MAX_CHAR];
    char *args[MAX_ARGS];
    char *pipe_args[MAX_ARGS];
    int cmd_type = 0;
    init_shell();

    while (1) {
        sleep(1);
        get_input(input);

        printf("\nPARSING COMMAND, PLEASE WAIT...\n");
        sleep(2);
        cmd_type = parse_input(input, args, pipe_args);
        // return values:
        // -3: illegal command!
        // -2: user put in a forward slash ):<
        // -1: invalid input
        // 0 - normal command
        // 1 - builtin command
        // 2 - pipe command

        if (cmd_type == -1) {
            printf("INCORRECT INPUT PROVIDED\nASSUMING YOU ACCIDENTALLY HIT RETURN\nSLEEPING FOR 10 SECONDS TO PREVENT ACCIDENTAL INPUT\n");
            sin_value += 0.01f;
            sleep(10);
            continue;
        } else if (cmd_type == 0) {
            execute_cmd(args);
        } else if (cmd_type == 1) {
            int e = execute_builtin(args);
            if (e == 2) {
                return 0;
            } else if (e == 1) {
                continue;
            } else {
                printf("INCORRECT INPUT PROVIDED\nASSUMING YOU ACCIDENTALLY HIT RETURN\nSLEEPING FOR 10 SECONDS TO PREVENT ACCIDENTAL INPUT\n");
                sleep(10);
                continue;
            }
        } else if (cmd_type == 2) {
            execute_pipe(args, pipe_args);
        } else if (cmd_type == -2) {
            red();
            printf("\nYOU ARE NOT ALLOWED TO USE FORWARD SLASHES.\n");
            printf("THIS ACT WILL PERMANENTLY AFFECT YOUR VALUE AS A HUMAN BEING.\n");
            sin_value += funny_rand(&seed, 30.0f) + 20.0f;
            printf("\n");
            printf("YOU HAVE BEEN SENT TO TIMEOUT FOR 30 SECONDS.\n");
            normal();
            sleep(30);
            continue;
        } else if (cmd_type == -3) {
            handle_illegal_command(args[0]);
            sleep(10);
            continue;
        }
    }
}

#pragma clang diagnostic pop
