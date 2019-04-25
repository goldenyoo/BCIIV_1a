/*************************************************************/
 //   File_name: customer_manager1.c
 //   Programmer: Seungjae Yoo                             
 //   Student ID: 20160767                                         
 //   Assignment #3                                         
 //   Last Modified: 2019_04_20                              
 //                                       
 //                    
 //  This code is wrote on Sublime Text
/*************************************************************/
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

  int curBuckSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
           // # whether the array should be expanded
           // # or not
};

struct Table{
  struct UserInfo *pArray[BUCKET_COUNT];
};

struct Table *Table_create(void){
  struct Table *t;
  t = calloc(1,sizeof(struct Table));
  return t;
}


void Table_free(DB_T d){
  struct UserInfo *p;
  struct UserInfo *nextp;
  int b;
  struct Table *t_id;
  struct Table *t_name;
  t_id = d->id_Table;
  t_name = d->name_Table;

  for(b = 0; b < d->curBuckSize; b++){
    for(p = t_id->pArray[b]; p != NULL; p = nextp){
      nextp = p->next_id;
      free(p);
    }
  }
  free(t_id);
  free(t_name);
}




/*--------------------------------------------------------------------*/
DB_T
CreateCustomerDB(void)
{
   
  DB_T d;
  
  d = (DB_T) calloc(1, sizeof(struct DB));
  if (d == NULL) {
    fprintf(stderr, "Can't allocate a memory for DB_T\n");
    return NULL;
  }
  d->curBuckSize = BUCKET_COUNT; // start with 1024 elements

  d->id_Table = Table_create();
  if(d->id_Table == NULL){
    fprintf(stderr, "Can't allocate a memory for Hash Table of size %d\n",
      d->curBuckSize);   
    free(d);
    return NULL;
  }
  
  d->name_Table = Table_create();
  if(d->name_Table == NULL){
    fprintf(stderr, "Can't allocate a memory for Hash Table of size %d\n",
      d->curBuckSize);   
    free(d);
    return NULL;
  }
  d->numItems = 0;
  return d;
  // ???? below?? typo?
  // return NULL;
}
/*--------------------------------------------------------------------*/
void
DestroyCustomerDB(DB_T d)
{
  /* fill out this function */
  // assert(0);
  // return NULL;
  if (d == NULL){
    return ;
  }
  struct UserInfo *p;
  struct UserInfo *nextp;
  int b;
  struct Table *t_id;
  struct Table *t_name;
  t_id = d->id_Table;
  t_name = d->name_Table;

  for(b = 0; b < d->curBuckSize; b++){
    for(p = t_id->pArray[b]; p != NULL; p = nextp){
      nextp = p->next_id;
      free(p);
    }
  }
  free(t_id);
  free(t_name);

  free(d);

}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
  /* fill out this function */
  // assert(0);

  if(d == NULL || id == NULL || name == NULL || purchase < 0 ){
    return (-1);
  }
 
 //Check the duplicate
  int h_id = hash_function(id,d->curBuckSize);
  int h_name = hash_function(name,d->curBuckSize);

struct UserInfo *iter;
for(iter = d->id_Table->pArray[h_id]; iter != NULL; iter = iter->next_id){
  if(strcmp(iter->id,id) == 0){
    return -1;
  }
}
for(iter = d->name_Table->pArray[h_name]; iter != NULL; iter = iter->next_name){
  if(strcmp(iter->name,name) == 0){
    return -1;
  }
}
  // Table_add(d,id,name,purchase);
  struct UserInfo *p = calloc(1, sizeof(struct UserInfo));
  if (p == NULL) {
    fprintf(stderr, "Can't allocate a memory for UserInfo\n");
    return -1;
  }
  

  p->id = strdup(id);
  p->name = strdup(name);
  assert(p->id != NULL); assert(p->name != NULL);
  p->purchase = purchase;
  p->Hash_id = h_id;
  p->Hash_name = h_name;
  p->next_id = d->id_Table->pArray[h_id];
  p->next_name = d->name_Table->pArray[h_name];
  d->id_Table->pArray[h_id] = p;
  d->name_Table->pArray[h_name] = p;





  d->numItems +=1;

  return 0;
}
/*--------------------------------------------------------------------*/
int
UnregisterCustomerByID(DB_T d, const char *id)
{
  /* fill out this function */
  // assert(0);
  if(d == NULL || id == NULL){
    return (-1);
  }
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // int checker = 0;
  // for(i = 0;i<d->numItems;i++){
  //   if(strcmp(iter[i].id,id)==0){
  //     checker = 1;
  //     break;
  //   }
  // }
  // if(checker != 1){
  //   return (-1);
  // }
  // int j;
  // for(j = i; j < d->numItems -1 ;j++){
  //   iter[j].id = strdup(iter[j+1].id);
  //   // iter[j].id = iter[j+1].id;
  //   iter[j].name = strdup(iter[j+1].name);
  //   // iter[j].name = iter[j+1].name;
  // }
  // iter[j].id = NULL;
  // iter[j].name = NULL;

  // d->numItems -= 1;

  return 0;
}

/*--------------------------------------------------------------------*/
int
UnregisterCustomerByName(DB_T d, const char *name)
{
  /* fill out this function */
  // assert(0);
  if(d == NULL || name == NULL){
    return (-1);
  }
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // int checker = 0;
  // for(i = 0;i<d->numItems;i++){
  //   if(strcmp(iter[i].name,name)==0){
  //     checker = 1;
  //     break;
  //   }
  // }
  // if(checker != 1){
  //   return (-1);
  // }
  // int j;
  //   for(j = i; j < d->numItems -1 ;j++){
  //     iter[j].id = strdup(iter[j+1].id);
  //     // iter[j].id = iter[j+1].id;
  //     iter[j].name = strdup(iter[j+1].name);
  //     // iter[j].name = iter[j+1].name;
  //   }
  //   iter[j].id = NULL;
  //   iter[j].name = NULL;

  //   d->numItems -= 1;

    return 0;
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  // assert(0);
  if(d == NULL || id == NULL){
    return (-1);
  }
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // for(i = 0; i < d->numItems; i++){
  //   if(strcmp(id,iter[i].id) == 0){
  //     return iter[i].purchase;
  //   }
  // }
  return (-1);

}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  // assert(0);
  if(d == NULL || name == NULL){
    return (-1);
  }
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // for(i = 0; i < d->numItems; i++){
  //   if(strcmp(name,iter[i].name) == 0){
  //     return iter[i].purchase;
  //   }
  // }
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  // assert(0);
  if(d == NULL || fp == NULL){
    return (-1);
  }
  int sum = 0;
  // int i;
  // struct UserInfo *iter;
  // iter = d->pArray;
  // for(i = 0; i < d->numItems; i++){
  //   sum += (*fp)(iter[i].id,iter[i].name,iter[i].purchase);
  // }
  return sum;
}
