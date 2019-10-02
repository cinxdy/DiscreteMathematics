// p1.c

#include "pset.h"

int main (){
    int x,y,k;
    int N = 9;
    int M = 9;

    // Scan the input file
    int** input = read_input(&N,&M);

    // Write the formula
	FILE * fp = fopen("formula", "w") ;

    // Declare the variables
	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(declare-const a%d_%d Int)\n", y, x) ;

    // Q0 : Specific number
    for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
            if(input[y-1][x-1]>0)
			    fprintf(fp, "(assert (= a%d_%d %d))\n", y, x, input[y-1][x-1]) ;

    // Q1 : All values are between 1-9.
    for (y = 1 ; y <= 9 ; y++)
        for (x = 1 ; x <= 9 ; x++)
        fprintf(fp, "(assert (and (<= 1 a%d_%d) (<= a%d_%d 9)))\n",y,x,y,x);

    // Q2 : Every row has only one every value.
    for (k = 1 ; k <=9 ; k++){
        for (y = 1 ; y <= 9 ; y++) {
            fprintf(fp,"(assert (= (+ ");
            for (x =1 ; x <= 9 ; x++){
                fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);
            }
            fprintf(fp, ") 1))\n") ;
        }
    }

    // Q3 : Every column has only one every value.
    for (k = 1 ; k <=9 ; k++){
        for (x = 1 ; x <= 9 ; x++) {
            fprintf(fp,"(assert (= (+ ");
            for (y =1 ; y <= 9 ; y++){
                fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);
            }
            fprintf(fp, ") 1))\n") ;
        }
    }

    // Q4 : Every box has only one every value.
    for(int m = 1 ; m <= 3 ; m++){
        for(int n = 1 ; n <= 3 ; n++){

            for (k = 1 ; k <=9 ; k++){
                fprintf(fp,"(assert (= (+ ");
                for (y = 3*m-2 ; y <= 3*m ; y++){
                    for (x = 3*n-2 ; x <= 3*n ; x++) {
                        fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);

                    }
                }
            fprintf(fp, ") 1))\n") ;
            }
        }
    }

    // Q5 : All star value is aristerisk
    for (k = 1 ; k <= 9 ; k++){
        fprintf(fp,"(assert (<= (+ \n");
        for (y = 1 ; y <= 9 ; y++) {
            for (x = 1 ; x <= 9 ; x++){
                if (input[y-1][x-1] == -1)
                    fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);
            }
        }
        fprintf(fp, ") 1))\n");
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
	fclose(fp) ;


    // Execute Z3 and print the result
    int** board = (int**) malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++)
	    board[i] = (int*) malloc(sizeof(int)*M);

	if(z3(N,M,board)) print_board(N,M,board);
}