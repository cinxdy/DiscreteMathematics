// p2.c

#include "pset.h"
#define MAX_RESULT 5

void formula(int turn, int N, int M, int** input,int*** board);

int main (){
    int x,y,k;
    int N = 0;
	int M = 0;

	int** board[MAX_RESULT];
    // Scan the input file
    int** input = read_input(&N,&M);

	int turn;
    for(turn = 0; turn < MAX_RESULT; turn++) {
		// Make turn-th board [array]
		board[turn] = (int**) malloc(sizeof(int*)*N);
		for(int i = 0; i < N; i++)
			board[turn][i] = (int*) malloc(sizeof(int)*M);

		// Make the formula
		formula(turn, N, M, input,board);

		// Execute Z3 and get the turn-th solution
		if(!z3(N,M,board[turn])) break;
		else print_board(N,M,board[turn]);
    }
	
	// If solution doesn't exist, print No solution
    if(turn == 0) printf("No solution\n");
}    

// check Satisfiable and get model
void formula(int turn, int N, int M ,int** input,int*** board) {
	// DEBUG printf("formula > turn = %d\n",turn);

    int x,y,k;

    // Write the formula
	FILE * fp = fopen("formula", "w") ;
	for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(declare-const a%d_%d Int)\n", y, x) ;

    // Q0 : 0<= a_yx <=1
    for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(assert (and (<= 0 a%d_%d) (<= a%d_%d 1))) \n", y, x, y, x) ;

    // Q1 : The sum of its neighbors is itself
    for (y = 1 ; y <= N ; y++){
        for (x = 1 ; x <= M ; x++){
            if(input[y-1][x-1]>0){
                fprintf(fp,"(assert (= (+ \n");
                for(int m = -1 ; m <= 1 ; m++){
                    for(int n = -1 ; n <= 1 ; n++){
                        if(0<y+m && y+m<=N && 0<x+n && x+n<=M)
                            fprintf(fp,"a%d_%d ",y+m,x+n);
                    }
                }
                fprintf(fp,") %d))\n",input[y-1][x-1]);
            }
        }
    }
	
    // Q2 : Never print same answer again
	// Way 1. not(and)
    for(int t = 0; t < turn; t++) {
		fprintf(fp, "(assert (not (and ");
		for(y = 1 ; y <= N; y++)
			for(x = 1 ; x <= M ; x++) {
				fprintf(fp,"(= a%d_%d %d) ",y,x,board[t][y-1][x-1]) ;
			}
		fprintf(fp,") )) \n") ;
    }

	// Way2. or(distinct)
	/*
	fprintf(fp,"(assert (or \n");
	for(y = 1 ; y <= N; y++){
		for(x = 1 ; x <= M ; x++) {
			fprintf(fp, "(distinct a%d_%d ",y,x);
			for(int t = 0; t < turn; t++){
				fprintf(fp, "%d",board[t][y-1][x-1]);
			}
			fprintf(fp,") \n") ;
		}
	}
	fprintf(fp,")) \n");
	*/

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    fclose(fp);

	// DEBUG printf("formula < turn = %d\n",turn);
}