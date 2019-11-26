#include <stdlib.h>

#include "bloom.h"

const int BLOOM_HASH1 = 17;
const int BLOOM_HASH2 = 29;

// compute a hash of a string using a seed value, where the result
// falls between zero and range-1
int hash_string(char * string, int seed, int range)
{
  int i;
  int hash = 0;

  // simple loop for mixing the input string
  for ( i = 0; string[i] != '\0'; i++ ) {
    hash = hash * seed + string[i];
  }
  // check for unlikely case that hash is negative
  if ( hash < 0 ) {
    hash = -hash;
  }
  // bring the hash within the range 0..range-1
  hash = hash % range;
  
  return hash;
}



// create a new, empty Bloom filter with 'size' slots
struct bloom * bloom_new(int size)
{
  //
  struct bloom * returnBloom = malloc(sizeof(struct bloom));

  returnBloom->bit_vector = bitset_new(size);
  returnBloom->size = size;

  return returnBloom;
}

// check to see if a string is in the set
int bloom_lookup(struct bloom * this, char * item)
{

  //hash the item
  int hashResult1 = hash_string(item, BLOOM_HASH1, this->size);

  //check if the first hash returns true
  if (bitset_lookup(this->bit_vector, hashResult1)){

    //check the second hash
    int hashResult2 = hash_string(item, BLOOM_HASH2, this->size);
    if (bitset_lookup(this->bit_vector, hashResult2)){
      
      //both hash functions have returned true, so return true
      return 1;
    } else {
      //hash 2 failed
      return 0;
    }
  } else {  
    //hash 1 failed
    return 0;
  }

  //incase of other failure
  return 0;
}



// add a string to the set has no effect if the item is already in the
// set; note that you cannot safely remove items from a Bloom filter
void bloom_add(struct bloom * this, char * item)
{
  //first hash of the string
  int hashValue1 = hash_string(item, BLOOM_HASH1, this->size);

  //second hash of the string
  int hashValue2 = hash_string(item, BLOOM_HASH2, this->size);

  //insert both hash results into the bitvector set
  bitset_add(this->bit_vector, hashValue1);
  bitset_add(this->bit_vector, hashValue2);

}

// place the union of src1 and src2 into dest
void bloom_union(struct bloom * dest, struct bloom * src1,
		  struct bloom * src2)
{

  //extract the bitsets
  //get the union for each of the blooms
  if ((src1->bit_vector->size_in_words == src2->bit_vector->size_in_words) && (dest->bit_vector->size_in_words == src1->bit_vector->size_in_words)){
    
    int counter;
    for (counter = 0; counter < src1->bit_vector->size_in_words; counter++){
      dest->bit_vector->data[counter] = src1->bit_vector->data[counter] | src2->bit_vector->data[counter];
    }
  }
}

// place the intersection of src1 and src2 into dest
void bloom_intersect(struct bloom * dest, struct bloom * src1,
                  struct bloom * src2)
{
  //extract the bitsets
  //get the union for each of the blooms
  if ((src1->bit_vector->size_in_words == src2->bit_vector->size_in_words) && (dest->bit_vector->size_in_words == src1->bit_vector->size_in_words)){
    
    int counter;
    for (counter = 0; counter < src1->bit_vector->size_in_words; counter++){
      dest->bit_vector->data[counter] = src1->bit_vector->data[counter] & src2->bit_vector->data[counter];
    }
  }
}

// print out the bits that are 1 in the bit vector of
// a bloom filter
void bloom_print(struct bloom * this)
{
  bitset_print(this->bit_vector);
}
