#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc == 1) {
        return EXIT_SUCCESS;
    }
    int length = 0;
    for (int i = 0; argv[i] != NULL; i++){
        length++;

    }
    length--;
    //char **output = malloc(length * sizeof(char *));
    for (int i = 2; i <= length; i++){
        int current = i;
        while ((strcmp(argv[current], argv[current - 1]) < 0) && (current >=2)) {
            char * temp = argv[current];
            argv[current] = argv[current - 1];
            argv[current - 1] = temp;
            current = current - 1;
        }
    }
    for (int i = 1; i <= length; i++){
        printf("%s\n", argv[i]);
    }
    

    /*if (length == 1){
        printf("%s\n", argv[1]);
        return EXIT_SUCCESS;
    }
    for (int i = length; i >= 1; i = i - 1){
        int later = i;
        int earlier = i - 1;
        printf("part c%i\n", i);
        while (earlier >= 2){
            if (strcmp(argv[later], argv[earlier]) < 0){
                if (strcmp(argv[later], argv[earlier - 1]) < 0){
                    earlier = earlier - 1;
                } else {
                    break;
                }
            } else {
                earlier = earlier - 1;
            }
        }
        if ((earlier == 1) && (later == 2)) {
            if (strcmp(argv[later], argv[earlier]) < 0) {
                char * temp = argv[later];
                argv[later] = argv[earlier];
                argv[earlier] = temp;
            } else {
                break;
            }
        }

        char * temp = argv[later];
        argv[later] = argv[earlier];
        argv[earlier] = temp;
        for (int i = 1; i <= length; i = i + 1){
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    for (int i = 1; i <= length; i = i + 1){
        printf("%s\n", argv[i]);
    }
    printf("The value for argc is %i\n", argc);
    printf("The value for length is %d\n", length);
    return EXIT_SUCCESS; */
    return EXIT_SUCCESS;
}
