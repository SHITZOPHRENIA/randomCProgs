// ----------------------------------------------------------;
// pRandTxLinePick.c
// FROM: https://github.com/SHITZOPHRENIA/randomCProgs/
// Created by SHITZO ( https://github.com/SHITZOPHRENIA/ )
// .
// DESCRIPTION:
// Picks a 'Pseudo(!!!)' ""Random"" line from a text file
// -specified by argv[1].
// .
// .
// ----------------------------------------------------------;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define IDEA_STR_BUF 200
#define MAX_IDEA_STRS 400

int main(int argc, char* argv[]) {
    // check the 1st arg for file path
    if (argc < 2) {
        // no file arg given
        printf("please specify the idea list text files path!\n");
        return 0;
    }
    // ""else {}"" arg is > 2, so assing argv[1] as FILE_NAME for f
    // get ideaListFile with FILE_NAME
    FILE* f = fopen(argv[1], "r");
    const int F__MIN_LINES = 0;

    // check if f is valid
    if (f == NULL) {
        printf("ERROR: could not open file: %s\n", argv[1]);
        perror("ERRNO");
        return -1;
    }

    // get all strings in the file with fgets()
    // then append those to 2D array 'ideaStrArr'
    int indx = 0;
    char ideaStrArr[MAX_IDEA_STRS][IDEA_STR_BUF];
    char* eofCheck = (char *)' '; // checks for EOF condition.
    while (eofCheck != NULL) {
        eofCheck = fgets(ideaStrArr[indx], (IDEA_STR_BUF - 1), f);
        indx++;
    }
    fclose(f); // NO MORE FILE OPERTIONS

    // set f's max line count
    const int F__MAX_LINES = (indx - 2); // subtract 1 to get an array index compatiple int.

    // get a PSEUDO(!!!) ""random"" int and assing it to RAND_IDEA_INDX
    srand(time(NULL));
    const int RAND_IDEA_INDX = (rand() % (F__MAX_LINES + 1 - F__MIN_LINES) + F__MIN_LINES);

    // get idea corresponding to int RAND_IDEA_INDX
    printf("%d : %s\n", (RAND_IDEA_INDX + 1), ideaStrArr[RAND_IDEA_INDX]);


    return 0;

}
