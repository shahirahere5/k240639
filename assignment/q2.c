#include <stdio.h>
int main ()
{

	int num1;
	int num2;
	int temp;
	
	scanf("%d",&num1);
	scanf("%d",&num2);
	
	printf("num1 before: %d \n",num1);
	printf("num2 before: %d \n",num2);
	
	temp = num1;
	num1 = num2;
	num2 = temp;
	
	printf("num1 after: %d \n",num1);
	printf("num2 after: %d \n",num2);
}	