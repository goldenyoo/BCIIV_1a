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
			*pcOne++;
			*pcSec++;
		}
		else{
			return *pcOne - *pcSec;
		}
	}
 
  return *pcOne - *pcSec;
}

int main(void){
	const char *s1 = "aaaaa"; // 9797102
	char s2[128];
	const char *s3 = "aaaaa";// 100

/* strcpy()*/
	strcpy(s2,s1);
	printf("%s\n", s2);

	StrCopy(s2,s1);
	printf("%s\n", s2);
	// int len;
	// len = strlen(s1);
	// printf("%d\n", len);

	printf("%d \n", strcmp(s1,s3));
	printf("%d \n", StrCompare(s1,s3));
	

	if (*s1 >= *s3){
		printf("%d\n", 12);
	}
	else if(*s1 < *s3){
		printf("%d\n", 15);
	}

	return 0;
}