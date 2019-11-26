#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "bitset.h"


//create a new bitset
struct bitset * bitset_new(int size){
  

  //generate the parameters required to create a new bitset
  int bitsPerWord = (sizeof(unsigned int) * 8);
  int arrSizeInWords = size / bitsPerWord;
  
  unsigned int* bitsetArray = (unsigned int*) malloc((sizeof(unsigned int) * arrSizeInWords));
  //clear each bitset by setting to 0
  int i;
  for (i = 0; i < arrSizeInWords; i++){
    bitsetArray[i] = 0;
  }
  
  //create a new bitset structure to return
  struct bitset * bitsetToReturn = malloc(sizeof(struct bitset));
  bitsetToReturn->data = bitsetArray;


  bitsetToReturn->size_in_bits = size;
  bitsetToReturn->size_in_words = arrSizeInWords;
  bitsetToReturn->bits_in_word = bitsPerWord; 

  //return a pointer to the datastructure
  return bitsetToReturn;
}

//return the size of a bitset
int bitset_size(struct bitset * this){
  return (this->size_in_words*32);
}


// get the number of bits set to one  within the set
int bitset_cardinality(struct bitset * this){

  int total = 0;
  //for each item witin the set, check if it has a number
  int i;
  for (i = 0; (i<this->size_in_words); i++){
    
    unsigned temp;
    int j;
    for (j = 0; (j<this->bits_in_word); j++){
      
      //get the current word from the bitset
      temp = this->data[i];
      unsigned mask = 1;
      temp = temp>>j;

      //if the bit at this point is 1, increment the total by 1
      if ((temp & mask) == 1){
        total++;
      }
    }
  }

  return total;
}

//add an item to the bitset
//has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item){
  //get the mask position and what bit it is stored in
  int wordPosition = item / this->bits_in_word;
  int itemPosition = item - (wordPosition*this->bits_in_word); 

  //set the bits
  //push the mask from the end to the item to be changed
  unsigned mask = 0;
  unsigned shiftNum = itemPosition;
  mask = 1<<shiftNum;

  //set bits
  this->data[wordPosition] = (this->data[wordPosition] | mask);
}


// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item){

  //get the mask position and what bit it is stored in
  int wordPosition = item / this->size_in_bits;
  int itemPosition = item % (this->size_in_bits * wordPosition); 
  
  //invert the mask to clear the bit
  unsigned mask;
  mask = ~(1<<itemPosition);
  //clear bits
  this->data[wordPosition] = (this->data[wordPosition] & mask);

}

// place the union of src1 and src2 into dest
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2){
  //return the union of the two sets

  //get the union for each of the words in the set
  if ((src1->size_in_words == src2->size_in_words) && (dest->size_in_words == src1->size_in_words)){
    
    int counter;
    for (counter = 0; counter < src1->size_in_words; counter++){
      dest->data[counter] = src1->data[counter] | src2->data[counter];
    }
  }

}
  


void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2){
  
  //return the intersect of the sets
  if ((src1->size_in_words == src2->size_in_words) && (dest->size_in_words == src1->size_in_words)){
    
    int counter;
    for (counter = 0; counter < src1->size_in_words; counter++){
      dest->data[counter] = src1->data[counter] & src2->data[counter];
    }
  }
}


// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){

  //for a word long bitset
  //shift the bit to find to the right and return the anded result
  unsigned int* temp = (unsigned int*) malloc(sizeof(unsigned int) * this->size_in_words);

  //duplicate into a temp
  int x; 
  for (x = 0; x < this->size_in_words; x++){
    temp[x] = this->data[x];
  }


  //get which word the bit is in
  unsigned int wordNumber = item / 32;
  //shift that word by this much
  unsigned int position = item % 32;
  //temp->bits is an array
  unsigned int one = 1;

  unsigned returnNo = (((temp[wordNumber]) >> position) & one);
  //free the temporary peice of memory
  free(temp);
  
  return returnNo;

}

// print the contents of the bitset
void bitset_print(struct bitset * this)
{
  int i;
  int size = bitset_size(this);
  for ( i = 0; i < size; i++ ) {
    if ( bitset_lookup(this, i) == 1 ) {
      printf("%d ", i);
    }
  }
  printf("\n");
}







/*
// add the characters from a string to a bitset
void add_chars_to_set(struct bitset * this, char * s)
{
  int i;
  for ( i = 0; s[i] != 0; i++ ) {
    unsigned char temp = s[i];
    bitset_add(this, temp);
  }

}


int main(){
  struct bitset * a = bitset_new(256);
  struct bitset * b = bitset_new(256);
  struct bitset * c = bitset_new(256);
  char * string1 = "What can you hear";
  char * string2 = "Nothing but the rain";

  bitset_print(a);


  add_chars_to_set(a, string1);
  add_chars_to_set(b, string2);


  printf("The contents of set a are:\n");
  // print the contents of the sets
  bitset_print(a);
  printf("\nThe contents of set b are:\n");
  bitset_print(b);

  // compute and print the union of sets
  bitset_union(c, a, b);
  printf("\nThe union of the sets are:\n");
  bitset_print(c);

  // compute and print the intersection of sets
  bitset_intersect(c, a, b);
  printf("\nThe intersection of the sets is:\n");
  bitset_print(c);

  return 0;
}
*/
