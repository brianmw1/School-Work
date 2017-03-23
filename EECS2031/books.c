#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_title 60
#define max_author 50
#define max_pub 50
#define max_recs 40

struct record {
	char title[max_title];
	char author[max_author];
	char publisher[max_pub];
	float price;
};

int main() {
	struct record book[max_recs];
	FILE * fp;
	int fileSize = 0;
	char newTitle[max_title];
	char newAuthor[max_author];
	char newPublisher[max_pub];
	float newPrice;
	char inqAns;
	char inqTitle[max_title];
	char inqAuthor[max_author];
	int dne = 1; // "does not exist" pseudo boolean if 1 book does not exist, if 0 book does exist
	int i = 0;
	int j = 0;
	int k = 0;
	
	//initialize first character of each title member to null character 
	//to prepare for counting amount of records (line 49)
	for(j = 0; j < max_recs; j++) { 
		book[j].title[0] = '\0';
	}
	
	if(!(fp = fopen("book.dat", "rb"))) {
		fp = fopen("book.dat", "wb");
	}
	
	while(k < max_recs && fread(&book[k], sizeof(book), 1, fp)) {
		k++;
		if(feof(fp)) {
			break;
		}
	}
	
	//count amount of records inside book.dat
	while(fileSize < max_recs && book[i].title[0] != '\0') {
		i++;
		fileSize++;
	}
	
	
	if(fileSize == max_recs){
		printf("The file is full\n");
	}
	printf("book.dat contains %i records\n", fileSize);
	while(fileSize < max_recs) {
		printf("Enter the name of the book\nTo stop entering, press enter at the beginning of a line\n");
		fgets(newTitle, max_title, stdin); //use fgets since scanf will skip new line character
		if(newTitle[0] == '\n') {
			break; // go to inquiry
		}
		else{
			++fileSize;
			int len = strlen(newTitle);
			if(newTitle[len - 1] == '\n') {
				newTitle[len - 1] = '\0';
			}
			strcpy(book[fileSize-1].title, newTitle);
			printf("Enter the author\n");
			scanf("%s", newAuthor);
			strcpy(book[fileSize-1].author, newAuthor);
			printf("Enter the publisher\n");
			scanf("%s", newPublisher);
			strcpy(book[fileSize-1].publisher, newPublisher);
			printf("Enter the price\n");
			scanf("%f", &newPrice);
			book[fileSize-1].price = newPrice;
			getchar();
		}
	}
	
	//inquire state
	while(1) {
		printf("Enter Q, T, or A followed by newline (enter).\n");
		scanf(" %c", &inqAns);
		getchar();
		if(inqAns == 'T') {
			printf("Enter the book title\n");
			fgets(inqTitle, max_title, stdin);
			int lenT = strlen(inqTitle);
			if(inqTitle[lenT - 1] == '\n') {
				inqTitle[lenT - 1] = '\0';
			}
			for(i = 0; i < fileSize; i++) {
				if(strcmp(book[i].title,inqTitle) == 0) {
						printf("Title: %s\n", book[i].title);
						printf("Author: %s\n", book[i].author);
						printf("Price: %.2f\n", book[i].price);
						dne = 0;
						break;
				}
				else {
					dne = 1;
				}
			}
			if(dne == 1){
				printf("No such book\n");
			}
		}
		if(inqAns == 'A') {
			printf("Enter the book author\n");
			fgets(inqAuthor, max_author, stdin);
			int lenA = strlen(inqAuthor);
			if(inqAuthor[lenA - 1] == '\n') {
				inqAuthor[lenA - 1] = '\0';
			}
			for(i = 0; i < fileSize; i++) {
				if(strcmp(book[i].author,inqAuthor) == 0) {
						printf("Title: %s\n", book[i].title);
						printf("Author: %s\n", book[i].author);
						printf("Price: %.2f\n", book[i].price);
						dne = 0;
						break;
				}
				else {
					dne = 1;
				}
			}
			if(dne == 1){
				printf("No such book\n");
			}
		}
		if(inqAns == 'Q') {
			exit(0);
		}
	}
	fclose(fp);
	return 0;
}