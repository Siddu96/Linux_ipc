#include<stdio.h>
int global = 500;
int main()
{
 static int i;
 static int i2 = 10;
 printf("Hello World\n");
 return 0;
}
