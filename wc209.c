/*************************************************************/
 //   File_name: wc209.c
 //   Programmer: Seungjae Yoo                             
 //   Student ID: 20160767                                         
 //   Assignment #1                                          
 //   Last Modified: 2018_03_09                              
 //            
 //                                               
 //	 This code is wrote on Sublime Text
/*************************************************************/

/*-------------------------------------------------------------------*/
/* This code prints the number of lines, words, and characters
  in the input text fed from standard input to standard output.
 Also this code will produce error, when detects unterminated
  comments.                                                         */
/*-------------------------------------------------------------------*/

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

/*Define states: WRD indicates word, CMNT indicates comment*/
enum DFAState {SPACE, WRD, CMNT};
enum DFAState state;

void DFA_SPACE(int *c_current, int *c_previous, int *c_cnt, 
	int *w_cnt, int *l_cnt, int *cmnt_after_space, int *err_l_cnt);
void DFA_WRD(int *c_current, int *c_previous, int *c_cnt, 
	int *w_cnt, int *l_cnt, int *cmnt_after_space, int *err_l_cnt);
void DFA_CMNT(int *c_current, int *c_previous, int *c_cnt, 
	int *w_cnt, int *l_cnt, int *cmnt_after_space, int *err_l_cnt);

/*-------------------------------------------------------------------*/
/* The main function consists of two parts: while-loop with a 
   switch and if-statement. while-loop with a switch represents
   DFA flow. After all DFA flow is executed, if-statement determines 
   whether the unterminated comment exist or not. If the file has some 
   errors the mainn function returns 'EXIT_FAILURE'            */
/*-------------------------------------------------------------------*/
int main(void){
	/*Transitions setting: number of lines, words and characters*/
	int c_cnt, w_cnt, l_cnt;
	c_cnt = 0; w_cnt = 0; l_cnt = 0;

	/*Data from getchar() will be stored in c_current*/
	/*c_previous indicates previous c_current*/
	int c_current, c_previous;
	c_current = 0; c_previous = 0;

	/*Indicates whether comment appears right after the space*/
	int cmnt_after_space;
	cmnt_after_space = FALSE; 

	/*Indicates the number of line that an error has occurred*/
	int err_l_cnt;
	err_l_cnt = 0;

	/*Set SPACE as a start state*/
	state = SPACE;

	while ((c_current = getchar()) != EOF){
		switch (state){
			case SPACE:
				DFA_SPACE(&c_current,&c_previous,&c_cnt,&w_cnt,&l_cnt,
					&cmnt_after_space,&err_l_cnt);
				break;

			case WRD:
				DFA_WRD(&c_current,&c_previous,&c_cnt,&w_cnt,&l_cnt,
					&cmnt_after_space,&err_l_cnt);
				break;

			case CMNT:
				DFA_CMNT(&c_current,&c_previous,&c_cnt,&w_cnt,&l_cnt,
					&cmnt_after_space,&err_l_cnt);
				break;
			default:
				assert(0);
				break;
		}
	}

	if (state == CMNT ){// If state remains at CMNT, it produces an error.
		fprintf(stderr,"Error: line %d: unterminated comment\n", 
			err_l_cnt + 1);
		exit(EXIT_FAILURE);
	}
	else{
		if (c_cnt == 0){// If input file is empty, output should be 0 0 0.
			l_cnt = -1;
		}
		printf("%d %d %d\n", l_cnt + 1, w_cnt, c_cnt);

		return EXIT_SUCCESS;
	}
	
}

/************************************************************************/
/*DFA_SPACE: get the informations of parameters such as c_current,
  c_previous, c_cnt, w_cnt, l_cnt, cmnt_after_space, err_l_cnt. Then 
  performs DFA flow of the state, SPACE. 
  Based on the c_current and c_previous, it will count the number of
  lines, words and chracteres.                                       */
/************************************************************************/
void DFA_SPACE(int *c_current, int *c_previous, int *c_cnt, int *w_cnt,
 int *l_cnt, int *cmnt_after_space, int *err_l_cnt){
	if (isspace(*c_current)){
		state = SPACE;
		++*c_cnt;
		if (*c_current == '\n'){
			++*l_cnt;
		}
	}
	else{
		state = WRD;
		++*w_cnt;
		++*c_cnt;
		*cmnt_after_space = TRUE;
	}
	*c_previous = *c_current;
}
/************************************************************************/
/*DFA_WRD: Same as above. 
  performs DFA flow of the state, WRD.                              */
/************************************************************************/
void DFA_WRD(int *c_current, int *c_previous, int *c_cnt, int *w_cnt,
 int *l_cnt, int *cmnt_after_space, int *err_l_cnt){
	if (isspace(*c_current)){
		state = SPACE;
		++*c_cnt;
		*cmnt_after_space = FALSE;
		if (*c_current == '\n'){
			++*l_cnt;
		}
	}
	else if (*c_current == '*' && *c_previous == '/'){
		state = CMNT;
		*err_l_cnt = *l_cnt;
	}
	else{
		state = WRD;
		++*c_cnt;
		*cmnt_after_space = FALSE;					
	}
	*c_previous = *c_current;
}
/************************************************************************/
/*DFA_CMNT: Same as above. 
  performs DFA flow of the state, CMNT                              */
/************************************************************************/
void DFA_CMNT(int *c_current, int *c_previous, int *c_cnt, int *w_cnt,
 int *l_cnt, int *cmnt_after_space, int *err_l_cnt){
	if (*c_current == '/' && *c_previous == '*'){
		state = SPACE;
		if (*cmnt_after_space){
			--*w_cnt;
			*cmnt_after_space = FALSE;
		}
	}
	else{
		state = CMNT;
		if (*c_current == '\n'){
			++*l_cnt;
			++*c_cnt;
		}
	}
	*c_previous = *c_current;
}

/*************************************************************/
 //   EOF: wc209.c
/*************************************************************/