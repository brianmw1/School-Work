#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int main() 
{
	int n; /* n lines of records */
	int ID; /* student id */
	char firstN[100]; /* student first name */
	char lastN[100]; /* student last name */
	int final; /* final exam mark 60% weight */
	int mid; /* midterm test mark 25% weight */
	float quiz1; /* quiz 1 5% weight */
	float quiz2; /* quiz 2  5% weight */
	float quiz3; /* quiz 3 5% weight */
	char cmd[300]; /* Possible commands to be input by keyboard */
	int line = 1; /* line counter */
	float perA; /* percentage of students with 80% or more average. */
	
	
	/* scan for integer n */
	if(!scanf("%d", &n)) {
		return (1);
	}
	
	/* check if integer n is larger than 0 or less than 0, if true end program */
	if(n > 50 || n < 0) {
		return (1);
	}
	
	float tMark[50]; /* array of total marks */
	int fID[50] = {0}; /* array of failing student id's */ 
	int topID[50] = {0}; /* array of top students */
	int aID[50] = {0}; /* array of A student's ids */
	char tLast[50][999] = {0}; /* last name of top last students */
	char aLast[50][999] = {0}; /* array of A student's last names */
	int aCounter = 0; /* used to count the amount of students who have a grade higher than 80% */
	int fCounter = 0; /* used for anomaly command, to count amount of studnets with grade F (<50%) */
	int anomaly = 0; /* boolean for anomaly command */
	int index = 0; /* index based on the current line */
	float topMark = 0; /* current top mark */
	
	/* scan through n lines of records */
	
	 while(line <= n) {
		index = line - 1;
		 scanf("%u %s %s %d %d %f %f %f \n", 
			&ID, firstN, lastN, &final, &mid, &quiz1, &quiz2, &quiz3);
		
		//printf("%u %s %s %d %d %f %f %f \n", 
			//ID, firstN, lastN, final, mid, quiz1, quiz2, quiz3);  
		 
		 /* calc mark assign a % grade*/
		 tMark[index] = ((final * 0.6) + (mid * 0.25) + ((quiz1*10) * 0.05) + ((quiz2*10) * 0.05) + ((quiz3*10) * 0.05));
		 
		 /* set to array for F command */
		 if(tMark[index] < 50) {
			 fID[index] = ID;
			 fCounter++;
		 }
		 
		 /* set to array for top command */
		 if(tMark[index] > topMark) {
			 memset(topID, 0, sizeof(topID));  /* clear the current topID array if a new high mark has been determined */
			 memset(tLast, 0, sizeof(tLast));
			 topID[index] = ID;
			 strncpy(tLast[index], lastN, 999);
			 topMark = tMark[index];
		 }
		 else if((fabsf(tMark[index] - topMark) <= 0.005) && (tMark[index] >= topMark)) {
			 topID[index] = ID; /* check if current and previous are equal. Also check if previous is larger than it's prior element */ 
			 strncpy(tLast[index], lastN, 999);
			 topMark = tMark[index];
		}
		 
		 /* Set to array for students who got an A
			Find the percentage of students with 80% or more */
		 if(tMark[index] >= 80) {
			 aID[index] = ID;
			 strncpy(aLast[index], lastN, 999);
			 aCounter++;
		 }	 
		 line++;
	 }
	 
	 /* anomaly check */
	 if(((100 * aCounter / n) > 30 || (100 * fCounter / n) > 30) && n > 15) {
		 anomaly = 1;
	 }
	 
	 /* command lines of the input */
	 while(scanf("%s", cmd) != EOF) {
		
		/* display id of failing students */
		if(strcmp(cmd, "F") == 0) {
			 for(int i = 0 ; i < n ; i++) {
				 if(fID[i] != 0) {
					 printf("%u \n", fID[i]);
				 }
			 }
		 }
		 
		 /* display id of top students */
		 if(strcmp(cmd, "top") == 0) {
			 for(int j = 0 ; j < n ; j++) {
				 if(topID[j] != 0) {
					 printf("%u %s \n", topID[j], tLast[j]);
				 }
			 }
		 }

		 /* display id and name percent of students with A or higher */
		 if(strcmp(cmd, "A") == 0) {
			 for(int k = 0 ; k < n ; k++) {
				 if(aID[k] != 0 && aLast[k] != 0) {
					 printf("%u  %s \n", aID[k], aLast[k]);
				 }
			 }
		 }
		 
		 		 /* display % of A students */
		 if(strcmp(cmd, "PerA") == 0) {
			 printf("Percentage of students with an average of A:%.2f%% \n", (100 * ((float) aCounter / (float) n)));
		 }
		 
		 
		 /* display if it is anomaly */ 
		 if(strcmp(cmd, "Anomaly") == 0) {
			 if(anomaly == 1) {
				printf("YES \n");
			 }
			 else {
				 printf("NO \n");
			 }
		 }
		 
		 /* thanks! */
		 if(strcmp(cmd, "q") == 0 || strcmp(cmd, "Q") == 0) {
			 printf("Thanks \n");
		 }
	 }		
	 return (1);
} 