#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"

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
	int i;
	char *pcStart;
	const char *pcEnd;
	assert(pcEnd);
	pcStart = pcDest;

	for(i = 0; i < StrGetLength(pcSrc); i++){
		*pcStart = *pcSrc;
		pcStart++;
		pcSrc++;
	}
  
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
			*pcOne++;
			*pcSec++;
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
 
  return strstr(pcHaystack, pcNeedle);
}
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
  
  return strcat(pcDest, pcSrc);
}
