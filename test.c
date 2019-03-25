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

int main(void){
	const char *s1 = "Hello";
	char s2[128];
/* strcpy()*/
	strcpy(s2,s1);
	printf("%s\n", s2);

	StrCopy(s2,s1);
	printf("%s\n", s2);
	// int len;
	// len = strlen(s1);
	// printf("%d\n", len);


	return 0;
}