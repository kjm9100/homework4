#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* �Լ� ���� */
int** create_matrix(int row, int col); // ��� ����(���� �Ҵ� �̿�) �Լ� 
void print_matrix(int** matrix, int row, int col); // ��� ��� �Լ�
int free_matrix(int** matrix, int row, int col); // ������ ���(���� �Ҵ�)�� �޸� ���� �Լ�
int fill_data(int** matrix, int row, int col); // ��� ���а� �ʱ�ȭ �Լ�
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // ��� �� ��� �Լ�
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // ��� �� ��� �Լ�
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // ��ġ��� ���� �Լ�
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // ��� �� ��� �Լ�

int main()
{

    char command;
    printf("[----- [������]  [2021041068] -----]\n");

    int row=0, col=0;
    srand(time(NULL)); // �õ尪 �ʱ�ȭ(rand �Լ� ��� �� �Ź� �������� �����ϱ� ����)

    printf("Input row and col : ");
    /* ����� ��� ���� �Է¹޴´�. ����� �հ� ���� ���� ����� ũ�Ⱑ ���ƾ� �ϱ⿡
    �ش� ��� ���� �޾� ��� a�� b�� �����Ѵ�. */
    scanf("%d %d", &row, &col);

    /* ��� a, b�� a�� ��ġ����� ����(���� �Ҵ� �̿�) */ 
    int** matrix_a = create_matrix(row, col);
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");
    // ��� a, b�� ����� �������� �ʾ��� ���, ������ ����� �ǹ��ϴ� �� -1�� ��ȯ�ϰ� ���� 
    if (matrix_a == NULL || matrix_b == NULL || matrix_a_t == NULL) {return -1;}

    do{
        // ��� ���� �޴� ���
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // ��� ����Ű ����

        switch(command) {
        case 'z': case 'Z': // z, Z ����Ű ���� ��, ��� a, b �ʱ�ȭ
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P': // p, P ����Ű ���� ��, ��� a, b ���
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A': // a, A ����Ű ���� ��, ��� �� a+b ��� �� ��� ���
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S': // s, S ����Ű ���� ��, ��� �� a-b ��� �� ��� ���
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T': // t, T ����Ű ���� ��, ��� a�� ��ġ���� ��ġ��� a_t�� ����� ���
            printf("Transpose matrix_a \n");
            printf("matrix_a\n"); 
            /* ��ġ��� a_t�� ��� a�� ���� ����, ���� ������ ���⿡ 
            ������ ��� a�� col����, ���� ��� a�� row���� �Ѱ��ش�. */
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M': // m, M ����Ű ���� ��, ��� a�� ��ġ��� a_t�� �� ��� �� ��� ���
            printf("Multiply matrix_a with transposed matrix_a \n");
            /* ��ġ����� ����⿡ ������ ��� a�� col����, ���� ��� a�� row���� �Ѱ��ش�. */
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q': // q, Q ����Ű ���� ��, ����� ���� �ߴ� ���� �Ҵ� �޸𸮵��� ���� �� ����
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // ��ġ��� ���� �ÿ��� �ప���� col, �������� row�� �Ѱ��ش�.
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default: //���� ����Ű�� �̿��� ���� ��쿡�� ��Ȯ�� �޽��� ���
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); // q, Q ����Ű �̿ܿ��� �ٸ� ������ ����� �� �ְ� �Ѵ�.

    return 1; // ���� ���� Ȯ���� ���� 1 ��ȯ
}

/* malloc�Լ��� �̿��� ��� ���� �Լ� ���� */
int** create_matrix(int row, int col)
{
    if(row <= 0 || col <=0) { // row�� col�� ���� 0���� ���� ��츦 ����� ��ó�� �˻�
    printf("Please check the size of row and col.\n");
    return NULL;
    }

   int** matrix_row=(int**)malloc(row*sizeof(int*)); // ��Ŀ��� ���� ����ϴ� ����������
  
    //���� ���� �Ҵ����� ����� �� �����͸� ���� ����ϴ� ������������ ��ҿ� �־� ��� ����
    for(int i=0; i<row; i++)
    {
        matrix_row[i] = (int*)malloc(col*sizeof(int));
    }   

    //matrix_row�� NULL �������� ��츦 ����� ��ó�� �˻�
    if(matrix_row == NULL) 
    {
        printf("Creating matrix Failed.\n");
        return NULL;
    }
    
    return matrix_row;   
}

/* ��� ��� �Լ� ���� */
void print_matrix(int** matrix, int row, int col)
{   
    // row�� col�� ���� 0���� ���� ���� matrix�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix==NULL)
    { 
    printf("Please check the size of row and col, or matrix\n");
    return;
    }

    int i, j;

    // ����� ���ʷ� ����Ѵ�.
     for(i=0;i<row;i++)
     {
        for(j=0; j<col; j++)
        {
            printf("%5d", matrix[i][j]);
        }
        
        printf("\n");
     }
    printf("\n");

    //matrix�� NULL�� ���� ���� ��ó�� �˻�
    if(matrix==NULL){
        printf("Check the matrix\n");
        return;
    }

}

/* ������ ����� �޸� �Ҵ� ���� �Լ� ����*/
int free_matrix(int** matrix, int row, int col)
{ 
    // row�� col�� ���� 0���� ���� ���� matrix�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix==NULL) {
    printf("Please check the size of row and col, or matrix\n");
    return -1;
    }

    int i;

    // ����� �� ���� ����Ű�� ���� �����Ѵ�.
    for(i=0; i<row; i++)
    {   
        free(matrix[i]);
    }

    // ����� ���� �����Ѵ�.
    free(matrix);

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

/* ������ ��Ŀ� �������� ���� �ִ� ��� �ʱ�ȭ �Լ� ���� */
int fill_data(int** matrix, int row, int col)
{   
    // row�� col�� ���� 0���� ���� ���� matrix�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix==NULL) {
    printf("Please check the size of row and col, or matrix\n");
    return -1;
    }

    int i, j;
    
    //��� �ʱ�ȭ
    for(i=0; i<row; i++)
    {
        for(j=0;j<col;j++)
        {
            // 0~19�� ���� �������� ��Ŀ� ����
            matrix[i][j]=rand()%20;
        }
    }
    
    //matrix�� NULL�� ���� ���� ��ó�� �˻�
    if(matrix==NULL){
        printf("Check the matrix\n");
        return -1;
    }

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

/* ��� a�� b�� ���� ��� a+b ����ϴ� �Լ� ���� */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    // row�� col�� ���� 0���� ���� ���� matrix_a/b�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix_a==NULL || matrix_b==NULL) {
    printf("Please check the size of row and col, or matrix_a/b\n");
    return -1;
    }

    int** matrix_sum = create_matrix(row, col); // ������� ���� ��� ����

    int i,j;

    // ��� a�� b�� ������ ���� ����� ��Ŀ� ����(�� ����� ũ��� ����.)
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            matrix_sum[i][j] = matrix_a[i][j]+matrix_b[i][j];
        }
    }

    // matrix_sum�� NULL�� ���� ����� ��ó�� �˻�
    if(matrix_sum==NULL)
    {
        printf("Memory allocation of matrix_sum Failed.");
        return -1;
    }

    // ����� ��� ���
    print_matrix(matrix_sum, row, col);

    // ����� ����� �޸� �Ҵ� ����
    free_matrix(matrix_sum, row, col);

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

/* ��� a�� b�� ���� ��� a-b ����ϴ� �Լ� ���� */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    // row�� col�� ���� 0���� ���� ���� matrix_a/b�� NULL�� ���� ����� ��ó�� �˻�
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

    // matrix_sub�� NULL�� ���� ����� ��ó�� �˻�
    if(matrix_sub==NULL)
    {
        printf("Memory allocation of matrix_sub Failed.");
        return -1;
    }

    // ����� ��� ���
    print_matrix(matrix_sub, row, col);
    // ��� �� ��� �޸� �Ҵ� ����
    free_matrix(matrix_sub, row, col);

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

/* ��ġ����� ���ϴ� �Լ� ���� */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    // row�� col�� ���� 0���� ���� ���� matrix, matrix_t�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix==NULL || matrix_t==NULL) {
    printf("Please check the size of row and col, matrix or matrix_t\n");
    return -1;
    }

    int i,j;

    // ����� ��ġ��Ų��.(���� ����� ��� ���� �ٲ� ��ġ�Ѵ�.)
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            matrix_t[i][j]=matrix[j][i];
        }
    }
    
    //matrix�� matrix_t�� NULL�� ���� ���� ��ó�� �˻�
    if(matrix==NULL || matrix_t==NULL){
        printf("Check the matrix or matrix_t\n");
        return -1;
    }

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

/* ��� a�� ��ġ����� ���� ���ϴ� �Լ� ���� */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    // row�� col�� ���� 0���� ���� ���� matrix_a/t�� NULL�� ���� ����� ��ó�� �˻�
    if(row <= 0 || col <=0 || matrix_a==NULL || matrix_t==NULL) {
    printf("Please check the size of row and col, or matrix_a/t\n");
    return -1;
    }

    int i,j,k;
    int ** matrix_aXt = create_matrix(row, row); // ��İ��� ���� ��� ����
    int temp_sum; //��İ� ����� ���� ���е��� ���� ���� ������ 

    // ����� ����� ���� 0���� �ʱ�ȭ
    for(int m=0; m<row; m++)
    {
        for(int n=0; n<row; n++)
        {
            matrix_aXt[m][n]=0;
        }
    }

    /* ���� ��İ� ��ġ����� ��(��İ� �˰����� ������.)
    ��İ� �˰��� : ���� ����� ��� ��ġ����� ���� ���е��� ���� �� */
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

    // matrix_aXt�� NULL�� ���� ���� ��ó�� �˻�
    if(matrix_aXt==NULL){
        printf("Memory allocation of matrix_aXt Failed.\n");
        return -1;
    }

    // ��İ� ��� ���
    print_matrix(matrix_aXt,row, row);
    
    // ��İ� ��� �޸� �Ҵ� ����
    free_matrix(matrix_aXt, row, row);

    return 1; // ���� ���� Ȯ�� ��ȯ��
}

