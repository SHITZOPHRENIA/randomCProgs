// ----------------------------------------------------------;
// h_massLossTracker.c
// FROM: https://github.com/SHITZOPHRENIA/randomCProgs/
// Created by SHITZO ( https://github.com/SHITZOPHRENIA/ )
// .
// DESCRIPTION:
// Takes weight as input and writes it to a txt file.
// SUPPORTS:
//  KG and LB.
//  Weight up to %.1f
// .
// FUTURE PLANNED FEATURES:
// .
//  PRINT OUT TOTAL WEIGHT LOSS
//      ABOVE BUT WITH SPECIFIED STARTING AND ENDING DATES
//  CONVERT POUNDS TO KG AND VICE VERSA
// .
// .
// ----------------------------------------------------------;

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// IMPORTANT ARGS
#define STR_HELP_ARG "h"
#define CH_HELP_ARG 'h'

// UNIT ARGS
#define STR_KG_ARG "k"
#define CH_KG_ARG 'k'
#define STR_POUND_ARG "p"
#define CH_POUND_ARG 'p'



const char* HELP_MSG =  "\n"
                        "MASS LOSS TRACKER - HELP:\n"
                        "\n"
                        "\n"
                        "IMPORTANT:\n"
                        "\n"
                        "-"STR_HELP_ARG"    DISPLAYS HELP.\n"
                        "\n"
                        "\n"
                        "UNIT:\n"
                        "\n"
                        "-"STR_KG_ARG"    STORES GIVEN NUMBER AS KG/KILOGRAMS // DEFAULT BEHAVIOUR IF NO ARGUMENTS ARE GIVEN!!!\n"
                        "-"STR_POUND_ARG"    STORES GIVEN NUMBER AS LB/POUNDS\n"
                        "\n"
                        "\n"
                        "";

typedef enum {
    KILO,
    POUND
} Unit;


void StrToFloat(char* s, float* f) {
    errno = 0;

    char* endptr [25];
    *f = strtof(s, endptr);

    if (*f == 0 && endptr[0][0] != '0') { // fuck c style string shenanigans btw (or i have a serious skill issue)
        printf("incorrect argument 2nd: \'%s\' \n", s);
        exit(-1);
    }

    if (errno == ERANGE) {
        printf("WARNING: 2nd argument: \'%s\' WILL overflow OR underflow!\n", s);
        printf("Either you are FAT AF, you don't exist OR you have managed to gain negative weight(\?\?\?)\n");
        printf("Continuing execution...\n");
    }

}

char* getWDayStr(int wDIndx) {
    switch (wDIndx) {
        case 0:
            return "Mon";
            break;
        case 1:
            return "Tue";
            break;
        case 2:
            return "Wed";
            break;
        case 3:
            return "Thu";
            break;
        case 4:
            return "Fri";
            break;
        case 5:
            return "Sat";
            break;
        case 6:
            return "Sun";
            break;
        default:
            return "Unknown";
            break;

}

}


int main(int argc, char* argv[]) {
    const char* fName = "mlt_list.txt";
    float weight = 0;

    // default unit is kilo.
    Unit unit = KILO;

    // check if user didn't add any arguments
    if (argc < 2) {
        printf("please add atleast 1 argument\n");
        return -1;
    }

    // check arg[1] for argument flags:
    if (argv[1][0] == '-') {
        // check if user added a 2nd argument
        if (argc > 2) {
            switch (argv[1][1]) {
                case CH_KG_ARG:
                    unit = KILO;
                    break;
                case CH_POUND_ARG:
                    unit = POUND;
                    break;
                default:
                    printf("ERROR: 1st argument \'%s\' is inncorrect. (-h for help...)\n", argv[1]);
                    return -1;
                    break;
            }
            StrToFloat(argv[2], &weight);

        } else {
            switch (argv[1][1]) {
                case CH_HELP_ARG:
                    printf("%s\n", HELP_MSG);
                    break;
                default:
                    printf("ERROR: 1st argument \'%s\' is inncorrect OR it is and you didn't add correct parameteres for it. (-h for help...)\n", argv[1]);
                    return -1;
                    break;
            }

        }


    } else {
        printf("DEFAULTING TO \'"STR_KG_ARG"\' (see -h for info/HELP)\n");
        StrToFloat(argv[1], &weight);
    }


    // TODO: Add file operations next.

    // open file in 'append' mode
    FILE* f = fopen(fName, "a");
    if (!f) {
        printf("ERROR OPENING FILE: \'%s\'\n", fName);
        return -1;
    }

    errno = 0;
    const time_t curTime = time(NULL);
    if (curTime == ((time_t) -1)) {
        printf("ERROR GETTING TIME.\n");
        perror("ERRNO");
        return -1;
    }
    struct tm dateStruct = *localtime(&curTime);

    char* wDay = getWDayStr(dateStruct.tm_wday);

    switch (unit) {
        case KILO:
            fprintf(f, "%s: %d.%d.%d %.1fkg\n", wDay, dateStruct.tm_mday, dateStruct.tm_mon, (dateStruct.tm_year -100), weight);
            break;
        case POUND:
            fprintf(f,"%s: %d/%d/%d %.1flb\n", wDay, dateStruct.tm_mon, dateStruct.tm_mday, (dateStruct.tm_year -100), weight);
            break;
        default:
            fprintf(f, "%s: %d.%d.%d %.1fkg\n", wDay, dateStruct.tm_mday, dateStruct.tm_mon, (dateStruct.tm_year -100), weight);
            break;
    }

    fclose(f);


    return 0;

}
