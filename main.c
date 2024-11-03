#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

void show_2d_matrix(int row, int col, int **mtx){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%d ", *(*(mtx + i)+j));
        }
        printf("\n");
    }
}

int ** matrix_definition(int *rows, int *cols, char * matrix_name){
    printf("Pendefinisian matriks %s \n", matrix_name);

    int ** matrix;

    // Input ukuran matriks
    printf("Masukkan jumlah baris matriks : ");
    scanf("%d", rows);
    printf("Masukkan jumlah kolom matriks : ");
    scanf("%d", cols);

    // Dynamically alocate memory for the matrix
    matrix = (int **)malloc(*rows * sizeof(int *));
    for(int i = 0; i < *rows; i++){
        *(matrix + i) = (int *)malloc(*cols * sizeof(int));
    }

    // Get matrix entries value from user input
    printf("\n");
    for(int i = 0; i < *rows; i++){
        for(int j = 0; j < *cols; j++){
            printf("Nilai matriks baris-%d kolom-%d : ", i + 1, j + 1);
            scanf("%d", *(matrix + i) + j);
        }
        printf("\n");
    }

    printf("Hasil matriks %s \n", matrix_name);
    show_2d_matrix(*rows, *cols, matrix);
    printf("\n\n\n\n");

    return matrix;
}

void matrix_addition_subtraction(int ** mtx1, int rows1, int cols1, int ** mtx2, int rows2, int cols2, char * method){
    // Check if matrices can addited
    if(rows1 != rows2 || cols1 != cols2){
        printf("Matrix tidak bisa dijumlahkan");
        return;
    }

    printf("Matrix a : \n");
    show_2d_matrix(rows1, cols1, mtx1);
    printf("\nMatrix b : \n");
    show_2d_matrix(rows2, cols2, mtx2);

    if(method == "addition"){
        printf("\nMatrix a  +  Matrix b :\n");
    }else if(method == "substraction"){
        printf("\nMatrix a  -  Matrix b :\n");
    }

    for(int i = 0; i < rows1; i++){
        int sum = 0;
        for(int j = 0; j < cols1; j++){
            if(method == "addition"){
                sum = *(*(mtx1 + i)+j) + *(*(mtx2 + i)+j);
            }else if(method == "substraction"){
                sum = *(*(mtx1 + i)+j) - *(*(mtx2 + i)+j);
            }else{
                printf("Invalid method");
            }
            printf("%d ", sum);
        }
        printf("\n");
    }

    printf("\n\n");
    printf("Tekan enter untuk lanjut : ");
    _getch();
    printf("\n\n\n\n");
}


void matrix_multipication(int ** mtx1, int rows1, int cols1, int ** mtx2, int rows2, int cols2){
    // Check if matrices can be multiplied
    if(cols1 != rows2){
        printf("Matrix can't be multiplied");
        return;
    }

    printf("Matrix a : \n");
    show_2d_matrix(rows1, cols1, mtx1);
    printf("\nMatrix b : \n");
    show_2d_matrix(rows2, cols2, mtx2);

    printf("\nMatrix a  x  Matrix b :\n");

    for(int i = 0; i < rows1; i++){
        for(int j = 0; j < cols2; j++){
            int res = 0; 
            for(int k = 0; k < cols1; k++){
                res += *(*(mtx1 + i)+k) * *(*(mtx2 + k)+j);
            }
            printf("%d ", res);
        }
        printf("\n");
    }

    printf("\n\n");
    printf("Tekan enter untuk lanjut : ");
    _getch();
    printf("\n\n\n\n");
}


int main(){

    int **matrix1 = NULL;
    int **matrix2 = NULL;
    int matrix1_defined = 0;
    int matrix2_defined = 0;


    int rows1, cols1;
    int rows2, cols2;

    // Program loop
    int user_pick = 1;
    while(user_pick != 0){

        printf("============================== Calculator ================================\n"
               "Pilihan Program : \n"
               "1. Operasi Matrix\n"
               "0. Keluar\n\n"
               "Pilih program yang anda inginkan : "
        );

        scanf("%d", &user_pick);
        printf("\n\n\n\n");

        if(user_pick == 1){
            int user_pick_matrix_program = 1;

            if(matrix1_defined == 0 || matrix2_defined == 0){
                matrix1 = matrix_definition(&rows1, &cols1, "a");
                matrix1_defined = 1;
                matrix2 = matrix_definition(&rows2, &cols2, "b");
                matrix2_defined = 1;
            }
            while(user_pick_matrix_program != 0){
                printf("============================ Operasi Matrix ===============================\n");
                printf("Matriks a : \n");
                show_2d_matrix(rows1, cols1, matrix1);

                printf("\nMatriks b : \n");
                show_2d_matrix(rows2, cols2, matrix2);
                
                printf("\n\n"
                        "Pilihan Operasi : \n"
                        "1. Penjumlahan Matriks\n"
                        "2. Pengurangan Matriks\n"
                        "3. Perkalian Matriks\n"
                        "4. Pendefinisian Ulang Matriks\n"
                        "0. Keluar\n"
                        "Pilih Proses : "
                );

                scanf("%d", &user_pick_matrix_program);
                printf("\n\n\n\n");
                if(user_pick_matrix_program == 1){
                    matrix_addition_subtraction(matrix1, rows1, cols1, matrix2, rows2, cols2, "addition");
                }else if(user_pick_matrix_program == 2){
                    matrix_addition_subtraction(matrix1, rows1, cols1, matrix2, rows2, cols2, "substraction");
                }else if(user_pick_matrix_program == 3){
                    matrix_multipication(matrix1, rows1, cols1, matrix2, rows2, cols2);
                }else if(user_pick_matrix_program == 4){
                    printf("Proses belum tersedia");
                }
            }

            
        }


    };

    // Cleanup memory allocation
    if(matrix1_defined){
        for(int i = 0; i < rows1; i++){
            free(*(matrix1 + i));
            *(matrix1 + i) = NULL;
        }

        free(matrix1);
        matrix1 = NULL;
    }

    if(matrix2_defined){
        for(int i = 0; i < rows2; i++){
            free(*(matrix2 + i));
            *(matrix2 + i) = NULL;
        }

        free(matrix2);
        matrix2 = NULL;
    }

    return 0;

}

