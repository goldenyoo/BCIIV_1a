#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"
#define MAX_SIZE 100

/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
<<<<<<< HEAD
  assert(pcSrc != NULL); /* NULL address, 0, and FALSE are identical. */
=======
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
	char *pcAsg;
	const char *pcCpy;

<<<<<<< HEAD
	assert(pcDest != NULL && pcSrc != NULL);
=======
	//assert(pcEnd);
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d
	pcAsg = pcDest;
	pcCpy = pcSrc;
	
	if(*pcCpy == '\0'){
		*pcAsg = '\0';
		return pcDest;
	}
	while(*pcCpy != '\0'){
		*pcAsg = *pcCpy;
		pcAsg++;
		pcCpy++;
	}
  	*pcAsg = '\0';
  return pcDest;
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  /* TODO: fill this function */
	const char* pcOne;
	const char* pcSec;
	
<<<<<<< HEAD
	assert(pcS1 !=NULL && pcS2 != NULL);
=======
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d
	pcOne = pcS1;
	pcSec = pcS2;

	while(*pcOne!='\0' && *pcSec!='\0'){
		if(*pcOne == *pcSec ){
			pcOne++;
			pcSec++;
		}
		else{
			return *pcOne - *pcSec;
		}
	}
 
  return *pcOne - *pcSec;
}

/*------------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  /* TODO: fill this function */
<<<<<<< HEAD
=======
	//assert(*pcNeedle);
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d

	enum DFAState {FIND, NON};
	enum DFAState state;

	state = NON;

	const char* pcOrig;
	//const char* pcTarget;
	const char* pcFind;
	const char* pcTmp;

<<<<<<< HEAD
	assert(pcHaystack != NULL && pcNeedle != NULL);

=======
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d
	pcOrig = pcHaystack;
	//pcTarget = pcNeedle;
	pcTmp = pcNeedle;
	pcFind = NULL;
	if(!(*pcNeedle)){
		return (char*)	pcHaystack;
	}
	while(*pcOrig){
		switch(state){
			case NON:
				if(*pcOrig == *pcNeedle){
					pcFind = pcOrig;
					pcOrig++;
					pcTmp++;
					state = FIND;
				}
				else{
					pcOrig++;
					state = NON;
				}
				break;

			case FIND:
				
				if(*pcOrig == *pcTmp){
					pcOrig++;
					pcTmp++;
					state = FIND;
					if(*pcTmp == '\0'){
						return (char*)pcFind;
					}
				}
				else{
					pcTmp = pcNeedle;
					state = NON;
				}
				break;

			default:
				assert(0);
				break;
		}
	}
	return (char*) NULL; 
}
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
	//char c_add[MAX_SIZE];
	char *c_first;
	const char *c_second;
	char *c_output;

<<<<<<< HEAD
	assert(pcDest != NULL && pcSrc != NULL);

=======
>>>>>>> 1ea29c21fbfda512e0c91928c8789ac33ec4183d
	c_first = pcDest;
	c_second = pcSrc;

	c_output = c_first;
	//c_output = StrCopy(c_add,c_first);

	while(*c_output != '\0'){
		c_output++;
	}

	while(*c_second != '\0'){
		*c_output = *c_second;
		c_output++;
		c_second++;
	}
	*c_output = '\0';

  return pcDest;	
}
