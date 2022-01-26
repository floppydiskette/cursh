/*
 * cursh - the cursed shell
 * written by husky (floppydiskette) in 2022
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <raudio.h>
#include <dirent.h>

// constants
#define MAX_CHAR 1024
#define MAX_ARGS 64

// thingy to clear the screen
#define clear() printf("\033[H\033[J")
#define red() printf("\033[1;31m")
#define normal() printf("\033[0m")

// greeting
void init_shell() {
    clear();
    printf("\nCursh - the cursed shell :3 [Version 9.10.21]\n");
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
        normal();
        return;
    } else if (pid == 0) {
        if (execvp(pString[0], pString) < 0) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("please fucking end the pain oh god help fuck this hurts so much please stop it please stop the pain\n\n");
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
        normal();
        return;
    }
    pid1 = fork();
    if (pid1 == -1) {
        red();
        printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
        perror("jesus fucking christ this hurts so much please stop it please stop the pain\n\n");
        normal();
        return;
    } else if (pid1 == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        if (execvp(pString[0], pString) == -1) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("please this hurts so much please stop the pain\n\n");
            normal();
            exit(EXIT_FAILURE);
        }
    } else {
        pid2 = fork();
        if (pid2 == -1) {
            red();
            printf("\n\nSOMETHING WRONG HAPPENED\nPLEASE CONTACT billgate@realmicrosoft.com AND SEND THEM THE FOLLOWING ERROR MESSAGE:\n");
            perror("jesus christ please this hurts so much please stop it please stop the pain\n\n");
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
    } else if (strcmp(string, "dir") == 0) {
        return 27;
    } else if (strcmp(string, "cls") == 0) {
        return 27;
    } else if (strcmp(string, "pause") == 0) {
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
    printf("\nNOW AVAILABLE ON AMAZON.COM!\n\n");
}

void print_files(char *args) {
    printf("%s\n", args);
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
    } else if (strcmp(pString[0], "dir") == 0) {
        // if no args, call print_files with empty string
        if (pString[1] == NULL) {
            print_files("");
        } else {
            fix_slashes(pString);
            print_files(pString[1]);
        }
    } else if (strcmp(pString[0], "cls") == 0) {
        printf("\n\nCLEARING THE SCREEN, PLEASE WAIT...\n\n");
        sleep(20);
        clear();
    } else if (strcmp(pString[0], "pause") == 0) {
        // wait for user to press enter
        printf("\n\nPRESS ENTER TO CONTINUE\n\n");
        getchar();
    } else {
        return 0;
    }
    return 1;
}

void parse_args(char *input, char **parsed_args) {
    char *pch = strtok(input, " ");
    int i = 0;
    while (pch != NULL) {
        parsed_args[i] = pch;
        pch = strtok(NULL, " ");
        i++;
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


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
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
        // -2: user put in a forward slash ):<
        // -1: invalid input
        // 0 - normal command
        // 1 - builtin command
        // 2 - pipe command

        if (cmd_type == -1) {
            printf("INCORRECT INPUT PROVIDED\nASSUMING YOU ACCIDENTALLY HIT RETURN\nSLEEPING FOR 10 SECONDS TO PREVENT ACCIDENTAL INPUT\n");
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
            printf("\n");
            printf("YOU HAVE BEEN SENT TO TIMEOUT FOR 30 SECONDS.\n");
            normal();
            sleep(30);
            continue;
        }
    }
    return 0;
}

#pragma clang diagnostic pop