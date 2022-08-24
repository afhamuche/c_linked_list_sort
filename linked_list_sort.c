#include <stdio.h>
#include <stdlib.h>

struct digit {
	int num;
	struct digit * next;
};

int thankYou();
struct digit * createDigit(int dig);
struct digit * append(struct digit * end, struct digit * newDigitPtr);
void printDigits(struct digit *);
void freeDigits(struct digit * start);
struct digit * readDigits();
struct digit * searchDigit(struct digit * start, int num);
struct digit * reverseDigits(struct digit * start);
struct digit * insertFront(struct digit * start, struct digit * newPtr);
struct digit * sortedCopy(struct digit * start);
struct digit * insertSorted(struct digit * start, struct digit * newDigit);

int main(void) {

	struct digit *start, *ptr, *backwards, *sorted;
	start = readDigits();
	printDigits(start);

	backwards = reverseDigits(start);
	printDigits(backwards);

	sorted = sortedCopy(start);
	printDigits(sorted);

	freeDigits(start);
	freeDigits(backwards);
	freeDigits(sorted);

	return thankYou();
}

int thankYou() {
	printf("\nThank you for using ThankYou-Bot!\n\n");
	return 0;
}

struct digit * createDigit(int dig) {
	struct digit * ptr;
	ptr = (struct digit *) malloc(sizeof(struct digit));
	ptr->num = dig;
	ptr->next = NULL;
	return ptr;
}

struct digit * append(struct digit * end, struct digit * newDigitPtr) {
	end->next = newDigitPtr;
	end = newDigitPtr;
	return end;
}

void printDigits(struct digit * start) {
	struct digit * ptr = start;
	int index = 1;
	printf("\nPrinting Linked digit Structure\n");
	while (ptr!=NULL) {
		printf("%3d. struct digit{%d};\n", index, ptr->num);
		ptr = ptr->next;
		index++;
	}
}

void freeDigits(struct digit * start) {
	struct digit * ptr = start;
	struct digit * tmp;
	while (ptr!=NULL) {
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
}

struct digit * readDigits(){
	char cDig;
	int dig;
	int asciiDig = 48;
	struct digit * start, * end, * newPtr;
	start = NULL;

	printf("Please enter an integer.\n> ");
	scanf("%c", &cDig);
	while (cDig!='\n') {
		dig = cDig - asciiDig;
		newPtr = createDigit(dig);
		if (start == NULL) {
			start = newPtr;
			end = start;
		} else {
			end = append(end, newPtr);
		}
		scanf("%c", &cDig);
	}
	return start;
}

struct digit * searchDigit(struct digit * start, int num) {
	struct digit * ptr = start;
	while (ptr!=NULL && ptr->num!=num) {
		ptr = ptr->next;
	}
	return ptr;
}

struct digit * reverseDigits(struct digit * start) {
	struct digit * ptr = start;
	struct digit * bStart = NULL;
	struct digit * newDigit;

	if (start!=NULL) {
		bStart = createDigit(start->num);
		ptr = ptr->next;
	}

	while (ptr!=NULL) {
		newDigit = createDigit(ptr->num);
		bStart = insertFront(bStart, newDigit);
		ptr = ptr->next;
	}

	return bStart;
}

struct digit * insertFront(struct digit * start, struct digit * newPtr) {
	newPtr->next = start;
	return newPtr;
}

struct digit * sortedCopy(struct digit * start) {
	struct digit * ptr = start;
	struct digit * sortedStart = NULL;
	struct digit * newDigit;

	printf("\nSorting linked list...\n");

	if (start!=NULL) {
		sortedStart = createDigit(start->num);
		ptr = ptr->next;
	}
	
	while (ptr!=NULL) {
		newDigit = createDigit(ptr->num);
		sortedStart = insertSorted(sortedStart, newDigit);
		ptr = ptr->next;
	}

	return sortedStart;
}

struct digit * insertSorted(struct digit * start, struct digit * newDigit) {
	struct digit * ptr = start;
	struct digit * previous = NULL;

	while (ptr!=NULL && ptr->num < newDigit->num) {
		previous = ptr;
		ptr = ptr->next;
	}

	if (previous == NULL) {
		start = insertFront(start, newDigit);
	} else {
		previous->next = newDigit;
		newDigit->next = ptr;
	}

	return start;
}
