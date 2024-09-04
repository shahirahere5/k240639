#include <stdio.h>
int main() {
	int principal;
	int rate_interest;
	int time_period;
	int interest;
	
	printf("enter total amount between rs.100 to rs.1000000: \n");
	scanf("%d", &principal);
	
	printf("enter rate interest between 5 to 10 percent: \n");
	scanf("%d", &rate_interest);
	
	printf("enter time period between 1 to 10 years: \n");
	scanf("%d", &time_period);
	
	interest= (rate_interest*time_period*principal) /100;
	principal = principal - interest;
	
	printf("interest is: %d \n",interest);
	printf("remaining amount is %d \n",principal);
}
