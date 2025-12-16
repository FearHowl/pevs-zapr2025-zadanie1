#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[100];
    char author[100];
    char genre[100];
    char start[11];
    char end[11];
    int score;
    char note[500];
}Book;

void listAllBooks_filter(int argc, char *argv[]) {
    char searchGenre[100] = "";
    char searchScore[10] = "";
    int filterReading = 0; 
    int filterFinished = 0;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--genre") == 0 && i + 1 < argc) {
            strcpy(searchGenre, argv[i+1]);
        }
        else if (strcmp(argv[i], "--score") == 0 && i + 1 < argc) {
            strcpy(searchScore, argv[i+1]);
        }
        else if (strcmp(argv[i], "--reading") == 0) {
            filterReading = 1;
        }
        else if (strcmp(argv[i], "--completed") == 0) {
            filterFinished = 1;
        }
    }
    
    FILE *file = fopen("reading_journal.txt", "r");
    if (file == NULL) {
        printf("List is empty or doesn't exist.\n");
        return;
    }

    char line[1024];

    printf("-----------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 

        if (strlen(searchGenre) > 0 && strstr(line, searchGenre) == NULL) continue;
        if (strlen(searchScore) > 0 && strstr(line, searchScore) == NULL) continue;

        if (filterReading == 1 || filterFinished == 1) {
            int pipes = 0;
            int isReading = 0;
                                                                 //toto som fakt netušil ako inak spraviť tak mi pomohlo AI no lebo už som to nedával. Napadlo ma to spraviť cez druhý pomocný súbor ale to som nevedel či sa môže tak som to dal takto aspoň
            for (int k = 0; line[k] != '\0'; k++) {
                if (line[k] == '|') pipes++;
                if (pipes == 4) {
                    if (line[k+1] == '|') isReading = 1; 
                    else isReading = 0;
                    break;
                }
            }

            if (filterReading == 1 && isReading == 0) continue;
            if (filterFinished == 1 && isReading == 1) continue;
        }

        printf("%s\n", line);
        printf("-----------------------------------------------------------------------------\n");
    }

    fclose(file);
}

void listAllBooks() {
    FILE *file = fopen("reading_journal.txt", "r");
    
    if (file == NULL) {
        printf("List is empty or doesn't exist.\n");
        return;
    }

    char line[1024];
    printf("-----------------------------------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    printf("-----------------------------------------------------------------------------------------------\n");
    }
    fclose(file);
}

void print_help(){
    printf("Help of program journal\nUsage:\n");
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("To add a new book:\n");
    printf("use ./journal new --name [] --author [] --genre [] --start [] --end [] --score [] -- note [] \n");
    printf("-----------------------------------------------------------------------------------------------\n");
}

int main(int argc, char* argv[]){
    if(argc <= 1) {
        print_help();
        return 0;
    }
    if (strcmp(argv[1], "--help") == 0) {
        print_help();
        return 0;
    }
    if (strcmp(argv[1], "new") == 0) {
        Book newBook;
        memset(&newBook, 0, sizeof(Book));
        // Aby scanf nehádzal random hodnoty
        strcpy(newBook.title, "");
        strcpy(newBook.author, "");
        strcpy(newBook.genre, "");
        strcpy(newBook.start, "");
        strcpy(newBook.end, "");
        strcpy(newBook.note, "");

        for (int i = 2; i < argc; i++) {
            
            if (strcmp(argv[i], "--name") == 0) {
                if (i + 1 < argc) { 
                    strcpy(newBook.title, argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--author") == 0) {
                if (i + 1 < argc) {
                    strcpy(newBook.author, argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--genre") == 0) {
                if (i + 1 < argc) {
                    strcpy(newBook.genre, argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--start") == 0) {
                if (i + 1 < argc) {
                    strcpy(newBook.start, argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--end") == 0) {
                if (i + 1 < argc) {
                    strcpy(newBook.end, argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--score") == 0) {
                if (i + 1 < argc) {
                    newBook.score = atoi(argv[i+1]);
                }
            }
            else if (strcmp(argv[i], "--note") == 0) {
                if (i + 1 < argc) {
                    strcpy(newBook.note, argv[i+1]);
                }
            }
        }
        FILE *file = fopen("reading_journal.txt", "a");
        if (file == NULL) {
        printf("Error: Could not open reading_journal.txt.\n");
        return 1;
    }

    fprintf(file, "%s|%s|%s|%s|%s|%d|%s\n", 
            newBook.title, 
            newBook.author, 
            newBook.genre,   
            newBook.start, 
            newBook.end,
            newBook.score,
            newBook.note);

    fclose(file);
    printf("Book '%s' saved successfully.\n", newBook.title);
    return 0;
    }
if (strcmp(argv[1], "list") == 0) { 
    if (argc == 2) {
            listAllBooks();
            return 0;
        }
    if (argc >= 3){
        listAllBooks_filter(argc, argv);
        return 0;
      }
}
    return 0;
}
