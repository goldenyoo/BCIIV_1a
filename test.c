#include <stdio.h>
#include <string.h>
#include <assert.h> 

size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}


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

char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  /* TODO: fill this function */
	enum DFAState {FIND, NON};
	enum DFAState state;

	state = NON;

	const char* pcOrig;
	const char* pcTarget;
	const char* pcFind;
	const char* pcTmp;

	pcOrig = pcHaystack;
	pcTarget = pcNeedle;
	pcTmp = pcNeedle;
	pcFind = NULL;

	while(*pcOrig){
		switch(state){
			case NON:
				if(*pcOrig == *pcTarget){
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
				if(*pcTmp == '\0'){
					return (char*)pcFind;
				}

				if(*pcOrig == *pcTmp){
					pcOrig++;
					pcTmp++;
					state = FIND;
				}
				else{
					pcOrig++;
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

int main(void){
	const char *s1 = "aaaaa"; // 9797102
	char s2[128];
	const char *s3 = "baaaa";// 100

	const char *s4 = "a acbboy at ";// 100
	const char *s5 = "boy";// 100
	const char *ptr;

	ptr = strstr(s4,s5);
	printf("%s\n", ptr);
	ptr = StrSearch(s4,s5);
	printf("%s\n", ptr);

/* strcpy()*/
	// strcpy(s2,s1);
	// printf("%s\n", s2);

	// StrCopy(s2,s1);
	// printf("%s\n", s2);
	// int len;
	// len = strlen(s1);
	// printf("%d\n", len);

	// printf("%d \n", strcmp(s1,s3));
	// printf("%d \n", StrCompare(s1,s3));
	

	
	return 0;
}