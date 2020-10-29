#include <stdio.h>
#define MAX_SIZE 3

void createMatrix(int a[][3], int b[][3], int rowA,int colA, int rowB, int colB)
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

void printMatrix(int matrix[][3], int row, int col)
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
void addMatrix(int a[][3],int b[][3],int c[][3], int rowA, int colA,int rowB,int colB,int sign)
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
void multiplyMatrix(int a[][3],int b[][3],int out[][3], int rowA, int colA,int rowB,int colB)
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

int main()
{

  int c[3][3];
  int d[3][3] = {
    {0,0,0},
    {0,0,0},
    {0,0,0}
  };
  int rowA =3;
  int colA =3;
  int rowB =3;
  int colB =3;
  
  int a[3][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };

  int b[3][3] = {
    {1,2,3},
    {4,5,6},
    {7,8,9}
  };
  createMatrix(a,b,rowA,colA,rowB,colB);
  addMatrix(a,b,c,rowA,colA,rowB,colB,0);
  printMatrix(c,rowA,colA);
  multiplyMatrix(a,b,d,rowA,colA,rowB,colB);
  printMatrix(d,rowA,colA);

  
}
