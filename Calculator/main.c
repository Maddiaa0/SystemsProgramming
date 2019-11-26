//program in sublime and then compile in here!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>


struct Stack{
    struct node *head;
};

//globally declare the head of the stack
struct node{
    float data;
    struct node* next;
} *head = NULL;

struct charNode{
    char data;
    struct charNode* next;
} *charHead = NULL;

//declare methods
int evaluateFile(char *fileText);
float evaluatePostFix(char *fileText);
float performAddition(float a, float b);
float performSubtraction(float a, float b);
float performDivision(float a, float b);
float performMultiplication(float a, float b);
float performIndice(float a, float powerOf);
float performArith(int operand, float a, float b);
void stackPush(float val);
float stackPop();
void displayStack(struct node* head);
char *getFileText(char *fileName[]);
char *convertFromInfixToPostFix(char *fileText);
int hasHigherPrecedence(char item, char compare);
char charStackPop();
void charStackPush(char val);
FILE *openFile(char fileName[]);



int main(int argc, char ** argv){

    /*
    char * filename;
    if (argc == 1){
        printf("Error: No input filename provided\n");
        printf("Usage: %s <input filename>\n", argv[0]);
        exit(1);
    }
    else if (argc > 2){
        printf("Error: Too many command line parameters\n");
        printf("Usage: %s <input filename\n", argv[0]);
        exit(1);
    }
    else{
        filename = argv[1];
    }
    */

    char fileName[] = "testFile.in.txt";
    FILE *numFile = openFile(fileName);
    //return string from file, else return null

    //return the results to the file
    char *returnStr = malloc(sizeof(char)* 100);
    FILE *returnFile = fopen("testFile.ans.txt", "w");
    //go through each line and evaluate
    if (numFile != NULL){
        while(!feof(numFile)){

            fgets(returnStr, 100, numFile);

            fprintf(returnFile, "%s\n", returnStr);
            if (returnStr[0] == 'i'){
                //deal with an infix equation
                fprintf(returnFile, "%f\n", evaluatePostFix(convertFromInfixToPostFix(returnStr)));
            } else if (returnStr[0] == 'p'){
                //deal with a postfix equation
                fprintf(returnFile, "%f\n", evaluatePostFix(returnStr));
            }

        }
    }


    //char *testData = getFileText("testFile.txt");

    //printf("%s", testData);
    //char *test = convertFromInfixToPostFix(testData);
    //printf("%f", evaluatePostFix(test));
    return 0;
}

//check the file has readable contents
//STILL NEED TO TEST THIS
FILE *openFile(char fileName[]){
    FILE * file;

    //check if the file can be opened
    file = fopen(fileName, "r");
    if (file == NULL){
        printf("ERROR: the opening of %s has been fatal\n", fileName);
        exit(1);
    }
    return file;
}



//return 0 for nothing
//return 1 for postfix
//return 2 for infix
int getExpressionType(char *fileText){
    char *token;

    token = strtok(fileText, " ");
    if (token[0] == 'p'){
        //line begins with p so it is postfix
        return 1;
    } else if (token[0] == 'i') {
        //line begins with i so it is infix
        return 2;
    } else {
        //undefined input
        return 0;
    }
}


float evaluatePostFix(char *fileText){

    char *token;

    token = strtok(fileText, " ");
    //loop through the contents of the file
    while (token != NULL){
        //get the character to check
        char toCheck = token[0];

        if (isdigit(toCheck)){
            //deal with adding the stack into the equation
            //cast the number on the stack to an integer
            char *scannedNumber = malloc(sizeof(token));
            strcpy(scannedNumber,token);


            //printf("%s\n", scannedNumber);
            //get this working for more than one character numbers
            float itemToPush = atof(scannedNumber);

            free(scannedNumber);
            stackPush(itemToPush);
            //also remember to check for a space
        } else if ((toCheck == '+')||(toCheck == '-')||(toCheck =='*')||(toCheck =='/')||(toCheck=='^')||(toCheck =='X')){
            //pop the last two items from the stack
            //work this bit out
            float b = stackPop(head);
            float a = stackPop(head);
            float arithResult = 0;
            char operand = toCheck;

            //perform Arithmetic operation
            arithResult = performArith(operand, a,b);

            //push the RESULT!!!!!!!!!
            stackPush(arithResult);
        }

        //increment the counter
        token = strtok(NULL," ");
    }
    return head->data;
}


//append to strings
void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

float performArith(int operand, float a, float b){
    float result = -1;
    //switch through the possible operators and return the result
    switch (operand){
    case '+':
        result = performAddition(a,b);
        break;
    case '-':
        result = performSubtraction(a,b);
        break;
    case '/':
        result = performDivision(a,b);
        break;
    case '*':
        result = performMultiplication(a,b);
        break;
    case 'X':
        result = performMultiplication(a,b);
        break;
    case '^':
        result = performIndice(a,b);
        break;
    }
    return result;
}


char * convertFromInfixToPostFix(char *fileText){

    char *outputText = malloc(sizeof(char) * 100);
    //initialise a counter and loop through the array
    char *spacer = " ";
    char *token;
    token = strtok(fileText, " ");
    outputText[0] = '\0';

    while (token != NULL){
        //check the first character of each input token, see if number of not
        char toCheck = token[0];
        //if token is a number, append it to the output string
        if (!isalpha(toCheck)){
            if (isdigit(toCheck)){

                strcat(outputText, token);
                strcat(outputText, spacer);
            }

            //if the token is an operator
            else if ((toCheck == '+')||(toCheck == '-')||(toCheck =='*')||(toCheck =='/')||(toCheck=='^')){
                //while there is an operator on top of stack with higher precedence
                //work out how to solve precedence
                int loopFlag = 0;
                while (loopFlag == 0){

                    if (charHead != NULL){

                        if (hasHigherPrecedence(toCheck, charHead->data) == 1){

                            char item[2];
                            item[0] = charStackPop();
                            item[1] = '\0';

                            strcat(outputText, item);
                            strcat(outputText, spacer);

                        }else{
                            loopFlag = 1;
                        }
                    } else{
                        loopFlag = 1;
                    }
                }
                charStackPush(toCheck);
            }
            //if token is a left bracket, push it to the stack
            else if (toCheck == '('){
                charStackPush(toCheck);
            }
            //if the token is a right bracket
            else if (toCheck == ')'){

                //while top of stack != '('
                //pop operator from stack and append to output string
                if (charHead != NULL){
                    char currentValOnHead = charHead->data;

                    //CODE GETS STUCK IN THIS LOOP
                    while (currentValOnHead != '(' ){ //&& currentValOnHead != NULL){

                        char item[2];
                        item[0] = charStackPop();
                        item[1] = '\0';

                        strcat(outputText, item);
                        strcat(outputText, spacer);
                        currentValOnHead = charHead->data;
                    }
                    //pop the left bracket
                    if (currentValOnHead == '('){
                        charStackPop();
                    }

                }
            }
            }
        //get the next token
        token = strtok(NULL," ");
    }
    //finally push all operators on the stack to the string

    //checker == '+' || checker == '-' || checker == '*' || checker == '/' || checker == '^' || checker == 'X'
    while (charHead!= NULL){
        char item[2];
        item[0] = charStackPop();
        item[1] = '\0';

        strcat(outputText, item);
        strcat(outputText, spacer);

    }
    return outputText;
}

//determine if the passed in operators have higher precedence over each other
int hasHigherPrecedence(char item, char compare){
    if (item == '-' && (compare == '+' || compare == '*' || compare== '/' || compare == '^' || compare =='X')){
        return 1;
    }
    else if (item == '+' && (compare == '*' || compare == '/' || compare =='^' || compare == 'X')){
        return 1;
    }
    else if (item == '/' && (compare == '*' || compare == 'X'|| compare == '^')){
        return 1;
    }
    else if (item == '*' && (compare == '^')){
        return 1;
    }
    else {
        return 0;
    }

}









//simple calculator sub-rountines
float performAddition(float a, float b){
    return a+b;
}

float performSubtraction(float a, float b){
    return a-b;
}

float performMultiplication(float a, float b){
    return a*b;
}

float performDivision(float a, float b){
    //catch divide by 0 error
    if (b == 0){
        return 0;
    } else{
        return a/b;
    }
}

float performIndice(float a, float powerOf){
    //check for the power of 0 case
    if (powerOf == 0){
        return 1;
    } else {
        return pow(a, powerOf);
    }
}







//stack information
void stackPush(float val)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));

    newNode->data = val;
    newNode->next = head;
    head = newNode;
}

float stackPop()
{
    float value;
    if (head == NULL)
    {
        value = 0;
    }
    else
    {
        struct node *temp;
        value = head->data;
        temp = head;
        head = temp->next;
        free(temp);
    }
    return value;
}

void charStackPush(char val)
{
    struct charNode *newNode = (struct charNode*)malloc(sizeof(struct charNode));
    newNode->data = val;
    newNode->next = charHead;
    charHead = newNode;
}

char charStackPop()
{
    char value;
    if (charHead == NULL)
    {
        value = 0;
    }
    else
    {
        struct charNode *temp;
        value = charHead->data;
        temp = charHead;
        charHead = temp->next;
        free(temp);
    }
    return value;
}



