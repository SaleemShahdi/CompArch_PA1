#include <stdio.h>
#include <stdlib.h>

struct node1 {
    int number;
    struct node1 * left;
    struct node1 * right;
};

typedef struct node1 node;

int insert(node * front, int value, int * size) {
    if (*size == 0) {
        //front = malloc(sizeof(node));
        front->number = value;
        front->left = NULL;
        front->right = NULL;
        *size = *size + 1;
        return 1;
    } else {
        if (value == front->number) {
            return 0;
        } else if (value < front->number){
            if (front->left == NULL) {
                node * current = malloc(sizeof(node));
                current->number = value;
                current->left = NULL;
                current->right = NULL;
                front->left = current;
                *size = *size + 1;
                return 1;
            } else {
                return insert(front->left, value, size);
            }
        } else if (value > front->number) {
            if (front->right == NULL) {
                node * current = malloc(sizeof(node));
                current->number = value;
                current->left = NULL;
                current->right = NULL;
                front->right = current;
                *size = *size + 1;
                return 1;
            } else {
                return insert(front->right, value, size);
            }
        }
    }
    return -1;
}

int search(node * front, int value, int * size) {
    if (*size == 0) {
        return 0;
    } else {
        if (value == front->number) {
            return 1;
        } else if (value < front->number){
            if (front->left == NULL) {
                return 0;
            } else {
                return search(front->left, value, size);
            }
        } else if (value > front->number) {
            if (front->right == NULL) {
                return 0;
            } else {
                return search(front->right, value, size);
            }
        }
    }
    return -1;
}

void printBST(node * front, int * size) {
    if (*size == 0) {
        return;
    }
    if (front == NULL) {
        return;
    }
    printf("(");
    printBST(front->left, size);
    printf("%i", front->number);
    printBST(front->right, size);
    printf(")");

}

void freeAll(node ** front, int * size) {
    if (*size == 0) {
        return;
    }
    if (((**front).left == NULL) && ((**front).right == NULL)) {
        free(*front);
        *front = NULL;
        *size = *size - 1;
        return;
    } 
    if ((**front).left != NULL) {
        freeAll(&((**front).left), size);
    } 
    if ((**front).right != NULL) {
        freeAll(&((**front).right), size);
    }
    free(*front);
    *front = NULL;
    *size = *size - 1;
    return;
}

int delete (node ** front, int value, int * size) {
    if (*size == 0) {
        return 0;
    }
    /*node current = *front;
    printf("Address of current is %p\n", &current);
    printf("Address of front is %p\n", front);
    printf("Address of dereferencing front and then taking address is %p\n", &(*front));*/
    node * prev = NULL;
    node * current = *front;
    int foundValue = 0;
    int tookLeft = 0;
    int tookRight = 0;
    while (current != NULL) {
        if (value == current->number) {
            foundValue = 1;
            break;
        } else if (value < current->number) {
            prev = current;
            current = current->left;
            tookLeft = 1;
            tookRight = 0;
        } else if (value > current->number) {
            prev = current;
            current = current->right;
            tookRight = 1;
            tookLeft = 0;
        }
    }
    if (foundValue == 0) {
        return 0;
    }
    if ((current->left == NULL) && (current->right == NULL)) {
        free(current);
        current = NULL;
    } else if (current->right == NULL) {
        node * new = current->left;
        free(current);
        current = new;
    } else if (current->left == NULL) {
        node * new = current->right;
        free(current);
        current = new;
    } else {
        node * prev = NULL;
        node * maximum = current->left;
        node * right = maximum->right;
        while (right != NULL) {
            prev = maximum;
            maximum = right;
            right = right->right;
        }
        if ((maximum->left != NULL) || (prev == NULL)) { // here prev == NULL means if you're deleting the root node of the tree with 2 children
            current->left = maximum->left;
            current->number = maximum->number;
        } else {
            current->number = maximum->number;
            prev->right = NULL;
        }
        free(maximum);
    }
    *size = *size - 1;
    if (prev == NULL) {
        *front = current;
    } else if ((tookLeft == 1) && (tookRight == 0)) {
        prev->left = current;
    } else if ((tookLeft == 0) && (tookRight == 1)) {
        prev->right = current;
    }
    return 1;
}

int main(int argc, char ** argv) {
    char command;
    int value;
    int size = 0;
    node * front = NULL;
    while (scanf("%c", &command) != EOF) {
         if (command == 'i') {
             scanf(" %i", &value);
             if (size == 0) {
                front = malloc(sizeof(node));
             }
             int i = insert(front, value, &size);
             if (i==1) {
                printf("inserted\n");
             } else {
                printf("not inserted\n");
             }
         } else if (command == 's') {
            scanf(" %i", &value);
            int i = search(front, value, &size);
                if (i == 1) {
                    printf("present\n");
                } else {
                    printf("absent\n");
                }
            } else if (command == 'p') {
                printBST(front, &size);
                printf("\n");
            } else if (command == 'd') {
                scanf(" %i", &value);
                int i = delete(&front, value, &size);
                if (i == 0){
                    printf("absent\n");
                } else if (i == 1) {
                    printf("deleted\n");
                }
            }
            

         }
    freeAll(&front, &size);


    }