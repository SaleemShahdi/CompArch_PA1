#include <stdio.h>
#include <stdlib.h>

struct linkedlist{
    int number;
    struct linkedlist * next;
    struct linkedlist * prev;
}
;

void insert(int item, int * linkedListSize, struct linkedlist ** front){
    //printf("%i\n", item);
    //printf("%i\n", *linkedListSize);
    if (*linkedListSize == 0){
        (**front).number = item;
        (**front).next = NULL;
        (**front).prev = NULL;
        *linkedListSize = *linkedListSize + 1;
        //printf("item being added is %i with new size %i\n", linkedListPointer->number, *linkedListSize);
        return;
    } else {
        //printf("made it to line 22");
        struct linkedlist * currentnode = *front;
        //printf("made it to line 24");
        for (int i = 0; i < *linkedListSize; i = i + 1){
            if (item <= currentnode->number) {
                if (item == currentnode->number) {
                    //printf("success");
                    return;
                } else if (i == 0) {
                    struct linkedlist * current = malloc(sizeof(struct linkedlist));
                    //*current = {item, currentnode, NULL};
                    current->number = item;
                    current->next = currentnode;
                    current->prev = NULL;
                    currentnode->prev = current;
                    //**front = *current;
                    *linkedListSize = *linkedListSize + 1;
                    *front = current;
                    //printf("success");
                    return;
                } else {
                    struct linkedlist * current = malloc(sizeof(struct linkedlist));
                    //*current = {item, currentnode, currentnode->prev};
                    current->number = item;
                    current->next = currentnode;
                    current->prev = currentnode->prev;
                    (currentnode->prev)->next = current;
                    currentnode->prev = current;
                    *linkedListSize = *linkedListSize + 1;
                    //printf("sucess");
                    return;
                }
            }
            //printf("made it to line 42");
            if (i == *linkedListSize - 1) {
                break;
            } else {
                currentnode = currentnode->next;
            } 
        }
        //printf("made it to line 48");
        struct linkedlist * current = malloc(sizeof(struct linkedlist));
        //*current = {item, NULL, currentnode};
        current->number = item;
        current->next = NULL;
        current->prev = currentnode;
        currentnode->next = current;
        *linkedListSize = *linkedListSize + 1;
        //printf("success");
        return;
        
    }
}

void delete(int item, int * linkedListSize, struct linkedlist ** front){
    if (*linkedListSize == 0) {
        return;
    }
    struct linkedlist * current = *front;
    while (current != NULL) {
        if (item < current->number) {
            return;
        }
        if (item > current->number) {
            current = current->next;
            continue;
        }
        if (item == current->number) {
            if ((current->prev == NULL) && (current->next == NULL)) {
                free(current);
                current = NULL;
                *linkedListSize = *linkedListSize - 1;
            } else if (current->prev == NULL) {
                *front = current->next;
                (current->next)->prev = NULL;
                current->next = NULL;
                free(current);
                current = NULL;
                *linkedListSize = *linkedListSize - 1;
            } else if (current->next == NULL) {
                (current->prev)->next = NULL;
                current->prev = NULL;
                free(current);
                current = NULL;
                *linkedListSize = *linkedListSize - 1;
            } else {
                (current->prev)->next = current->next;
                (current->next)->prev = current->prev;
                current->next = NULL;
                current->prev = NULL;
                free(current);
                current = NULL;
                *linkedListSize = *linkedListSize - 1;
            }
            return;
        }
    }
    return;
}
    /*if (*linkedListSize == 0){
        return;
    } else {
        struct linkedlist * currentnode = *front;
        for (int i = 0; i < *linkedListSize; i = i + 1){
            if (item >= currentnode->number) {
                if (item == currentnode->number) {
                    if (i == 0){
                        *front = currentnode->next;
                        (currentnode->next)->prev = NULL;
                        currentnode->next = NULL;
                        free(currentnode);
                        currentnode = NULL;
                        *linkedListSize = *linkedListSize - 1;
                    } else {
                        (currentnode->prev)->next = currentnode->next;
                        currentnode->next->prev = currentnode->prev;
                        currentnode->next = NULL;
                        currentnode->prev = NULL;
                        free(currentnode);
                        currentnode = NULL;
                        *linkedListSize = *linkedListSize - 1;
                    }
                    //printf("success");
                } else {
                    currentnode = currentnode->next;
                }
            } else {
                return;
            }
            if (i == *linkedListSize - 1) {
                break;
            } else {
                currentnode = currentnode->next;
            }
        }
        if (item < currentnode->number) {
            return;
        } else if (item == currentnode->number) {
            (currentnode->prev)->next = NULL;
            currentnode->prev = NULL;
            free(currentnode);
            currentnode = NULL;
            *linkedListSize = *linkedListSize - 1;
            return;
        } else {
            return;
        } 
    }
}*/

void freeAll(struct linkedlist * front, int * size) {
    if (*size == 0) {
        return;
    }
    if ((*front).next == NULL) {
        free(front);
        front = NULL;
        return;
    } else {
        freeAll((*front).next, size);
        free(front); //added
        front = NULL; //added
    }
}



int main(int argc, char **argv){
    char instruction;
    int number;
    int size = 0;
    struct linkedlist ** front = malloc(sizeof(struct linkedlist *));
    while (1){
        //printf("Number read in was %i\n", number);
        int i = scanf("%c %i", &instruction, &number);
        if (i == EOF) {
            break;
        }
        if (i == 1) {
            continue;
        }
        if (instruction == 'i'){
            if (size == 0) {
                *front = malloc(sizeof(struct linkedlist));
            }
            insert(number, &size, front);
        } else if (instruction == 'd') {
            delete(number, &size, front);
        }
        if (size == 0) {
            printf("%i :\n", size);
            continue;
        }
        printf("%i : ", size);
        struct linkedlist * current = *front;
        //struct linkedlist current = *current1;
        //struct linkedlist current = linkedList;
        while (current->next != NULL) {
            printf("%i ", current->number);
            current = current->next;
        }
        printf("%i\n", current->number);
        // free(current);
        }
        freeAll(*front, &size);
        free(front);
    }
    
    
