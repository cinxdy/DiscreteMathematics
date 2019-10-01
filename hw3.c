// 21800409 Jiyoung Shin
// 21700613 SB

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int board[101][101];

int N, M;
void print_board();
bool z3();
int main (){
    int x,y,k;

// scan the input file
    int** input;
    int arr[4096];
    int arr_cnt = 0;
    char c;
    N = 1; M = 0;
    while(!feof(stdin)) {
	char ch[128];
	scanf("%s",ch);
		if(strcmp("?",ch) == 0) {
			arr[arr_cnt] = 0;
			arr_cnt ++;
		} else {
			arr[arr_cnt] = atoi(ch);
			arr_cnt ++;
		}
	if(getchar() == '\n') N++;
    }
    M = arr_cnt / N;

    input = (int**) malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++) {
	input[i] = (int*) malloc(sizeof(int)*M);
    }

    for(int i = 0; i < arr_cnt; i++) {
	int quo, remain;
	quo = i / M;
	remain = i % M;
	input[quo][remain] = arr[i];
    }


    // write formula
	FILE * fp = fopen("formula", "w") ;

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

    
    // Q2 : like snake
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

    // Q3 : Every row and column has only one every value.
    for (k = 1 ; k <= N*M ; k++){
        fprintf(fp,"(assert (= (+ ");
        for (y = 1 ; y <= N ; y++) 
            for (x =1 ; x <= M ; x++)
                fprintf(fp,"\t(ite (= a%d_%d %d) 1 0)\n",y,x,k);
            
        fprintf(fp, ") 1))\n") ;
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    
	fclose(fp) ;
	
	if(z3()) print_board();
}
bool z3() {
    int i, j, k;
    char satis[128];
    char a[128] ;
    char b[128] ;
    char s[128] ;
    char t[128] ;

	FILE * fin = popen("z3 formula", "r");

	while(!feof(fin)) {
    		fscanf(fin,"%s",satis);
		if(strcmp("unsat",satis) == 0) {
			fscanf(fin,"%s",b); // error message absort
			printf("No solution\n");
			return false;
		} else if(strcmp("sat",satis) == 0) {
			fscanf(fin,"%s",b); // error message absort
			while(1) {

				int val, col, row;

				fscanf(fin,"%s", a) ;
				if(strcmp(")",a) == 0) break;
				fscanf(fin," a%d_%d %s %s %s", &col,&row, b, b, t) ;

				t[strlen(t)-1] = 0x0;
				val = atoi(t);
				board[col-1][row-1] = val;		
			}
		}
	}
	return true;
}
void print_board() {
	for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				printf("%d ",board[i][j]);
			}
			printf("\n");
		}
	printf("\n");
}
