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
<<<<<<< HEAD
  if (d == NULL){
    return ;
  }
  struct UserInfo *p, *nextp;
  int b;

  struct Table *t_id, *t_name;
  t_id = d->id_Table; t_name = d->name_Table;
=======
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
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e

  for(b = 0; b < d->curBuckSize; b++){
    for(p = t_id->pArray[b]; p != NULL; p = nextp){
      nextp = p->next_id;
      free(p);
    }
  }
<<<<<<< HEAD
  free(t_id); free(t_name);
  free(d);
=======
  free(t_id);
  free(t_name);

  free(d);

>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
}
/*--------------------------------------------------------------------*/
int
RegisterCustomer(DB_T d, const char *id,
		 const char *name, const int purchase)
{
<<<<<<< HEAD
=======
  /* fill out this function */
  // assert(0);

>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
  if(d == NULL || id == NULL || name == NULL || purchase < 0 ){
    return (-1);
  }
 
 //Check the duplicate
<<<<<<< HEAD
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
=======
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
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
}

/*Table Expansion*/
// if(d->numItems >= 0.75*d->curBuckSize){
//   d->curBuckSize *= 2;
//   struct UserInfo *tmp_arry_id;
//   struct UserInfo *tmp_arry_name;
//   tmp_arry_id = calloc(d->curBuckSize,sizeof(struct UserInfo));
//   tmp_arry_name = calloc(d->curBuckSize,sizeof(struct UserInfo));

//   int b;
//   struct Table *t_id;
//   struct Table *t_name;
//   t_id = d->id_Table;
//   t_name = d->name_Table;
//   struct UserInfo *p;
//   // struct UserInfo *nextp;

//   /*Moving original data to new Hash Table*/
//   for(b = 0; b < (d->curBuckSize)/2; b++){
//     p = t_id->pArray[b];
//     if(p != NULL){
//       tmp_arry_id[b%2].next_id = p->next_id;
//     }
//   }
//   for(b = 0; b < (d->curBuckSize)/2; b++){
//     p = t_name->pArray[b];
//     if(p != NULL){
//       tmp_arry_name[b%2].next_name = p->next_name;
//     }
//   }
//   /*Free the old Hash Table*/
//   free(d->id_Table->pArray);
//   free(d->name_Table->pArray);

//   d->id_Table->pArray = tmp_arry_id;
//   d->name_Table->pArray = tmp_arry_name;

// }

  // Table_add(d,id,name,purchase);
  struct UserInfo *p = calloc(1, sizeof(struct UserInfo));
  if (p == NULL) {
    fprintf(stderr, "Can't allocate a memory for UserInfo\n");
    return -1;
  }
  

  p->id = strdup(id);
  p->name = strdup(name);
  assert(p->id != NULL); assert(p->name != NULL);
<<<<<<< HEAD
  /*All data saved at (struct UserInfo) p */
=======
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
  p->purchase = purchase;
  p->Hash_id = h_id;
  p->Hash_name = h_name;
  p->next_id = d->id_Table->pArray[h_id];
  p->next_name = d->name_Table->pArray[h_name];
<<<<<<< HEAD
  
  /*Add at head of the linked list*/
  d->id_Table->pArray[h_id] = p;
  d->name_Table->pArray[h_name] = p;

  /*Increment the number of item*/
=======
  d->id_Table->pArray[h_id] = p;
  d->name_Table->pArray[h_name] = p;





>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
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
  struct UserInfo *p;
  struct UserInfo *q;
  q = NULL;
<<<<<<< HEAD

=======
  // struct UserInfo *tmp;
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
  int h = hash_function(id,d->curBuckSize);
  int checker = 0;
  for(p = d->id_Table->pArray[h]; p != NULL; p = p->next_id){

    if(strcmp(p->id,id) == 0){
      checker =1;
      break;
    }
    q = p;
  }
<<<<<<< HEAD
  if(checker != 1){
    return -1;
  }
=======
printf("OUT1\n");
  if(checker != 1){
    return -1;
  }
  // tmp = q->next_id;
  printf("OUT1.5\n");
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
  if(q != NULL){
    q->next_id = p->next_id;
  }
  else{
    d->id_Table->pArray[h] = NULL;
  }
<<<<<<< HEAD
=======
printf("OUT2\n");
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e

  struct UserInfo *l;
  struct UserInfo *m;
  m = NULL;
  checker = 0;
  for(l = d->name_Table->pArray[p->Hash_name]; l != NULL; l = l->next_name){

    if(strcmp(l->id,id) == 0){
      checker =1;
      break;
    }
    m = l;
  }
  if(checker != 1){
    return -1;
  }
  if(m != NULL){
    m->next_name = l->next_name;
  }
  else{
    d->name_Table->pArray[p->Hash_name] = NULL;
  }

  free(l);
  // free(p);

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
  struct UserInfo *p;
  struct UserInfo *q;
  q = NULL;
  // struct UserInfo *tmp;
  int h = hash_function(name,d->curBuckSize);
  int checker = 0;
  for(p = d->name_Table->pArray[h]; p != NULL; p = p->next_name){

    if(strcmp(p->name,name) == 0){
      checker =1;
      break;
    }
    q = p;
  }

  if(checker != 1){
    return -1;
  }
  // tmp = q->next_id;
  if(q != NULL){
    q->next_name = p->next_name;
  }
  else{
    d->name_Table->pArray[h] = NULL;
  }
  struct UserInfo *l;
  struct UserInfo *m;
  m = NULL;
  checker = 0;
  for(l = d->id_Table->pArray[p->Hash_id]; l != NULL; l = l->next_id){

    if(strcmp(l->name,name) == 0){
      checker =1;
      break;
    }
    m = l;
  }
  if(checker != 1){
    return -1;
  }

  if(m != NULL){
    m->next_id = l->next_id;
  }
  else{
    d->id_Table->pArray[p->Hash_id] = NULL;
  }
  free(l);
  // free(p);

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
<<<<<<< HEAD

  struct UserInfo *p;
  int h = hash_function(id,d->curBuckSize);
  int checker = 0;
  for(p = d->id_Table->pArray[h]; p != NULL; p = p->next_id){
    if(strcmp(p->id,id) == 0){
      checker =1;
      break;
    }
  }
  if(checker != 1){
    return -1;
  }
  else{
    return p->purchase;
  }
=======
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // for(i = 0; i < d->numItems; i++){
  //   if(strcmp(id,iter[i].id) == 0){
  //     return iter[i].purchase;
  //   }
  // }
  return (-1);

>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
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
<<<<<<< HEAD
  struct UserInfo *p;
  int h = hash_function(name,d->curBuckSize);
  int checker = 0;
  for(p = d->name_Table->pArray[h]; p != NULL; p = p->next_name){
    if(strcmp(p->name,name) == 0){
      checker =1;
      break;
    }
  }
  if(checker != 1){
    return -1;
  }
  else{
    return p->purchase;
  }
=======
  // struct UserInfo *iter;
  // iter = d->pArray;
  // int i;
  // for(i = 0; i < d->numItems; i++){
  //   if(strcmp(name,iter[i].name) == 0){
  //     return iter[i].purchase;
  //   }
  // }
  return (-1);
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
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
<<<<<<< HEAD
  struct UserInfo *p;
  struct UserInfo *nextp;
  int b;
  for(b =0; b< d->curBuckSize ; b++){
    for(p = d->id_Table->pArray[b]; p != NULL; p =nextp){
      sum += (*fp)(p->id,p->name,p->purchase);
      nextp = p->next_id;
    }
  }
=======
  // int i;
  // struct UserInfo *iter;
  // iter = d->pArray;
  // for(i = 0; i < d->numItems; i++){
  //   sum += (*fp)(iter[i].id,iter[i].name,iter[i].purchase);
  // }
>>>>>>> ac8716076bae3a328e0ca3f446b0c4442a610d0e
  return sum;
}
