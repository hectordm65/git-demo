#include <stdio.h>
#include <stdlib.h>

void getBitOp(char *bitOp); // get the bit operator
void setAndFixNum(char *fixing); // gets a particular number and makes sure it's valid
void calcOp(unsigned long first, unsigned long second, char *bitOp); // function for 2 binary numbers
void calcOpNot(unsigned long first); // function for 1 binary number, assuming ~
void dToB(unsigned long result); // decimal to binary algorithm

int main(int argc, char **argv){
	char *bitOperator = (char *)malloc(2*sizeof(char)); // I don't think this needs to be a char *, could just be char but I wanna have all void functions lol
	char *firstBinNum  = (char *)malloc(9*sizeof(char)); // first number we'll need
	

	getBitOp(bitOperator);

	while(firstBinNum == NULL ||
	       firstBinNum[0] == '\0'){
		printf("\nPlease enter an 8-bit binary number: ");
		setAndFixNum(firstBinNum);
	}
	unsigned long dNum = strtoul(firstBinNum, NULL, 2);
	printf("Your initial number in decimal is: %lu\n", dNum);
	
	if(*bitOperator != '~') { //if we're calculating a second number
		char *secondBinNum = (char *)malloc(9*sizeof(char)); // will only be created if we need it
		printf("\nPlease enter another 8-bit binary number (you did not select '~'): ");
		setAndFixNum(secondBinNum); //gets our number

		unsigned long dNumTwo = strtoul(secondBinNum, NULL, 2); 
		printf("Your second initial number in decimal is: %lu\n", dNumTwo);
		calcOp(dNum, dNumTwo, bitOperator);
		free(secondBinNum);
	}	
	else if(*bitOperator == '~') { //if we're only calculating the one number
		calcOpNot(dNum);	
	}
	free(bitOperator);
	free(firstBinNum);
	
	return 0;
}

void getBitOp(char *bitOp) {
	while(*bitOp != '|' &&
	       *bitOp != '&' &&
	       *bitOp != '^' && 
	       *bitOp != '~'){ //getting our operator
		printf("Please enter a bit level operator (|, &, ^, ~): ");
		int c;
		scanf("%1s", bitOp);
		while ((c = fgetc(stdin)) != '\n' && c != EOF); //Flush stdin, gets rid of the rest of the typed stuff
		printf("You chose: %s\n", bitOp);
	}
}

void fixNum(char *fixing) {
	int i;
	for(i = 0; i < 8; i++)
	{
		if(fixing[i] != '1' && fixing[i] != '0')
			fixing[i] = '1';
	}
	fixing[8] = '\0';
}

void setAndFixNum(char *setting){
	int c;
	scanf("%8s", setting);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); //Flush stdin, gets rid of the rest of the typed stuff
	fixNum(setting);
	printf("Your number(after input validation): %s\n", setting);
}

void calcOp(unsigned long first, unsigned long second, char *bitOp) {
	unsigned long result = 0;
	if(bitOp[0] == '|') {
		result = first | second;
	} else if(bitOp[0] == '&') {
		result = first & second;
	} else if(bitOp[0] == '^') {
		result = first ^ second;
	}
	printf("%lu %s %lu", first, bitOp, second);
	printf("\nYour final result in decimal is: %lu\n", result);
	dToB(result);
}

void calcOpNot(unsigned long first) {
	unsigned long notFirst = ~first;
	notFirst = notFirst & 0x000000FF; //mask
	printf("~%lu", first);
	printf("\nYour final result in decimal is: %lu\n", notFirst);
	dToB(notFirst);
}

void dToB(unsigned long result) {
	unsigned long binDig = 128;
	char *temp = (char *)malloc(9*sizeof(char));
	unsigned long remain = result;
	
	int i;
	for(i = 0; i < 8; i++) {
		//printf("checking: %lu %% %lu = %lu < %lu\n", remain, binDig, (remain%binDig), remain); // was used for debugging
		if((remain % binDig) < remain) { 
			remain = remain - binDig;
			temp[i] = '1';
		} else {
			temp[i] = '0';
		}
		binDig = binDig/2;
	}
	printf("Your final result in binary: %s\n", temp);
}
