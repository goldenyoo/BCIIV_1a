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
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
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

	//assert(pcEnd);
	pcAsg = pcDest;
	pcCpy = pcSrc;
	
	if(!(*pcCpy)){
		*pcAsg = '\0';
		return pcDest;
	}
	while(*pcCpy){
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
	
	pcOne = pcS1;
	pcSec = pcS2;

	while(*pcOne && *pcSec){
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
	//assert(*pcNeedle);

	enum DFAState {FIND, NON};
	enum DFAState state;

	state = NON;

	const char* pcOrig;
	//const char* pcTarget;
	const char* pcFind;
	const char* pcTmp;

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
	char c_add[MAX_SIZE];
	char *c_first;
	const char *c_second;
	char *c_output;

	c_first = pcDest;
	c_second = pcSrc;

	c_output = StrCopy(c_add,c_first);

	while(*c_output){
		c_output++;
	}

	while(*c_second){
		*c_output = *c_second;
		c_output++;
		c_second++;
	}
	*c_output = '\0';

	pcDest = c_add;

  
  return pcDest;	
}
