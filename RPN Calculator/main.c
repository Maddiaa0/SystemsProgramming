#include <stdio.h>
#include <stdlib.h>



#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <ctype.h>

int main()
{
    printf("Hello world!\n");
    return 0;
}

//define the linked list
struct listnode{
	int data;
	struct listnode * next;
}

typedef struct {
	struct listnode * head;
} List;

//add to the list
int initialiseList(List * listToInit){
	listToInit->head = NULL;
	head = malloc(sizeof(listToInit));
}

int pushToListEnd(List * listToAdd, int val){
	listNode * current = listToAdd->head;
	while (current->next != NULL){
		current = current->next;
	}

	current->next = malloc(sizeof(listnode));
	current->next->val = val;
	current->next->next = NULL;
}


//point to a pointer of the head
//then add to the change the head pointer to point to the
//new node, with the previous head pointer pointing to
//the new value
int pushToListStart(List ** head, int val){
	listNode * newNode;
	newNode = malloc(sizeof(listNode));

	newNode->val = val;
	newNode->next = *head;
	*head = newNode;
}

int poppingFirstItem(listnode **head){
	//set the return value to -1 for error
	int retVal = -1;
	listnode * nextNode = NULL;

	//check for an empty list
	if (*head == NULL){
		return -1;
	}

	//get the item the head is currently pointing to
	nextNode = (*head)->next;
	//return the item the head is pointing to
	retVal = (*head)->val;
	//return what head is pointing to to the heap
	free(*head);
	//set the original item after the head to be the head
	*head = nextNode;

	return retVal;
}


int readFile(char[] fileAddress){

}


//this function hopes to return a string of the text in the file
char *readFile(char *fileName){

	int size = 0;
	char *returnedText;

	//use the open file method to get the file
	FILE *file = open_file(filename);

	//get the size of the file
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	returnedText = malloc(fileSize);

	//add the file to a String
	while ((returnChar = fgetc(file)) != EOF){
		returnedText[size++] = (char)returnChar;
	}

	returnChar[size] = '/0';

	return returnedText;
}

/* Open a file. Abort program if file cannot be opened */
FILE * open_file(char filename[])
{
  FILE * file;

  //check if the file can be opened
  //using f-open library
  file = fopen(filename, "r");
  if ( file == NULL ) {
    printf("FATAL: Error opening file %s. Aborting program.\n", filename);
    exit(1);
  }

  return file;
}



int evaluateInputString(char * inputString){

}

int evaluateChar(char *input){
	//get the length of the string being processed
	int stringLength = strlen(input);
	//iterate through string
	int i;
	for (i = 0; i< stringLength; i++){

		//if (token is a number)
		if (isdigit(input[i])){
			//go until a space or another character is reached
			int originalPoint = i;
			int endPoint = i;
			while (isdigit(input[i]){
				endPoint++;
			}
			char stringToStore =
 		} else if (isalpha(input[i])){

 		}
 		//then read through the array to find a space
	}


	if (input >= '0' && input <= '9'){
		return 1; //1 represents a number
	} else if (input == ' '){
		return 2; //2 represents a space
	} else if (input == '*' || input == '/' || input == '+' || input == '-' || input == '^'){
		return 3; // 3 represents a mathematical character
	} else {
		return -1; //return 1 if the character is not recognised
	}
}


//small subroutines to perform the calculator actions
int performMultiplication(int a, int b){
	return (a + b);
}

int performSubtraction(int a, int b){
	return (a-b);
}

int performPower(int a, int b){
	return pow(a,b);
}

int performDivision(int a, int b){
	return (a/b);
}








/*
DAVID GREGG CODE

read a stream of up to 'size' integers from a text file.
   return number of integers
int read_in(int a[], int size, char filename[])
{
  const int max_line = 1024;
  char line[max_line];
  int i;
  FILE * file;
  char * eof;

  file = open_file(filename);

  /* read in the ints - one per line
  i = 0;
  eof = fgets(line, max_line, file);
  while ( eof != NULL && i < size ) {     /* eof == NULL => end of file
    sscanf(line, "%d", &(a[i]));
    i++;
    eof = fgets(line, max_line, file);
  }
  fclose(file);
  return i;
}
*/

















/* write out an array of integers up to 'size' */
void write_out(int a[], int size)
{
  int i;

  for ( i = 0; i < size; i++ ) {
    printf("%d\n", a[i]);
  }
}


/* read in a file of numbers, sort them, and
   write them out to the screen
int main()
{
  const int size = 1024;
  int nums[size];
  int nnums;

  nnums = read_in(nums, size, "numbers.txt");
  funnySort(nums, nnums);
  write_out(nums, nnums);
  /* flush output buffer, so all output appears on screen
  fflush(stdout);

  return 0;
}*/

