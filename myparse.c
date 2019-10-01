#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int board[5000][5000];

    int max_col = 0;
    int max_row = 0;
    
void print_board() {
		for(int i = 0; i < max_col; i++) {
			for(int j = 0; j < max_row; j++) {
				printf("%d ",board[i][j]);
			}
			printf("\n");
		}
}

int main ()
{
	int i, j, k;

    char ch[5] = {'a','b','c','d','e'};
  
    char satis[128];
    char a[128] ;
    char b[128] ;
    char s[128] ;
    char t[128] ;

    	gets(satis);

	if(strcmp("unsat",satis) == 0) {
		gets(b); // error message absort
		printf("No solution\n");
	} else if(strcmp("sat",satis) == 0) {
//		printf("sat!\n");

		gets(b); // get-model

		
		while(1) {

			scanf("%s", a) ;
			if(strcmp(")",a) == 0) break;
			scanf(" %s %s %s %s", s, b, b, t) ;

			int val = t[0] - '0';
			int col = s[1] - '0';
			if(col > max_col) max_col = col;
			int row = s[2] - '0';
			if(row > max_row) max_row = row;
			board[col][row] = val;		

		}
	}
	print_board();
}
