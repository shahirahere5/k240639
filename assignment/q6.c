#include <stdio.h>
int main() {
	int x1;
	int x2;
	int y1;
	int y2;
	int change_in_y;
	int change_in_x;
	float gradient;
	
	x1 = 3;
	x2 = 5;
	y1 = 2;
	y2 = 4;
	
	change_in_y = y2 - y1;
	change_in_x = x2 - x1;
	
	gradient = change_in_y / change_in_x;
	
	printf("gradient is: %.3f \n" , gradient);
}
