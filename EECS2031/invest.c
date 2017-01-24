#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main() {
	
	char c[1000];
	float current = 0;
	FILE *fp = fopen("in.txt", "r");
	float initialCash = 10000;
	float cash = 10000;
	float change = 0;
	int consecutiveNegative = 0; /* counts decreased consecutive days, resets at 2 or break. */
	int consecutive5 = 0; /* counts 5% increased consecutive days, resets at 2 or break. */
	int consecutive10 = 0; /* counts 10% increased consecutive days, resets at 2 or break. */
	int noStocks = 0;  /* number of stocks owned */
	int firstday = 1; /* boolean to check for first day */
	float previousVal; /* previous value for comparison */
	float previousVal2; 
	int i;
	
	while(fgets(c,1000,fp)) {
		current = atof(c);
		if(firstday) {
			firstday = 0;
			previousVal = current;
		}
		
		if(consecutive10 >= 2) {
				/* printf("sold all   "); */
				cash = cash + (noStocks * previousVal);
				noStocks = 0;
		}
		if(consecutive5 >= 2 && cash > 0) {
				/* printf("bought half   "); */
				noStocks = noStocks + ((cash / 2) / previousVal);
				cash = cash - ((int)((cash / 2) / previousVal)*previousVal);
		}
		if(consecutiveNegative >= 2 && cash > 0) {
				/* printf("bought all   "); */
				noStocks = noStocks + (cash / previousVal);
				cash = cash - (((int)(cash/previousVal)) * previousVal);
		}
		change = ((current - previousVal)/ previousVal) * 100;
		
		/* printf("current: %.2f ----> change: %.2f \n", current, change);*/
		
		if(change > 10) {
			consecutive10++;
			consecutive5++;
			consecutiveNegative = 0;
			previousVal2 = previousVal;
			previousVal = current;
		}
		if(change > 5) {
			consecutive5++;
			consecutiveNegative = 0;
			previousVal2 = previousVal;
			previousVal = current;

		}
		else if(change >= 0) {
			consecutive5 = 0;
			consecutive10 = 0;
			consecutiveNegative = 0;
			previousVal2 = previousVal;
			previousVal = current;
			/* printf("No Action   "); */
		}
		else if(change < 0) {
			consecutiveNegative++;
			consecutive5 = 0;
			consecutive10 = 0;
			previousVal2 = previousVal;
			previousVal = current;

		}
		
		/* printf("current: %.2f ----> change: %.2f \n", current, change); */
	}
	if((cash + (noStocks * previousVal2)) > initialCash) {
		printf("Gain:$%.2f \n", ((cash + (noStocks * previousVal2)) - initialCash)); 
	}
	else {
		printf("Loss:$%.2f \n", (initialCash - (cash + (noStocks * previousVal2)))); 
	}
	
	fclose(fp);
	
	return 0;
}
