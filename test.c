#include <stdio.h>

int main()
{
  for( int i=0; i<100; i++)
    {
      if(!(i%15))
	printf("fizzbuzz\n");
      else if(!(i%5))
	printf("fizz\n");
      else if(!(i%3))
	printf("buzz\n");
      else
	printf("%d\n",i);
    }
}
