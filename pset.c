// pset.c

#include "pset.h"

#ifdef DEBUG
#define DPrint(f) f;
#else
#define DPrint(f) ;
#endif

#define ARRAY_SIZE 128
#define STRING_SIZE 1024

int** read_input(int* pN, int* pM){
    DPrint(printf("DEBUG > read_input(*pN = %d,*pM = %d)\n",*pN,*pM));
    int N = 0;
    int M = 0;

    // whether needs to check the NM or not.
    bool check_NM;
    if(*pN == 0 && *pM == 0) check_NM = true;
    else false;
    
    int* arr = (int*)malloc(sizeof(int)*ARRAY_SIZE);
    int arr_cnt = 0;
    int arr_totalcnt = ARRAY_SIZE;

    char ch[STRING_SIZE];
    bool firstrow= true;

    while(!feof(stdin)) {
        // Scan the input
        scanf("%s",ch);
        if(check_NM && firstrow)
            M++;
        if(getchar() == '\n') firstrow = false;
            
        // Convert the value and save in temporary array
        if(!strcmp(ch,"?")) arr[arr_cnt] = 0;
        else if(!strcmp(ch,"*")) arr[arr_cnt] = -1;
        else arr[arr_cnt] = atoi(ch);
        arr_cnt ++;
        
        // If array is exceeded, reallocate
        if(arr_cnt == arr_totalcnt){
            arr_totalcnt = arr_cnt + 128;
            arr = (int*)realloc(arr,sizeof(int)*arr_totalcnt);
        }
    }
    
    // Check N and M
    if(check_NM) { // if need to check
        N = arr_cnt / M;
        
        *pN = N;
        *pM = M;
    }
    else { // if don't need to check N and M, load the given N and M.
        N = *pN;
        M = *pM;
    }

    // Make an input array
    int** input = (int**) malloc(sizeof(int*)*N);
    for(int i = 0; i < N; i++) {
	    input[i] = (int*) malloc(sizeof(int)*M);
    }

    // Copy to new array
    for (int n = 0 ; n < N * M ; n++)
        input[n/M][n%M] = arr[n];

    DPrint(printf("DEBUG < read_input(*pN = %d,*pM = %d, arr_cnt = %d)\n",*pN,*pM, arr_cnt));
    return input;
}

void print_board(int N,int M, int** board) {
    DPrint(printf("DEBUG > print_board\n"));

	for(int i = 0; i < N; i++) {
			for(int j = 0; j < M; j++) {
				printf("%d ",board[i][j]);
			}
			printf("\n");
		}
	printf("\n");
    DPrint(printf("DEBUG < print_board\n"));
}

bool z3(int N, int M, int** board) {
    DPrint(printf("DEBUG > z3\n"));

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
		}
        else if(!strcmp("sat",satis)) {
			fscanf(fin,"%s",b); // model
			while(1) {

				fscanf(fin,"%s", a) ;
				if(!strcmp(")",a)) break;
				fscanf(fin," %s %s %s %s", s, b, b, t) ;

				int val = t[0] - '0';
				int col = s[1] - '0';
				int row = s[2] - '0';

                
                DPrint(printf("DEBUG in z3 %d %d %d %d %d\n",N,M,val,col,row));
				board[col-1][row-1] = val;
			}
		}
	}
    DPrint(printf("DEBUG < z3\n"));
	return true;
}

#if 0
int main(){
    int N = 0;
    int M = 0;
    int** input = read_input(&N,&M);

    printf("%d X %d\n", N,M);
    print_board(N,M,input);
}
#endif