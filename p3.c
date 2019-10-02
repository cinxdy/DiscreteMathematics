// p3.c

#include "pset.h"

int main (){
    int x,y,k;
    int N = 0;
    int M = 0;

    // Scan the input file
    int** input = read_input(&N,&M);

    // Write the formula
	FILE * fp = fopen("formula", "w") ;

    // Declare the variables
	for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(declare-const a%d_%d Int)\n", y, x) ;

    // Q0 : specific number
    for (y = 1 ; y <= N ; y++)
        for (x = 1 ; x <= M ; x++)
            if(input[y-1][x-1]>0)
                fprintf(fp, "(assert (= a%d_%d %d))\n", y, x, input[y-1][x-1]) ;

    // Q1 : All values are between 1-N*M.
    for (y = 1 ; y <= N ; y++)
        for (x = 1 ; x <= M ; x++)
        fprintf(fp, "(assert (and (<= 1 a%d_%d) (<= a%d_%d %d)))\n",y,x,y,x,N*M);

    // Q2 : a(i,j)-1 exists among the neighbors.
    for (y = 1 ; y <= N ; y++){
        for (x = 1 ; x <= M ; x++){
            fprintf(fp, "(assert (or \n");
            fprintf(fp, "(= a%d_%d %d) \n",y,x,1);
            if(1 <= y-1)
                fprintf(fp, "(= (+ a%d_%d -1) a%d_%d) \n",y,x,y-1,x);
            if(y+1 <= N)
                fprintf(fp, "(= (+ a%d_%d -1) a%d_%d) \n",y,x,y+1,x);
            if(1 <= x-1)
                fprintf(fp, "(= (+ a%d_%d -1) a%d_%d) \n",y,x,y,x-1);
            if(x+1 <= M)
                fprintf(fp, "(= (+ a%d_%d -1) a%d_%d) \n",y,x,y,x+1);
            fprintf(fp,"))\n");
        }
    }

    // Q3 : a(i,j)+1 exists among the neighbors.
    for (y = 1 ; y <= N ; y++){
        for (x = 1 ; x <= M ; x++){
            fprintf(fp, "(assert (or \n");
            fprintf(fp, "(= a%d_%d %d) \n",y,x,N*M);
            if(1 <= y-1)
                fprintf(fp, "(= (+ a%d_%d 1) a%d_%d) \n",y,x,y-1,x);
            if(y+1 <= N)
                fprintf(fp, "(= (+ a%d_%d 1) a%d_%d) \n",y,x,y+1,x);
            if(1 <= x-1)
                fprintf(fp, "(= (+ a%d_%d 1) a%d_%d) \n",y,x,y,x-1);
            if(x+1 <= M)
                fprintf(fp, "(= (+ a%d_%d 1) a%d_%d) \n",y,x,y,x+1);
            fprintf(fp,"))\n");
        }
    }

    // Q4 : Every row and column has only one every value.
    for (k = 1 ; k <= N*M ; k++){
        fprintf(fp,"(assert (= (+ ");
        for (y = 1 ; y <= N ; y++) 
            for (x =1 ; x <= M ; x++)
                fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);
            
        fprintf(fp, ") 1))\n") ;
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
	fclose(fp) ;


	// Execute Z3 and print the result
    int** board = (int**) malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++)
	    board[i] = (int*) malloc(sizeof(int)*M);

	if(z3(N,M,board)) print_board(N,M,board);
}