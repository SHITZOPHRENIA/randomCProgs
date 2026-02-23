// WORK IN PROGRESS
// -
// THIS IS GOING TO BE A WEIGHT LOSS TRACKER
//
//                              -shitzo
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

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
                        "-"STR_POUND_ARG"    STORES GIVE NUMBER AS LB/POUNDS\n"
                        "\n"
                        "\n"
                        "";


void StrToFloat(char* s, float* f) {
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

int main(int argc, char* argv[]) {
    // const char* fName = "massTrack.txt";
    float input_lb = 0;
    float input_kg = 0;

    // check if user didn't add any arguments
    if (argc < 2) {
        printf("please add atleast 1 argument\n");
        return -1;
    }

    // check arg[1] for argument flags:
    if (argv[1][0] == '-') {
        // check if user added a 2nd argument
        switch (argv[1][1]) {
            case CH_HELP_ARG:
                printf("%s\n", HELP_MSG);
                break;
            default:
                printf("ERROR: 1st argument \'%s\' is inncorrect. (-h for help...)\n", argv[1]);
                break;

            }
        if (argc > 2) {
            switch (argv[1][1]) {
                case CH_KG_ARG:
                    StrToFloat(argv[2], &input_kg);
                    break;
                case CH_POUND_ARG:
                    StrToFloat(argv[2], &input_lb);
                    break;
                default:
                    printf("ERROR: 1st argument \'%s\' is inncorrect. (-h for help...)\n", argv[1]);
                    break;
            }
        }


    } else {
        printf("DEFAULTING TO \'"STR_KG_ARG"\' (see -h for info/HELP)\n");
        StrToFloat(argv[1], &input_kg);
    }

    // TODO: REMOVE THESE 2 printf() when not needed anymore.
    printf("input as kg = %.1f\n", input_kg);
    printf("input as lb = %.1f\n", input_lb);

    // TODO: Add file operations next.


    return 0;

}
