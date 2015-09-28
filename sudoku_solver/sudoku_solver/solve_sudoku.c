#include <stdio.h>

typedef enum {FALSE, TRUE} boolean;

boolean solve( int matr[9][9], int r, int c);
boolean is_valid( int matr[9][9], int r, int c);
void print_matr(int matr[9][9]);

int main(int argc, const char * argv[]) {
    FILE *f_in;
    int val, r=0, c=0, matr[9][9], status;
    
    // open sudoku file
    if ((f_in = fopen(argv[1], "r")) == NULL) {
        printf("Error while reading the input file\n");
        return 1;
    }
    
    // read file
    for (status = fscanf(f_in,"%d", &val);
            status != EOF;
                status = fscanf(f_in,"%d", &val)) {
        matr[r][c] = val;
        c++;
        if (c > 8) {
            c = 0;
            r++;
        }
    }
    
    printf("Original sudoku:\n\n");
    print_matr(matr);
    
    // solve sudoku
    solve(matr, 0, 0);
    
    // print solved sudoku
    printf("\n\nSolved sudoku:\n\n");
    print_matr(matr);
    return 0;
}

void print_matr(int matr[9][9]) {
    int r, c;
    for (r=0; r < 9; r++) {
        if (r%3 == 0) {
            printf(" -----------------------\n");
        }
        for (c=0; c < 9; c++) {
            if (c%3 == 0) {
                printf("|");
            }
            if (matr[r][c] == 0) {
                printf(" -");
            }
            else {
                printf(" %d", matr[r][c]);
            }
            if ((c+1)%3 == 0) {
                printf(" ");
            }
        }
        printf("|");
        printf("\n");
    }
    printf(" -----------------------\n");
}

boolean solve( int matr[9][9], int r, int c) {
    int i;
    
    if (r > 8) {
        return TRUE;
    }
    if (matr[r][c] != 0) {
        // go to the next number
        c++;
        if (c > 8) {
            c=0;
            r++;
        }
        if (solve(matr, r, c)) {
            return TRUE;
        }
    }
    else {
        // position is to be filled
        for (i=1; i < 10; i++) {
            matr[r][c] = i;
            if ( is_valid(matr, r, c)) {
                c++;
                if (c > 8) {
                    c=0;
                    r++;
                }
                if (solve(matr, r, c)) {
                    return TRUE;
                }
                c--;
            }
        }
        // backtrack
        matr[r][c] = 0;
    }
    return FALSE;
}


boolean is_valid( int matr[9][9], int r, int c) {
    int i, j, start_line, end_line, start_col, end_col;
    
    // check line
    for (j=0; j < 9; j++) {
        if (matr[r][j] == matr[r][c] && j!=c) {
            return FALSE;
        }
    }
    
    // check column
    for (i=0; i < 9; i++) {
        if (matr[i][c] == matr[r][c] && i!=r) {
            return FALSE;
        }
    }
    
    // check 3x3 square
    start_line = r - (r%3);
    end_line = start_line + 3;
    start_col = c - (c%3);
    end_col = start_col + 3;
    for (i=start_line; i < end_line; i++) {
        for (j=start_col; j < end_col; j++) {
            if (matr[i][j] == matr[r][c] && i!=r && j!=c) {
                return FALSE;
            }
        }
    }
    
    // is valid
    return TRUE;
}