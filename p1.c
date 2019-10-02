// 21800409 Jiyoung Shin
// 21700613 Sb

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void print_board();
bool z3();
int main (){
    int x,y,k;

    //scan the input file
    int input[9][9];
    char c;
    for (y = 0 ; y < 9 ; y++){
        for ( x=0 ; x < 9 ; x++){
            scanf("%c ",&c);

            if(c=='?') input[y][x] = 0;
            else if(c=='*') input[y][x] = -1;
            else input[y][x] = c - '0';
        }
    }

    // write formula
	FILE * fp = fopen("formula", "w") ;

	for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
			fprintf(fp, "(declare-const a%d%d Int)\n", y, x) ;

    // debug
    #ifdef DEBUG
    fprintf(fp,"Debug Mode\n");
    for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
            fprintf(fp,"input[%d][%d] = %d\n",y,x,input[y-1][x-1]);
    #endif

    // Q0 : specific number
    for (y = 1 ; y <= 9 ; y++)
		for (x = 1 ; x <= 9 ; x++)
            if(input[y-1][x-1]>0)
			    fprintf(fp, "(assert (= a%d%d %d))\n", y, x, input[y-1][x-1]) ;


    // Q1 : All values are between 1-9.
    for (y = 1 ; y <= 9 ; y++)
        for (x = 1 ; x <= 9 ; x++)
        fprintf(fp, "(assert (and (<= 1 a%d%d) (<= a%d%d 9)))\n",y,x,y,x);

    // Q2 : Every row has only one every value.
    for (k = 1 ; k <=9 ; k++){
        for (y = 1 ; y <= 9 ; y++) {
            fprintf(fp,"(assert (= (+ ");
            for (x =1 ; x <= 9 ; x++){
                fprintf(fp,"\t(ite (= a%d%d %d) 1 0)\n",y,x,k);
            }
            fprintf(fp, ") 1))\n") ;
        }
    }

    // Q3 : Every column has only one every value.
    for (k = 1 ; k <=9 ; k++){
        for (x = 1 ; x <= 9 ; x++) {
            fprintf(fp,"(assert (= (+ ");
            for (y =1 ; y <= 9 ; y++){
                fprintf(fp,"\t(ite (= a%d%d %d) 1 0)\n",y,x,k);
            }
            fprintf(fp, ") 1))\n") ;
        }
    }

    // Q4 : Every box has only one every value.
    for(int m = 0 ; m < 9 ; m+=3){
        for(int n = 0 ; n < 9 ; n+=3){

            for (k = 1 ; k <=9 ; k++){
                fprintf(fp,"(assert (= (+ ");
                for (y = m+1 ; y <= m+3 ; y++){
                    for (x = n+1 ; x <= n+3 ; x++) {
                        fprintf(fp,"\t(ite (= a%d%d %d) 1 0)\n",y,x,k);

                        #ifdef DEBUG
                            fprintf(fp,"Debug Mode\n");
                            fprintf(fp,"y,x = %d %d", y,x);
                        #endif
                    }
                }
            fprintf(fp, ") 1))\n") ;
            }
        }
    }

    // Q5 : All star value is aristerisk
    #ifdef DEBUG
        fprintf(fp,"Debug Mode\n");
        fprintf(fp,"Q5\n");
    #endif

    for (k = 1 ; k <= 9 ; k++){
        fprintf(fp,"(assert (<= (+ \n");
        for (y = 1 ; y <= 9 ; y++) {
            for (x = 1 ; x <= 9 ; x++){
                if (input[y-1][x-1] == -1)
                    fprintf(fp,"\t(ite (= a%d%d %d) 1 0)\n",y,x,k);
            }
        }
        fprintf(fp, ") 1))\n");
    }

    fprintf(fp, "(check-sat)\n(get-model)\n") ;
    
	fclose(fp) ;

	if(z3()) print_board();
}
int board[10][10];
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
		if(!strcmp("unsat",satis)) {
			fscanf(fin,"%s",b); // error message absort
			printf("No solution\n");
			return false;
			break;
		} else if(!strcmp("sat",satis)) {
			fscanf(fin,"%s",b); // error message absort
			while(1) {

				fscanf(fin,"%s", a) ;
				if(strcmp(")",a) == 0) break;
				fscanf(fin," %s %s %s %s", s, b, b, t) ;

				int val = t[0] - '0';
				int col = s[1] - '0';
				int row = s[2] - '0';

				board[col][row] = val;
			}
		}
	}
	return true;
}
void print_board() {
	for(int i = 1; i <= 9; i++) {
			for(int j = 1; j <= 9; j++) {
				printf("%d ",board[i][j]);
			}
			printf("\n");
		}
	printf("\n");
}
