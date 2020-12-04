#include <stdio.h>
#define SIZE 3

void createMatrix(int a[][SIZE], int b[][SIZE], int rowA,int colA, int rowB, int colB)
{
  printf("macierz A\n");
  for(int i=0; i<rowA; i++)
    for(int j=0; j<colA; j++)
      {
	printf("a%d%d: ",i+1,j+1);
	scanf("%d",&a[i][j]);
      }
  
  printf("macierz B\n");
  for(int i=0; i<rowB; i++)
    for(int j=0; j<colB; j++)
      {
	printf("b%d%d: ",i+1,j+1);
	scanf("%d",&b[i][j]);
      }
}

void printMatrix(int matrix[][SIZE], int row, int col)
{
  printf("macierz:\n");
  for(int i=0; i<row; ++i)
    for(int j=0; j<col; ++j)
      {
	printf("%d  ",matrix[i][j]);
	if(j==col-1)
	  printf("\n\n");
      }
}
void addMatrix(int a[][SIZE],int b[][SIZE],int c[][SIZE], int rowA, int colA,int rowB,int colB,int sign)
{
  if(sign!=0)
    sign=-1;
  else
    sign=0;
  for(int i=0;i<rowA;i++)
    {
      for(int n=0;n<colA;n++)
	{
	  c[i][n] = a[i][n]+b[i][n]*-1;
	}
    }
  
}
void multiplyMatrix(int a[][SIZE],int b[][SIZE],int out[][SIZE], int rowA, int colA,int rowB,int colB)
{
  for(int i=0;i<rowA;i++)
    {
      for(int n=0;n<rowB;n++)
	{
	  for(int k=0; k<colB;k++)
	    {
	      out[i][n]+= a[i][k] * b[k][n];
	    }
	}

    }
}

