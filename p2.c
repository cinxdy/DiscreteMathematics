// p2.c

#define T 5
int board[T][1001][1001];

void print_board(int tt);
bool z3(int tt);
int formula(int tt, int** input);
int N, M;
int main (){
    int x,y,k;
	int N = 0;
    int M = 0;

    // Scan the input file
    int** input = read_input(&N,&M);

    int tt;
    for(tt = 0; tt < 5; tt ++) {

	if(!formula(tt,input)) {
		break;
	} else {
    		print_board(tt);
	}
    }
    if(tt == 0) {
	printf("No solution\n");
    }
}    


// check Satisfiable and get model
int formula(int tt, int** input) {
    int x,y,k;

    // Write the formula
	FILE * fp = fopen("formula", "w") ;
	for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(declare-const a%d_%d Int)\n", y, x) ;

    // 0<= a_yx <=1
    for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(assert (and (<= 0 a%d_%d) (<= a%d_%d 1))) \n", y, x, y, x) ;

    // Q0 : sum of its neighbors is itself (?)
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

    // Q1 : never print same answer again
    for(int t = 0; t < tt; t++) {

	fprintf(fp, "(assert (not (and ");
	for(y = 1 ; y <= N; y++)
		for(x = 1 ; x <= M ; x++) {

		int v = board[t][y-1][x-1];
		fprintf(fp,"(= a%d_%d %d) ",y,x,v) ;
	}
	fprintf(fp,") )) \n") ;
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    
    fclose(fp);
    return z3(tt);
}

bool z3(int tt) {
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
				board[tt][col-1][row-1] = val;		
			}
		}
	}
	return true;
}
void print_board(int tt) {
	for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				printf("%d ",board[tt][i][j]);
			}
			printf("\n");
		}
	printf("\n");
}
