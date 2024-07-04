#include <stdio.h>
#include <ctype.h>

// Function to check if a character is a word delimiter
int isDelimiter(char ch) {
    return isspace(ch) || ch == '\0';
}

// Function to count words, lines, and characters
void countWordsLinesChars(FILE *file, int *wordCount, int *lineCount, int *charCount) {
    char ch;
    int inWord = 0;
    
    *wordCount = 0;
    *lineCount = 0;
    *charCount = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*charCount)++;

        if (ch == '\n') {
            (*lineCount)++;
        }

        if (isDelimiter(ch)) {
            if (inWord) {
                inWord = 0;
                (*wordCount)++;
            }
        } else {
            inWord = 1;
        }
    }

    // Account for the last word if the file doesn't end with a delimiter
    if (inWord) {
        (*wordCount)++;
    }

    // Account for the last line if the file doesn't end with a newline
    if (*charCount > 0 && ch != '\n' && ch != '\r') {
        (*lineCount)++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int wordCount, lineCount, charCount;
    countWordsLinesChars(file, &wordCount, &lineCount, &charCount);

    fclose(file);

    printf("Total words: %d\n", wordCount);
    printf("Total lines: %d\n", lineCount);
    printf("Total characters: %d\n", charCount);

    return 0;
}
