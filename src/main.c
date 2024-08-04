#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

int** define_matrix(int matrix_size) {
    int** matrix = calloc(matrix_size, sizeof(int*));
    
    for(int i = 0; i < matrix_size; i++) {
        matrix[i] = calloc(matrix_size, sizeof(int));  
    }
    
    return matrix;
}

int print_matrix(int **matrix, int matrix_size) {
    for(int i = 0; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            printf("%d |", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

int fill_random_field(int **matrix, int matrix_size) {
    int possibleFields = 0;
    for(int i = 0; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            if(matrix[i][j] == 0) {
                possibleFields++;
            }
        }
    }
    
    if(possibleFields == 0) {
        return 1;
    }
    
    int** fields = malloc(possibleFields * sizeof(int*));
    int fieldsPos = 0;
    for(int i = 0; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            if(matrix[i][j] == 0) {
                fields[fieldsPos] = &matrix[i][j];
                fieldsPos++;
            }
        }
    }
    
    srand(time(NULL));
    int random_index = rand() % (possibleFields + 1);
    int* field = fields[random_index];
    *field = 2;
    
    free(fields);
    return 0;
}

int is_empty_matrix(int** matrix, int matrix_size) {
    int free_field_count = 0;
    for(int i = 0; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            if(matrix[i][j] == 0) {
                free_field_count++;
            }
        }
    }
    
    return free_field_count != 0;
}

int shift_up(int** matrix, int matrix_size) {
    for(int i = 1; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            for(int k = i; k > 0; k--) {
                if(matrix[k-1][j] == matrix[k][j] || matrix[k-1][j] == 0) {
                    matrix[k-1][j] += matrix[k][j];
                    matrix[k][j] = 0;
                }
            }
        }
    }

    return 0;
}

int shift_right(int** matrix, int matrix_size) {
    for(int i = 0; i < matrix_size; i++) {
        for(int j = matrix_size - 1; j > 0; j--) {
            for(int k = j; k < matrix_size; k++) {
                if(matrix[i][k - 1] == matrix[i][k] || matrix[i][k] == 0) {
                    matrix[i][k] += matrix[i][k - 1];
                    matrix[i][k - 1] = 0;
                }
            }
        }
    }
    
    return 0;
}

int shift_down(int** matrix, int matrix_size) {
    for(int i = matrix_size - 1; i >= 0; i--) {
        for(int j = 0; j < matrix_size; j++) {
            for(int k = i; k < matrix_size - 1; k++) {
                if(matrix[k+1][j] == matrix[k][j] || matrix[k+1][j] == 0) {
                    matrix[k+1][j] += matrix[k][j];
                    matrix[k][j] = 0;
                }
            }
        }
    }

    return 0;
}

int shift_left(int** matrix, int matrix_size) {
    for(int i = 0; i < matrix_size; i++) {
        for(int j = 1; j < matrix_size; j++) {
            for(int k = j; k > 0; k--) {
                if(matrix[i][k-1] == matrix[i][k] || matrix[i][k-1] == 0) {
                    matrix[i][k-1] += matrix[i][k];
                    matrix[i][k] = 0;
                }
            }
        }
    }
    
    return 0;
}

int shift_matrix(int direction, int** matrix, int matrix_size) {
    switch(direction) {
        case UP: 
            return shift_up(matrix, matrix_size);
            break;
        case RIGHT: 
            return shift_right(matrix, matrix_size);
            break;
        case DOWN: 
            return shift_down(matrix, matrix_size);
            break;
        case LEFT: 
            return shift_left(matrix, matrix_size);
            break;
    }
    
    return 1;
}

int** copy_matrix(int** newMatrix, int** matrix, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}

int matrix_changed(int** matrix, int** refMatrix, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(matrix[i][j] != refMatrix[i][j]) {
                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    //Initialize game
    int MATRIX_SIZE = 5;
    int** matrix = define_matrix(MATRIX_SIZE);
    int** refMatrix = define_matrix(MATRIX_SIZE);

    fill_random_field(matrix, MATRIX_SIZE);
    fill_random_field(matrix, MATRIX_SIZE);

    //TODO: use SDL2

    //TODO: game loop
    
    print_matrix(matrix, MATRIX_SIZE);
    shift_matrix(UP, matrix, MATRIX_SIZE);
    printf("\n\n");
    print_matrix(matrix, MATRIX_SIZE);
    
    shift_matrix(RIGHT, matrix, MATRIX_SIZE);
    printf("\n\n");
    print_matrix(matrix, MATRIX_SIZE);

    shift_matrix(DOWN, matrix, MATRIX_SIZE);
    printf("\n\n");
    print_matrix(matrix, MATRIX_SIZE);

    shift_matrix(LEFT, matrix, MATRIX_SIZE);
    printf("\n\n");
    print_matrix(matrix, MATRIX_SIZE);
    
    //clean up
    for(int i = 0; i < MATRIX_SIZE; i++) {
        free(matrix[i]);
        free(refMatrix[i]);
    }
    
    free(matrix);
    free(refMatrix);
    return 0;
}
