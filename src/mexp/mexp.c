#include <stdio.h>
#include <stdlib.h>

/*char * generateString(int i){
    if (i == 1){
        return "%i";
    }
    return 
}*/

int ** multiply(int ** matrix1, int ** matrix2, int rows, int power, int *** listofmallocs) {
    int ** result = malloc(rows * sizeof(int *));
        for (int i = 0; i <= rows - 1; i++){
            result[i] = malloc(rows * sizeof(int));
        }
        listofmallocs[power] = result;
    for (int i = 0; i <= rows - 1; i++){
        for (int j = 0; j <= rows - 1; j++){
            int sum = 0;
            for (int c = 0; c <= rows - 1; c++) {
                sum = sum + (matrix1[i][c] * matrix2[c][j]);
            }
            result[i][j] = sum;
        }
    }
    return result;
}

int ** raisetopower(int ** matrix, int rows, int power, int *** listofmallocs){
    if (power == 0) {
        int ** result = malloc(rows * sizeof(int *));
        for (int i = 0; i <= rows - 1; i++){
            result[i] = malloc(rows * sizeof(int));
        }
        listofmallocs[power] = result;
        for (int i = 0; i <= rows - 1; i++){
            for (int j = 0; j <= rows - 1; j++){
                if (i == j) {
                    result[i][j]= 1;
                } else {
                    result[i][j] = 0;
                }
            }
        }
        return result;
    } else {
        return multiply(matrix, raisetopower(matrix, rows, power-1, listofmallocs),
        rows, power, listofmallocs);
    }


}

int main(int argc, char ** argv){
    FILE * stream = fopen(argv[1], "r");
    int numberoftimestobemultiplied;
    int rows;
    fscanf(stream, "%d", &rows);
    int columns = rows;
    int ** matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i <= rows - 1; i = i + 1){
        matrix[i] = malloc(columns * sizeof(int));
    }
    for (int i = 1; i <= rows; i++){
        for (int j = 1; j <= columns; j++){
            if (j == columns) {
                fscanf(stream, "%i", &(matrix[i-1][j-1]));
            } else {
                fscanf(stream, "%i ", &(matrix[i-1][j-1]));
            }
        }
    }
    fscanf(stream, "%i", &numberoftimestobemultiplied);
    fclose(stream);

    int *** listofmallocs = malloc( (numberoftimestobemultiplied + 1) * sizeof(int **) );
    /*int ** result = malloc(rows * sizeof(int *));
    for (int i = 0; i <= rows - 1; i++){
        result[i] = malloc(rows * sizeof(int));
    }*/
    int ** result = raisetopower(matrix, rows, numberoftimestobemultiplied, listofmallocs);
    for (int i = 0; i <= rows - 1; i++) {
        for (int j = 0; j <= columns - 1; j++){
            if (j == columns - 1) {
                printf("%i\n", result[i][j]);
            } else {
                printf("%i ", result[i][j]);
            }   
        }
    }
    for (int i = 0; i <= numberoftimestobemultiplied; i++){
        for (int j = 0; j <= rows - 1; j++){
            free(listofmallocs[i][j]);
        }
        free(listofmallocs[i]);
    }
    free(listofmallocs);
    /*for (int i = 0; i <= rows - 1; i++) {
        free(result[i]);
    }
    free(result);*/
    for (int i = 0; i <= rows - 1; i++) {
        free(matrix[i]);
    }
    free(matrix);

    
    /*for (int i = 0; i <= rows - 1; i++) {
        for (int j = 0; j <= columns - 1; j++){
            if (j == columns - 1) {
                printf("%i\n", matrix[i][j]);
            } else {
                printf("%i ", matrix[i][j]);
            }   
        }
    }
    for (int i = 0; i <= rows - 1; i++) {
        free(matrix[i]);
    }
    free(matrix);*/ 
}