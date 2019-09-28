#include <stdio.h>
#include <string.h>

char board[9][9] ;

int main ()
{
	int i, j, k;

	char b[128] ;
	char s[128] ;
	char t[128] ;

	scanf("%s %s", b, b) ;
	for (k = 0 ; k < 81 ; k++) {
		scanf("%s %s %s %s %s", b, s, b, b, t) ;

		i = s[1] - '0' ;
		j = s[2] - '0' ;

		board[i-1][j-1] = t[0] - '0' ;

        #ifdef DEBUG
        if(board[i][j]>0)
        printf("board[%d][%d] = %d\n",i,j,board[i-1][j-1]);
        #endif
	}

	for (i = 1 ; i <= 9 ; i++) {
		for (j = 1 ; j <= 9 ; j++) {
			printf("%d ", board[i-1][j-1]) ;
		}
		printf("\n") ;
	}
}