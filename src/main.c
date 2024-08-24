#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

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

    printf("\n\n");
    
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

int** copy_matrix(int** newMatrix, int** matrix, int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}

int moves_possible(int** matrix, int size) {
    int** matrix_before = define_matrix(size);
    int** matrix_after = define_matrix(size);
    copy_matrix(matrix_before, matrix, size);
    copy_matrix(matrix_after, matrix, size);

    shift_up(matrix_after, size);
    if (matrix_changed(matrix_before, matrix_after, size))
        return 1;

    //reset matrix_after
    copy_matrix(matrix_after, matrix, size);
    shift_right(matrix_after, size);
    if (matrix_changed(matrix_before, matrix_after, size))
        return 1;

    copy_matrix(matrix_after, matrix, size);
    shift_down(matrix_after, size);
    if (matrix_changed(matrix_before, matrix_after, size))
        return 1;

    copy_matrix(matrix_after, matrix, size);
    shift_left(matrix_after, size);
    if (matrix_changed(matrix_before, matrix_after, size))
        return 1;
    
    return 0;
}

int main()
{
    //Initialize graphics
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640*4, 480*4, 0, &window, &renderer);    

    //Initialize game
    int exit = 0;
    int MATRIX_SIZE = 5;
    int** matrix = define_matrix(MATRIX_SIZE);

    fill_random_field(matrix, MATRIX_SIZE);
    fill_random_field(matrix, MATRIX_SIZE);
    print_matrix(matrix, MATRIX_SIZE);

    while (!exit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            exit = 1;
                            break;
                        case SDLK_RIGHT:
                            shift_right(matrix, MATRIX_SIZE);
                            break;
                        case SDLK_LEFT:
                            shift_left(matrix, MATRIX_SIZE);
                            break;
                        case SDLK_UP:
                            shift_up(matrix, MATRIX_SIZE);
                            break;
                        case SDLK_DOWN:
                            shift_down(matrix, MATRIX_SIZE);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }

            //TODO: outsource rendering in other function
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawLine(renderer, 640*2, 480*2, 640, 480);
            SDL_RenderPresent(renderer);

            //TODO: fix game logic with SDL_KEYUP
            print_matrix(matrix, MATRIX_SIZE);
            if(!moves_possible(matrix, MATRIX_SIZE)) {
                printf("No more moves possible!");
                break;
            }
        }
    }   

    printf("Game ended.");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    //clean up
    for(int i = 0; i < MATRIX_SIZE; i++) {
        free(matrix[i]);
    }
    
    free(matrix);
    return 0;
}
