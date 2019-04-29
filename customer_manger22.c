/*************************************************************/
 //   File_name: customer_manager2.c
 //   Programmer: Seungjae Yoo                             
 //   Student ID: 20160767                                         
 //   Assignment #3                                         
 //   Last Modified: 2019_04_26                             
 //                                       
 //                    
 //  This code is wrote on Sublime Text
/*************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "customer_manager.h"


enum {HASH_MULTIPLIER = 65599};
enum {BUCKET_COUNT = 1024};
#define UNIT_ARRAY_SIZE 1024


/* Return a hash code for pcKey that is between 0 and iBucketCount-1,
   inclusive. Adapted from the EE209 lecture notes. */
static int hash_function(const char *pcKey, int iBucketCount){
   int i;
   unsigned int uiHash = 0U;
   for (i = 0; pcKey[i] != '\0'; i++)
      uiHash = uiHash * (unsigned int)HASH_MULTIPLIER
               + (unsigned int)pcKey[i];
   return (int)(uiHash % (unsigned int)iBucketCount);
}

struct UserInfo{
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
  int Hash_id;
  int Hash_name;

  struct UserInfo (*next_id);
  struct UserInfo (*next_name);

};

struct DB {
  struct Table *id_Table;   // pointer to the array
  struct Table *name_Table;   // pointer to the array

  int curBuckSize;            // current Bucket size 
  int numItems;              // # of stored items, needed to determine
           // # whether the array should be expanded
           // # or not
};

struct Table{
  struct UserInfo **pArray;
};

struct Table *Table_create(void){
  struct Table *t;
  t = calloc(1,sizeof(struct Table));
  return t;
}


/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
   
  DB_T d;
  
  d = (DB_T) calloc(1, sizeof(struct DB));
  /*Verify d pointer*/
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  /*Set the initial size of Bucket*/
  d->curBuckSize = BUCKET_COUNT; // start with 1024 elements

  /*Create Hash Table for id*/
  d->id_Table = calloc(1,sizeof(struct Table));
  d->id_Table->pArray = calloc(BUCKET_COUNT,sizeof(struct UserInfo *));
  printf("dsfsdfsdfsf\n");
  if(d->id_Table->pArray == NULL){//Verify id_Table
    fprintf(stderr, "Can't allocate a memory for Hash Table of size %d\n",
      d->curBuckSize);   
    free(d);
    return NULL;
  }
  
  /*Create Hash Table for name*/
  d->name_Table = calloc(1,sizeof(struct Table));
  d->name_Table->pArray = (struct UserInfo **) calloc(BUCKET_COUNT,sizeof(struct UserInfo  *));
  if(d->name_Table->pArray == NULL){//Verify name_Table
    fprintf(stderr, "Can't allocate a memory for Hash Table of size %d\n",
      d->curBuckSize);   
    free(d);
    return NULL;
  }
  /*Initialize the number of items*/
  d->numItems = 0;
  
  return d;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /*Verify the d*/
  if (d == NULL){
    return ;
  }
  
  int b;
  struct UserInfo *p, *nextp;
  struct Table *t_id, *t_name;
  /*t_id, t_name is Hash Table for id and name*/
  t_id = d->id_Table; t_name = d->name_Table;

  /*Freeing the data througn id_Table*/
  for(b = 0; b < d->curBuckSize; b++){
    for(p = t_id->pArray[b]; p != NULL; p = nextp){
      nextp = p->next_id;
      free(p);
    }
  }
  /*Free the Table*/
  free(t_id); free(t_name);
  /*Free the DB*/
  free(d);

  return ;
}
/*--------------------------------------------------------------------*/
int TableExpansion(DB_T d){
 return 0; 
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
     const char *name, const int purchase)
{
  /*Verify the parameters*/
  if(d == NULL || id == NULL || name == NULL || purchase < 0 ){
    return (-1);
  }
 
 /*Check the duplicate*/
  int h_id = hash_function(id,d->curBuckSize); int h_name = hash_function(name,d->curBuckSize);
  struct UserInfo *iter;

  for(iter = d->id_Table->pArray[h_id]; iter != NULL; iter = iter->next_id){
    if(strcmp(iter->id,id) == 0){/*ID already exist, return -1*/
      return -1;
    }
  }
  for(iter = d->name_Table->pArray[h_name]; iter != NULL; iter = iter->next_name){
    if(strcmp(iter->name,name) == 0){/*Name already exist, return -1*/
      return -1;
    }
}

/*Table Expansion*/
// if(d->numItems >= 0.75*d->curBuckSize){
//   TableExpansion(d);
// }

  /*allocate memory for new UserInfo*/
  struct UserInfo *p = calloc(1, sizeof(struct UserInfo));
  /*verify the pointer p*/
  if (p == NULL) {
    fprintf(stderr, "Can't allocate a memory for UserInfo\n");
    return -1;
  }
  
  /*Copy id, name to UserInfo*/
  p->id = strdup(id);
  p->name = strdup(name);
  assert(p->id != NULL); assert(p->name != NULL);//verify the strdup()
  
  /*All data saved at (struct UserInfo) p */
  p->purchase = purchase;
  p->Hash_id = h_id;
  p->Hash_name = h_name;
  p->next_id = d->id_Table->pArray[h_id];
  p->next_name = d->name_Table->pArray[h_name];
  
  /*Add at head of the linked list*/
  d->id_Table->pArray[h_id] = p;
  d->name_Table->pArray[h_name] = p;

  /*Increment the number of item*/
  d->numItems +=1;

  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /*Verify the parameter*/
  if(d == NULL || id == NULL){
    return (-1);
  }

  struct UserInfo *p,*q;
  q = NULL;
  int h = hash_function(id,d->curBuckSize);//Hash value for the given id
  int checker = 0;//checker for the id match

 /*Find the UserInfo which has an id*/ 
  for(p = d->id_Table->pArray[h]; p != NULL; p = p->next_id){
    if(strcmp(p->id,id) == 0){//if id is founded, checker is 1 and break the for-loop
      checker =1;
      break;
    }
    q = p;
  }

  /*checker is 0, means there is no such UserInfo*/
  if(checker != 1){
    return -1;
  }
  /*checker is 1, means UserInfo do exist*/
  else{
    if(q != NULL){ //Bucket has more than one linked list elements
      q->next_id = p->next_id;
    }
    else{//Bucket has only one linked list elements
      d->id_Table->pArray[h] = NULL;
    }    
  }

  /*Although Unregistering by ID, name_Table also has to be modified*/
  struct UserInfo *l;
  struct UserInfo *m;
  m = NULL;
  checker = 0;

  for(l = d->name_Table->pArray[p->Hash_name]; l != NULL; l = l->next_name){
    if(strcmp(l->id,id) == 0){//if id is founded, checker is 1 and break the for-loop
      checker =1;
      break;
    }
    m = l;
  }
  /*checker is 0, means there is no such UserInfo*/
  if(checker != 1){
    return -1;
  }
  /*checker is 1, means UserInfo do exist*/
  else{
    if(m != NULL){//Bucket has more than one linked list elements
      m->next_name = l->next_name;
    }
    else{//Bucket has only one linked list elements
      d->name_Table->pArray[p->Hash_name] = NULL;
    }
  }
  /*Free the data*/
  free(l);

  return 0;
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /*Verify the parameter*/
  if(d == NULL || name == NULL){
    return (-1);
  }

  struct UserInfo *p;
  struct UserInfo *q;
  q = NULL;
  int h = hash_function(name,d->curBuckSize);//Hash value for the given name
  int checker = 0;//checker for the name match

  /*Find the UserInfo which has an name*/
  for(p = d->name_Table->pArray[h]; p != NULL; p = p->next_name){
    if(strcmp(p->name,name) == 0){//if name is founded, checker is 1 and break the for-loop
      checker =1;
      break;
    }
    q = p;
  }
  /*checker is 0, means there is no such UserInfo*/
  if(checker != 1){
    return -1;
  }
  /*checker is 1, means UserInfo do exist*/
  else{
    if(q != NULL){//Bucket has more than one linked list elements
      q->next_name = p->next_name;
    }
    else{//Bucket has only one linked list elements
      d->name_Table->pArray[h] = NULL;
    }  
  }
  
  /*Although Unregistering by name, id_Table also has to be modified*/
  struct UserInfo *l;
  struct UserInfo *m;
  m = NULL;
  checker = 0;

  /*Find the UserInfo*/
  for(l = d->id_Table->pArray[p->Hash_id]; l != NULL; l = l->next_id){
    if(strcmp(l->name,name) == 0){
      checker =1;
      break;
    }
    m = l;
  }

  /*checker is 0, means there is no such UserInfo*/
  if(checker != 1){
    return -1;
  }
  /*checker is 1, means UserInfo do exist*/
  else{
    if(m != NULL){
      m->next_id = l->next_id;
    }
    else{
      d->id_Table->pArray[p->Hash_id] = NULL;
    }  
  }
  
  free(l);

  return 0;
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /*Verify the parameters*/
  if(d == NULL || id == NULL){
    return (-1);
  }

  struct UserInfo *p;
  int h = hash_function(id,d->curBuckSize);
  int checker = 0;
  /*Find the UserInfo which has an id*/
  for(p = d->id_Table->pArray[h]; p != NULL; p = p->next_id){
    if(strcmp(p->id,id) == 0){
      checker =1;
      break;
    }
  }

  if(checker != 1){/*There is no such Userinfo*/
    return -1;
  }
  else{
    return p->purchase;
  }
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /*Verify parameters*/
  if(d == NULL || name == NULL){
    return (-1);
  }

  struct UserInfo *p;
  int h = hash_function(name,d->curBuckSize);
  int checker = 0;

  /*Find the UserInfo which has an id*/
  for(p = d->name_Table->pArray[h]; p != NULL; p = p->next_name){
    if(strcmp(p->name,name) == 0){
      checker =1;
      break;
    }
  }
  if(checker != 1){/*There is no such Userinfo*/
    return -1;
  }
  else{
    return p->purchase;
  }
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /*Verify the parameters*/
  if(d == NULL || fp == NULL){
    return (-1);
  }

  int sum = 0;
  struct UserInfo *p;
  struct UserInfo *nextp;
  int b;
  
  /*For all UserInfo in the Table*/
  for(b =0; b< d->curBuckSize ; b++){
    for(p = d->id_Table->pArray[b]; p != NULL; p =nextp){
      sum += (*fp)(p->id,p->name,p->purchase);
      nextp = p->next_id;
    }
  }
  return sum;
}

