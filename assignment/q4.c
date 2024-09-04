#include <stdio.h>
int main() {
	int distance; //in km
	distance = 1207;
	
	int fwd_fuel_price; //in litre
	fwd_fuel_price = 118;
	
	int bwd_fuel_price; //in litre
	bwd_fuel_price = 123;
	
	float fuel_average;
	printf("what is your fuel average?(please refrain from negative number): \n");
	scanf("%f", &fuel_average);
	
	float fuel_consumed;
	fuel_consumed = (distance /fuel_average) *2;
	
	float fwd_fuel_cost;
	fwd_fuel_cost = (distance/fuel_average) * fwd_fuel_price;
	
	float bwd_fuel_cost;
	bwd_fuel_cost = (distance/fuel_average) * bwd_fuel_price;
	
	float total_cost;
	total_cost = fwd_fuel_cost + bwd_fuel_cost;
	
	printf("total fuel consumed is %f: \n",fuel_consumed); //in litre
	printf("total fuel cost is: %f \n",total_cost); 
}
