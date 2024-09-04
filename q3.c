#include <stdio.h>
int main()
{
	float tax_rate;
	float salary;
	float tax;
	
	printf("enter percent tax rate: \n");
	scanf("%f",&tax_rate);
	
	printf("enter your salary: \n");
	scanf("%f",&salary);
	
	tax = (tax_rate / 100) * salary;
	printf("tax paid is: %f \n",tax);
	
	salary = salary - tax;
	printf("remaining salary is: %f", salary);
}	