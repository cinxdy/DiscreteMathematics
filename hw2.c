// 21800409 Jiyoung Shin

#include <stdio.h>
// #define N 5
// #define M 5
#define T 5

int main (){
    int x,y,k;

    // scan the input file
    int N = 0, M = 0;
    int** input;
    int arr[4096];
    int arr_cnt = 0;
    char c;

    while(!feof(stdin)) {
	char ch;
	scanf("%c",&ch);
		if(ch >= '0' && ch <= '9') {
			arr[arr_cnt] = ch - '0';
			arr_cnt ++;
		} else if(ch == '?') {
			arr[arr_cnt] = 0;
			arr_cnt ++;
		} else if(ch == '\n') {
			N++;
		}
    }
    N--;
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
			fprintf(fp, "(declare-const a%d%d Int)\n", y, x) ;

    // 0<= a_yx <=1
    for (y = 1 ; y <= N ; y++)
		for (x = 1 ; x <= M ; x++)
			fprintf(fp, "(assert (and (<= 0 a%d%d) (<= a%d%d 1))) \n", y, x, y, x) ;

    // Q0 : sum of its neighbors is itself (?)
    for (y = 1 ; y <= N ; y++){
        for (x = 1 ; x <= M ; x++){
            if(input[y-1][x-1]>0){
                fprintf(fp,"(assert (= (+ \n");
                for(int m = -1 ; m <= 1 ; m++){
                    for(int n = -1 ; n <= 1 ; n++){
                        if(0<y+m && y+m<=N && 0<x+n && x+n<=M)
                            fprintf(fp,"a%d%d ",y+m,x+n);
                    }
                }
                fprintf(fp,") %d))\n",input[y-1][x-1]);
            }
        }
    }

    // check Satisfiable and get model
    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    
    fclose(fp);
}
