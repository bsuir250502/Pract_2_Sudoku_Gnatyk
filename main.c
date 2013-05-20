#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define m 9
    char Spis1[]="d:/input.txt";
    char Spis2[]="d:/output.txt";
    int ms[m][m];


    void clear_screen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    FILE *Open_file(char*file,char*code)
    {
        FILE*f;
        if(!(f = fopen(file,code))){
            puts("Error!");
            exit(1);
        }
        else return f; 
    }

    void displaySudoku(FILE * file)
    {
        int i, j;
        file = fopen(Spis2, "w+");
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++) {
                if (j == 2 || j == 5 || j == 8) {
                    printf("%3d ", ms[i][j]);
                }

                else {
                    printf("%3d", ms[i][j]);
                }
            }
            puts("");
            if (i == 2 || i == 5 || i == 8) {
                puts("");
            }
        }
        for (i = 0; i < m; i++) {
            for (j = 0; j < m; j++) {
                fprintf(file, "%d ", ms[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }

    int** peresap_bin_f(FILE* file)
    {
        FILE *fb;
        fb = Open_file(Spis1,"r+");
        int i,j;
        for (i = 0; i< m; i++)  {
            for(j = 0;j < m; j++) {
                fscanf(file,"%d" ,&ms[i][j] );
            }
        }
        fclose(file);
        return 0;

    }

    int  check_the_rows()
    {
        int curr_num, i, j;
        int num_of_repeats = 0;
        for(curr_num = 1; curr_num < 10 ; curr_num++ ) {
            for (i = 0; i < m; i++) {
                for (j = 0; j < m; j++) {
                    if ( ms[i][j] == curr_num)
                        num_of_repeats ++;
                }
                if ( num_of_repeats > 1 ) {
                    return 1;
                }
                num_of_repeats = 0;
            }
        }
        return 0;
    }

    int check_the_columns ()
    {
        int curr_num, i, j;
        int num_of_repeats = 0;
        for(curr_num = 1; curr_num < 10; curr_num++ ) {
            for (j = 0; j < m; j++) {
                for (i = 0; i < m; i++) {
                    if ( ms[i][j] == curr_num)
                        num_of_repeats ++;
                }
                if ( num_of_repeats > 1 ){
                    return 1;
                }
                num_of_repeats = 0;
            }
        }
        return 0;

    }

    int check_the_squares ()
    {
        int curr_num, i, j, ii, jj;
        int num_of_repeats = 0;
        for(curr_num = 1; curr_num < 10; curr_num++ ) {
            for (i = 0; i < m; i += 3) {
                for (j = 0; j < m; j += 3) {
                    for (ii = i; ii < i+3 ; ++ ii) {
                        for (jj = j; jj < j+3 ; ++ jj) {
                            if (ms[ii][jj] == curr_num)
                                num_of_repeats ++;
                        }
                    }
                    if ( num_of_repeats > 1 ) {
                        return 1;
                    }
                    num_of_repeats = 0;                       
                }          
            }
        }
        return 0;
    }

    int check_sudoku ()
    {
        if (check_the_rows () == 0)
        {
            if (check_the_columns () == 0)
            {
                if (check_the_squares () == 0)
                    return 0;
                else 
                    return 1;
            }
            return 1;
        }
        return 1;    
    }

    int funct_sudoku(FILE * file, int i,int j)
    {
        int  current_number = 1;
        while (1) {
            if ((i + 1) >= m && (j + 1) >= m)
                return 0;
            if (j >= m) {
                i++;
                j = 0;
            }
            if(ms[i][j] != 0) {
                j++;
            }
            else
                break;
        }
        while (1) {
            while (1) {
                if(current_number <= m) {
                    ms[i][j] = current_number;
                    current_number ++;
                    if (check_sudoku() == 0) {
                        break;
                    }
                }
                if (current_number >= m+1) {
                    ms[i][j] = 0;
                    return 1;
                }
            }
            if ( funct_sudoku(file, i, (j + 1 )) == 0) {
                return 0;
            }
        }
    }

    int main(int argc, char* argv[])
    {

        FILE *file;
        int koll;
        file = NULL;
        file = Open_file(Spis1,"r");
        peresap_bin_f(file);
        koll = funct_sudoku(file,0,0);
        if (koll == 1) {
            puts ("Sudoku is not correct");
            return 0;
        }
        else {
            displaySudoku(file);
        }          
        return 0;
    }



#ifdef __cplusplus
}
#endif

