#include <stdio.h>
#include <stdlib.h>

struct linkedlist{
    int size;
    char arr[];
}
;

void push(char item, char stack[], int *sizepointer){
    int size = *sizepointer;
    if (size == 0){
        stack[0] = item;
        stack[1] = '\0';
        *sizepointer = 1;

    } else {
        for (int i = size; i >= 0; i = i -1){
            stack[i+1] = stack[i];
        }
        stack[0] = item;
        *sizepointer = *sizepointer + 1;

    }
}

char pop(char stack[], int *sizepointer){
    int size = *sizepointer;
    if (size == 0){
        return '\0';

    } else {
        char item = stack[0];
        for (int i = 0; i + 1 <= size; i++){
            stack[i] = stack[i+1];
        }
        //stack.arr = &(stack.arr[1]);
        *sizepointer = *sizepointer - 1;
        return item;
    }
}

int main(int argc, char *argv[]){
    int length = 0;
    for (int i = 0; argv[1][i] != '\0'; i++){
        length = length + 1;
    }
    length = length + 1;
    char *stack = (char *)malloc(sizeof(char) * length);
    //printf("%li\n", sizeof(char) * length);
    int size = 0;
    for (int i = 0; argv[1][i] != '\0'; i++) {
        char current = argv[1][i];
        if ((current == '(') || (current == '[') || (current == '{')) {
            push(current, stack, &size);
            //printf("%i\n", size);
        } else if ((current == ')') || (current == ']') || (current == '}')){
            char popped = pop(stack, &size);
            //printf("%i\n", size);
            if (popped == '\0') {
                printf("%i: %c\n", i, current);
                free(stack);
                return EXIT_FAILURE;
            }
            int matches = 0;
            if ((popped == '(') && (current == ')')) {
                matches = 1;
            } else if ((popped == '[') && (current == ']')){
                matches = 1;
            } else if ((popped == '{') && (current == '}')){
                matches = 1;
            } else {
                matches = 0;
            }
            if (matches == 0){
                printf("%i: %c\n", i, current);
                free(stack);
                return EXIT_FAILURE;
            }
            


        }
    }
    //printf("%i\n", size);
    if (size == 0){
        free(stack);
        return EXIT_SUCCESS;

    } else {
        char *closers = malloc((size+1) * sizeof(char));
        int i = 0;
        while (size > 0) {
            char opener = pop(stack, &size);
            //printf("Value for size is %i\n", size);
            //printf("Value for i is %i\n", i);
            if (opener == '('){
                closers[i] = ')';
            } else if (opener == '['){
                closers[i] = ']';
            } else if (opener == '{'){
                closers[i] = '}';
            }
            i = i + 1;
        }
        closers[i] = '\0';
        printf("open: %s\n", closers);
        free(stack);
        free(closers);
        return EXIT_FAILURE;


    }
    
}


