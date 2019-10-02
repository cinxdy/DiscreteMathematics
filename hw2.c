// 21800409 Jiyoung Shin

#include <stdio.h>
#define N 5
#define M 5
#define K 5

int main (){
    int x,y,k;

    // scan the input file
    int input[N][M];
    char s;

    for (y = 0 ; y < N ; y++){
        for ( x = 0 ; x < M ; x++){
            scanf("%c ",&s);

            if(s=='?') input[y][x] = 0;
            else input[y][x] = s - '0';
        }
    }

    // write formula
	FILE * fp = fopen("formula", "w") ;

    char c[5] = {'a','b','c','d','e'};

    for(int kk = K ; kk > 0 ; kk--){
        fprintf(fp,"(push)\n");
        for(int k = 0; k < kk ; k++){

            for (y = 1 ; y <= N ; y++)
                for (x = 1 ; x <= M ; x++)
                    fprintf(fp, "(declare-const %c%d%d Int)\n", c[k],y, x) ;

            // 0<= a_yx <=1
            for (y = 1 ; y <= N ; y++)
                for (x = 1 ; x <= M ; x++)
                    fprintf(fp, "(assert (and (<= 0 %c%d%d) (<= %c%d%d 1))) \n", c[k],y, x,c[k], y, x) ;

            // Q0 : sum of its neighbors is itself (?)
            for (y = 1 ; y <= N ; y++){
                for (x = 1 ; x <= M ; x++){
                    if(input[y-1][x-1]>0){
                        fprintf(fp,"(assert (= (+ \n");
                        for(int m = -1 ; m <= 1 ; m++){
                            for(int n = -1 ; n <= 1 ; n++){
                                if(0<y+m && y+m<=N && 0<x+n && x+n<=M)
                                    fprintf(fp,"%c%d%d ",c[k],y+m,x+n);
                            }
                        }
                        fprintf(fp,") %d))\n",input[y-1][x-1]);
                    }
                }
            }
        }
    
        fprintf(fp,"(assert (or \n");
        for (y = 1 ; y <= N ; y++){
            for (x = 1 ; x <= M ; x++){
                fprintf(fp,"(distinct ");
                for (int k = 0 ; k < kk ; k++){
                    fprintf(fp,"%c%d%d ",c[k],y,x);
                }
                fprintf(fp,")\n");
            }
        }
        fprintf(fp,"))");
    
        // check Satisfiable and get model
        fprintf(fp, "(check-sat)\n (get-model)\n");
        fprintf(fp,"(pop)\n"); 
    }
    
    fclose(fp);
}