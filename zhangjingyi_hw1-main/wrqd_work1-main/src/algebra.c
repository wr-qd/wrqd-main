#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

Matrix add_matrix(Matrix a, Matrix b)
{
    while(a.rows==b.rows&&a.cols==b.cols){
        int rowa=a.rows;
        int cola=a.cols;
        Matrix ans = create_matrix(rowa,cola);
        for(int i=0;i<rowa;i++){
            for(int j=0;j<cola;j++){
                ans.data[i][j]=a.data[i][j]+b.data[i][j];
            }
        }
        return ans;
    }
    printf("Error: Matrix a and b must have the same rows and cols.\n");
    return create_matrix(0, 0);
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    while(a.rows==b.rows&&a.cols==b.cols){
        int rowa=a.rows;
        int cola=a.cols;
        Matrix ans = create_matrix(rowa,cola);
        for(int i=0;i<rowa;i++){
            for(int j=0;j<cola;j++){
                ans.data[i][j]=a.data[i][j]-b.data[i][j];
            }
        }
        return ans;
    }
    printf("Error: Matrix a and b must have the same rows and cols.\n");
    return create_matrix(0, 0);
}

Matrix mul_matrix(Matrix a, Matrix b)
{
    while(a.cols==b.rows){
        int rowa=a.rows;
        int cola=a.cols;
        Matrix ans = create_matrix(rowa,cola);
        for(int i=0;i<rowa;i++){
            for(int j=0;j<cola;j++){
                for(int k=0;k<cola;k++){
                    ans.data[i][j]+=a.data[i][k]+b.data[k][j];
                }
            }
        }
        return ans;
    }
    printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
    return create_matrix(0, 0);
}

Matrix scale_matrix(Matrix a, double k)
{
    int rowa=a.rows;
    int cola=a.cols;
    Matrix ans = create_matrix(rowa,cola);
    for(int i=0;i<rowa;i++){
        for(int j=0;j<cola;j++){
                ans.data[i][j]=a.data[i][j]*k;
            }
        }
    return ans;
    return create_matrix(0, 0);
}

Matrix transpose_matrix(Matrix a)
{
    
    int rowa=a.rows;
    int cola=a.cols;
    Matrix ans = create_matrix(rowa,cola);
    for(int i=0;i<rowa;i++){
        for(int j=0;j<cola;j++){
                ans.data[i][j]=a.data[j][i];
            }
        }
    return ans;
    return create_matrix(0, 0);
}

double det_matrix(Matrix a)
{
    double key=0;
    int num=a.rows;
    if(a.rows!=a.cols){
        printf("The input matrix must be a square matrix");
        return 0;
    }
    if(num==1){
        return a.data[0][0];
    }
    for(int k=0;k<num;k++){
        Matrix ans = create_matrix(num-1,num-1);
        for(int i=0;i<num-1;i++){
            for(int j=0;j<num;j++){
                if(j<k){
                    ans.data[i][j]=a.data[i+1][j];
                }else if(j>k){
                    ans.data[i][j-1]=a.data[i+1][j];
                }
            }
        }
        key+=pow(-1,k)*a.data[0][k]*det_matrix(ans);
    }
    return key;
}

Matrix inv_matrix(Matrix a)
{
    int num=a.rows;
    if(a.rows!=a.cols){
        printf("The matrix must be a square matrix.");
        return create_matrix(0, 0);
    }
    if(det_matrix(a)==0){
        printf("Error: The matrix is singular.");
    }
    Matrix ans = create_matrix(num,num);
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++){
                Matrix tmp = create_matrix(num-1,num-1);
                for(int k=0;k<num;k++){
                    for(int q=0;q<num;q++){
                        if(k<i&&q<j){
                            tmp.data[k][q]=a.data[k][q];
                        }else if(k>i&&q<j){
                            tmp.data[k-1][q]=a.data[k][q];
                        }else if(k<i&&q>j){
                            tmp.data[k][q-1]=a.data[k][q];
                        }else if(k>i&&q>j){
                            tmp.data[k-1][q-1]=a.data[k][q];
                        }
                    }   
                }
                double key=det_matrix(tmp)*pow(-1,i+j);
                ans.data[j][i]=key/det_matrix(a);
            }
        }
    return ans;
    
}

int rank_matrix(Matrix a)
{
    int r;
    int num=a.rows;
    for(int i=0;i<num-1;i++){
        for(int k=i+1;k<num;k++){
            if(a.data[k][i]!=0){
                double mul=a.data[i][i]/a.data[k][i];
                for(int q=i;q<num;q++){
                    a.data[k][q]=a.data[k][q]*mul-a.data[i][q];
                }
            }
        }
    }
    int flag=0;
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(a.data[i][j]!=0){
                flag-=1;
                break;
            }
        }
        flag+=1;
    }
    return num-flag;
    return 0;
}

double trace_matrix(Matrix a)
{
    double key=0;
    int num=a.rows;
    if(a.rows!=a.cols){
        printf("The matrix must be a square matrix.");
        return 0;
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            if(i==j){
                key+=a.data[i][j];
            }
        }
    }
    return key;
    return 0;
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}