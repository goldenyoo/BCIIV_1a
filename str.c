/*************************************************************/
 //   File_name: str.c
 //   Programmer: Seungjae Yoo                             
 //   Student ID: 20160767                                         
 //   Assignment #2                                          
 //   Last Modified: 2018_04_02                              
 //                                       
 //                    
 //	 This code is wrote on Sublime Text
/*************************************************************/




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
/*------------------------------------------------------------------*/
/*StrGetLength(): 
  from the parameter pcSrc, calculate the string length until 
  null chracter and return it                                    */
/*------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;

  assert(pcSrc != NULL); /* NULL address, 0, and FALSE are identical.*/
  
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------*/
/*StrCopy(): 
  Using parameter pcDest and pcSrc, function copys pcSrc to pcDest.*/
/*------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
	char *pcAsg;
	const char *pcCpy;

	assert(pcDest != NULL && pcSrc != NULL); /*Asserting parameteres are not NULL*/
	pcAsg = pcDest;
	pcCpy = pcSrc;
	
	if(*pcCpy == '\0'){/*copying just empty string results empty string*/
		*pcAsg = '\0';
		return pcDest;
	}
	while(*pcCpy != '\0'){/*Copying string until '\0' chracter*/
		*pcAsg = *pcCpy;
		pcAsg++;
		pcCpy++;
	}
  	*pcAsg = '\0'; /*Add '\0' chracter at the end*/

	return pcDest;
}

/*------------------------------------------------------------------*/
/*StrCompare(): 
  from the parameter pcS1 and pcS2, compare each chracter with
  ASCII code. If chracter are different, return the value of 
  ASCII code difference.                                         */
/*------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
	const char* pcOne;
	const char* pcSec;
	
	assert(pcS1 != NULL && pcS2 != NULL);/*Asserting parameters are not NULL*/

	pcOne = pcS1;
	pcSec = pcS2;

	while(*pcOne!='\0' && *pcSec!='\0'){/*until we meet the '\0' chracter*/
		if(*pcOne == *pcSec ){/*Compare chracter*/
			pcOne++;
			pcSec++;
		}
		else{
			return *pcOne - *pcSec;
		}
	}
 
  return *pcOne - *pcSec;
}

/*------------------------------------------------------------------*/
/*StrCompare(): 
  from the parameter pcS1 and pcS2, compare each chracter with
  ASCII code. If chracter are different, return the value of 
  ASCII code difference.                                         */
/*------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
	/*FIND: we enter FIND state, when some of chracter in pcNeedle matches to pcHaystack*/
	enum DFAState {FIND, NON};
	enum DFAState state;

	state = NON; /*Initial starting state is NON*/

	const char* pcOrig;
	const char* pcFind;
	const char* pcTarget;

	assert(pcHaystack != NULL && pcNeedle != NULL);/*Asserting parameters are not NULL*/

	pcOrig = pcHaystack;
	pcTarget = pcNeedle;
	pcFind = NULL;

	if(!(*pcNeedle)){/*If we searching with empty string, just return original pcHaystack*/
		return (char*)	pcHaystack;
	}
	while(*pcOrig){
		switch(state){
			case NON:
				if(*pcOrig == *pcTarget){
					pcFind = pcOrig;/*Save the first matching address*/
					pcOrig++;
					pcTarget++;
					state = FIND;
				}
				else{
					pcOrig++;
					state = NON;
				}
				break;

			case FIND:
				
				if(*pcOrig == *pcTarget){
					pcOrig++;
					pcTarget++;
					state = FIND;

					/*pcTarget matches all chracter, meaning that we find pcNeedle in pcHaystack*/
					if(*pcTarget == '\0'){
						return (char*)pcFind;
					}
				}
				else{
					/*Initialize pcTarget to pcNeedle so that we can search another matches*/
					pcTarget = pcNeedle;
					state = NON;
				}
				break;

			default:
				assert(0);
				break;
		}
	}
	return (char*) NULL; /*If there is no matching, return NULL pointer*/
}
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
	char *c_first;
	const char *c_second;
	char *c_output;

	assert(pcDest != NULL && pcSrc != NULL);/*Assering parameteres are not NULL*/

	c_first = pcDest;
	c_second = pcSrc;

	c_output = c_first;

	while(*c_output != '\0'){/*Find the ending '\0*/
		c_output++;
	}

	while(*c_second != '\0'){/*Concatenate pcSrc*/
		*c_output = *c_second;
		c_output++;
		c_second++;
	}
	*c_output = '\0'; /*Add ending '\0'*/

  return pcDest;	
}
