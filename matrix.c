#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* 함수 선언 */
int** create_matrix(int row, int col); // 행렬 생성(동적 할당 이용) 함수 
void print_matrix(int** matrix, int row, int col); // 행렬 출력 함수
int free_matrix(int** matrix, int row, int col); // 생성된 행렬(동적 할당)의 메모리 해제 함수
int fill_data(int** matrix, int row, int col); // 행렬 성분값 초기화 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 합 계산 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 행렬 차 계산 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 전치행렬 생성 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 행렬 곱 계산 함수

int main()
{

    char command;
    printf("[----- [김지민]  [2021041068] -----]\n");

    int row=0, col=0;
    srand(time(NULL)); // 시드값 초기화(rand 함수 사용 시 매번 랜덤값을 생성하기 위함)

    printf("Input row and col : ");
    /* 행렬의 행과 열을 입력받는다. 행렬의 합과 차를 위해 행렬의 크기가 같아야 하기에
    해당 행과 열을 받아 행렬 a와 b를 생성한다. */
    scanf("%d %d", &row, &col);

    /* 행렬 a, b와 a의 전치행렬을 생성(동적 할당 이용) */ 
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");
    // 행렬 a, b가 제대로 생성되지 않았을 경우, 비정상 출력을 의미하는 값 -1을 반환하고 종료 
    if (matrix_a == NULL || matrix_b == NULL || matrix_a_t == NULL) {return -1;}

    do{
        // 행렬 조작 메뉴 출력
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 행렬 조작키 선택

        switch(command) {
        case 'z': case 'Z': // z, Z 조작키 선택 시, 행렬 a, b 초기화
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': // p, P 조작키 선택 시, 행렬 a, b 출력
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': // a, A 조작키 선택 시, 행렬 합 a+b 계산 및 결과 출력
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': // s, S 조작키 선택 시, 행렬 차 a-b 계산 및 결과 출력
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': // t, T 조작키 선택 시, 행렬 a를 전치시켜 전치행렬 a_t를 만들고 출력
            printf("Transpose matrix_a \n");
            printf("matrix_a\n"); 
            /* 전치행렬 a_t는 행렬 a의 행을 열로, 열을 행으로 갖기에 
            행으로 행렬 a의 col값을, 열로 행렬 a의 row값을 넘겨준다. */
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': // m, M 조작키 선택 시, 행렬 a와 전치행렬 a_t의 곱 계산 및 결과 출력
            printf("Multiply matrix_a with transposed matrix_a \n");
            /* 전치행렬을 만들기에 행으로 행렬 a의 col값을, 열로 행렬 a의 row값을 넘겨준다. */
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': // q, Q 조작키 선택 시, 행렬을 위해 했던 동적 할당 메모리들을 해제 및 종료
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // 전치행렬 해제 시에는 행값으로 col, 열값으로 row을 넘겨준다.
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //위의 조작키들 이외의 조작 경우에는 재확인 메시지 출력
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); // q, Q 조작키 이외에는 다른 조작을 계속할 수 있게 한다.

    return 1; // 정상 종료 확인을 위한 1 반환
}

/* malloc함수를 이용한 행렬 생성 함수 정의 */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <=0) { // row와 col의 값이 0보다 작을 경우를 대비한 전처리 검사
    printf("Please check the size of row and col.\n");
    return NULL;
    }

   int** matrix_row=(int**)malloc(row*sizeof(int*)); // 행렬에서 행을 담당하는 이중포인터
  
    //열을 동적 할당으로 만들어 그 포인터를 행을 담당하는 이중포인터의 요소에 넣어 행렬 생성
    for(int i=0; i<row; i++)
    {
        matrix_row[i] = (int*)malloc(col*sizeof(int));
    }   

    //matrix_row가 NULL 포인터일 경우를 대비한 후처리 검사
    if(matrix_row == NULL) 
    {
        printf("Creating matrix Failed.\n");
        return NULL;
    }
    
    return matrix_row;   
}

/* 행렬 출력 함수 정의 */
void print_matrix(int** matrix, int row, int col)
{   
    // row와 col의 값이 0보다 작을 경우와 matrix가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix==NULL)
    { 
    printf("Please check the size of row and col, or matrix\n");
    return;
    }

    int i, j;

    // 행렬을 차례로 출력한다.
     for(i=0;i<row;i++)
     {
        for(j=0; j<col; j++)
        {
            printf("%5d", matrix[i][j]);
        }
        
        printf("\n");
     }
    printf("\n");

    //matrix가 NULL일 때를 위한 후처리 검사
    if(matrix==NULL){
        printf("Check the matrix\n");
        return;
    }

}

/* 생성된 행렬의 메모리 할당 해제 함수 정의*/
int free_matrix(int** matrix, int row, int col)
{ 
    // row와 col의 값이 0보다 작을 경우와 matrix가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix==NULL) {
    printf("Please check the size of row and col, or matrix\n");
    return -1;
    }

    int i;

    // 행렬의 각 행이 가리키는 열을 해제한다.
    for(i=0; i<row; i++)
    {   
        free(matrix[i]);
    }

    // 행렬의 행을 해제한다.
    free(matrix);

    return 1; // 정상 종료 확인 반환값
}

/* 생성된 행렬에 무작위로 값을 넣는 행렬 초기화 함수 정의 */
int fill_data(int** matrix, int row, int col)
{   
    // row와 col의 값이 0보다 작을 경우와 matrix가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix==NULL) {
    printf("Please check the size of row and col, or matrix\n");
    return -1;
    }

    int i, j;
    
    //행렬 초기화
    for(i=0; i<row; i++)
    {
        for(j=0;j<col;j++)
        {
            // 0~19의 값을 무작위로 행렬에 저장
            matrix[i][j]=rand()%20;
        }
    }
    
    //matrix가 NULL일 때를 위한 후처리 검사
    if(matrix==NULL){
        printf("Check the matrix\n");
        return -1;
    }

    return 1; // 정상 종료 확인 반환값
}

/* 행렬 a와 b의 합인 행렬 a+b 계산하는 함수 정의 */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    // row와 col의 값이 0보다 작을 경우와 matrix_a/b가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix_a==NULL || matrix_b==NULL) {
    printf("Please check the size of row and col, or matrix_a/b\n");
    return -1;
    }

    int** matrix_sum = create_matrix(row, col); // 행렬합을 위한 행렬 생성

    int i,j;

    // 행렬 a와 b의 성분을 더해 행렬합 행렬에 저장(두 행렬의 크기는 같다.)
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j]+matrix_b[i][j];
        }
    }

    // matrix_sum이 NULL일 때를 대비한 후처리 검사
    if(matrix_sum==NULL)
    {
        printf("Memory allocation of matrix_sum Failed.");
        return -1;
    }

    // 행렬합 행렬 출력
    print_matrix(matrix_sum, row, col);

    // 행렬합 행렬의 메모리 할당 해제
    free_matrix(matrix_sum, row, col);

    return 1; // 정상 종료 확인 반환값
}

/* 행렬 a와 b의 차인 행렬 a-b 계산하는 함수 정의 */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    // row와 col의 값이 0보다 작을 경우와 matrix_a/b가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix_a==NULL || matrix_b==NULL) {
    printf("Please check the size of row and col, or matrix_a/b\n");
    return -1;
    }

    int** matrix_sub = create_matrix(row, col);
    int i,j;

    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            matrix_sub[i][j] = matrix_a[i][j]-matrix_b[i][j];
        }
    }

    // matrix_sub이 NULL일 때를 대비한 후처리 검사
    if(matrix_sub==NULL)
    {
        printf("Memory allocation of matrix_sub Failed.");
        return -1;
    }

    // 행렬차 행렬 출력
    print_matrix(matrix_sub, row, col);
    // 행렬 차 행렬 메모리 할당 해제
    free_matrix(matrix_sub, row, col);

    return 1; // 정상 종료 확인 반환값
}

/* 전치행렬을 구하는 함수 정의 */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    // row와 col의 값이 0보다 작을 경우와 matrix, matrix_t가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix==NULL || matrix_t==NULL) {
    printf("Please check the size of row and col, matrix or matrix_t\n");
    return -1;
    }

    int i,j;

    // 행렬을 전치시킨다.(기존 행렬의 행과 열을 바꿔 배치한다.)
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            matrix_t[i][j]=matrix[j][i];
        }
    }
    
    //matrix와 matrix_t가 NULL일 때를 위한 후처리 검사
    if(matrix==NULL || matrix_t==NULL){
        printf("Check the matrix or matrix_t\n");
        return -1;
    }

    return 1; // 정상 종료 확인 반환값
}

/* 행렬 a와 전치행렬의 곱을 구하는 함수 정의 */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    // row와 col의 값이 0보다 작을 경우와 matrix_a/t가 NULL일 때를 대비한 전처리 검사
    if(row <= 0 || col <=0 || matrix_a==NULL || matrix_t==NULL) {
    printf("Please check the size of row and col, or matrix_a/t\n");
    return -1;
    }

    int i,j,k;
    int ** matrix_aXt = create_matrix(row, row); // 행렬곱을 위한 행렬 생성
    int temp_sum; //행렬곱 계산을 위해 성분들의 곱의 합을 저장할 

    // 곱행렬 계산을 위해 0으로 초기화
    for(int m=0; m<row; m++)
    {
        for(int n=0; n<row; n++)
        {
            matrix_aXt[m][n]=0;
        }
    }

    /* 기존 행렬과 전치행렬의 곱(행렬곱 알고리즘을 따른다.)
    행렬곱 알고리즘 : 기존 행렬의 행과 전치행렬의 열의 성분들의 곱의 합 */
    for(k=0; k<row; k++)
    {
        for(i=0; i<row; i++)
        { 
            for(j=0; j<col; j++)
            {
               matrix_aXt[k][i] += ((matrix_a[k][j])*(matrix_t[j][i]));
            }
        }
    }

    // matrix_aXt가 NULL일 때를 위한 후처리 검사
    if(matrix_aXt==NULL){
        printf("Memory allocation of matrix_aXt Failed.\n");
        return -1;
    }

    // 행렬곱 행렬 출력
    print_matrix(matrix_aXt,row, row);
    
    // 행렬곱 행렬 메모리 할당 해제
    free_matrix(matrix_aXt, row, row);

    return 1; // 정상 종료 확인 반환값
}

