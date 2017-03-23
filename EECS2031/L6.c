#include <stdio.h>
#include <stdlib.h>

/* read a string character by character and use each char as an unsigned 8 bit number (0-255). Add each characters modulo the table size. Result should be an integer between 0 and k-1. */
int hash(unsigned char *curr, int k) {
	int hash = 0;
	int c;
	while(c = *curr) {
		hash = hash + c;
		curr++;
	}
		return hash % k;
	}

int main() {
	
	typedef struct Record {
		char Name[50];
		int midMark;
		int finMark;
		struct Record *ptr;
	} Records;
	
	Records *r2, *prev, *head = NULL;
	char s[10], s1[50];
	int i, hashNum = 0, k, steps = 0, dne = 1; //dne, does not exist, if 0 then exists if 1 then dne
	FILE * fp;
	int hashArr[k];
	memset(hashArr, 0, max_size);
	
	if(!(fp = fopen("records.txt","r"))) {
		perror("Could not open file");
		return(-1);
	}
	
	fgets(s, sizeof(s), stdin);
	sscanf(s, ”%d”, &k);
	
	Records *recArr[k];
	rnext = malloc(sizeof(Records));
	
	//add to array of linked lists
	while(fgets(rnext->Name, 51,fp) != NULL) {
		fgets(rnext->Name, 51,fp);
		scanf("%i", &rnext->midMark);
		scanf("%i", &rnext->finMark);
		rnext->ptr = NULL;
		hashNum = hash(rnext->Name, k);
		if(!head) {
			head = rnext;
		}
		else {
			recArr[hashNum] = head;
			while(recArr[hashNum]->ptr != NULL) {
				recArr[hashNum] = recArr[hashNum]->ptr;
			}
			recArr[hashNum]->ptr = rnext;
		}
		hashNum = 0;
	}
	
	//find the name of file
	
	while(fgets(s1, 51, stdin) != NULL){
		i=0;
		while(s1[i] != '\n') {
			i++;
		}
		s1[i]='\0'; i =0; // set last char to null of name that was input
		
		for(i = 0; i < k; i++) {
			while(recArr[i] != NULL) {
				steps++;
				if(strcmp(recArr[i]->Name, s1) == 0) {
					printf("%d %d %d\n", recArr[i]->midMark, recArr[i]->finMark, steps);
					dne = 0;
				}
				recArr[i]-> ptr;
			}
		}
		
		if(dne == 0) {
			printf("The name does not exist in the file");
		}
	}
}
			
		
		
		
		
	
		
			
			
		
		
		
	
		