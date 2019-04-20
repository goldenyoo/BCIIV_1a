#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "customer_manager.h"



#define UNIT_ARRAY_SIZE 1024

struct UserInfo {
  char *name;                // customer name
  char *id;                  // customer id
  int purchase;              // purchase amount (> 0)
};

struct DB {
  struct UserInfo *pArray;   // pointer to the array
  int curArrSize;            // current array size (max # of elements)
  int numItems;              // # of stored items, needed to determine
			     // # whether the array should be expanded
			     // # or not
};



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
  d->curArrSize = UNIT_ARRAY_SIZE; // start with 1024 elements
  d->pArray = (struct UserInfo *)calloc(d->curArrSize,
               sizeof(struct UserInfo));
  if (d->pArray == NULL) {
    fprintf(stderr, "Can't allocate a memory for array of size %d\n",
	    d->curArrSize);   
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
  struct UserInfo *iter;
  iter = d->pArray;
  int i;
  for(i = 0; i < d->numItems;i++){//? free upto where??
    free(iter[i].id);
    free(iter[i].name);
  }
 
  free(d->pArray);
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
  struct UserInfo *iter;
  iter = d->pArray;

  // while(iter != NULL){
  //   if(strcmp(iter->id,id)== 0 || strcmp(iter->name,name)== 0 ){
  //     return (-1);
  //   }
  //   iter++;
  // }
  // data = calloc(1, sizeof(struct UserInfo));

  // if((data->name = strdup(name)) == NULL || (data->id = strdup(id)) == NULL ){
  //   return (-1);
  // }
  // data->purchase = purchase;
  // iter = data;


  int i;
  for(i = 0;i<d->numItems;i++){
    if(strcmp(iter[i].id,id)==0 || strcmp(iter[i].name,name)==0){
      return -1;
    }
  }
  if((iter[i].name = strdup(name))== NULL || (iter[i].id = strdup(id)) == NULL){
    return -1;
  }
  iter[i].purchase = purchase;
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
  struct UserInfo *iter;
  iter = d->pArray;
  int i;
  int checker = 0;
  for(i = 0;i<d->numItems;i++){
    if(strcmp(iter[i].id,id)==0){
      checker = 1;
      break;
    }
  }
  if(checker != 1){
    return (-1);
  }

  DB_T tmp;

  if(d->numItems == 1){
    tmp = CreateCustomerDB();
    DestroyCustomerDB(d);
    d = tmp;
  }
  else{
    tmp = CreateCustomerDB();
    int j;
    int brk = 0;
    for(j = 0;j<d->numItems;j++){
      if(j == i){
        brk = -1;
        continue;
      }
      else{
        RegisterCustomer(tmp,iter[j+brk].id,iter[j+brk].name,iter[j+brk].purchase);
      }
    }
    tmp->numItems = d->numItems;
    DestroyCustomerDB(d);
    d = tmp;
    assert(d != NULL);
    d->numItems -=1;
    assert(d->numItems >=0);
  }
  
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
  struct UserInfo *iter;
  iter = d->pArray;
  int i;
  int checker = 0;
  for(i = 0;i<d->numItems;i++){
    if(strcmp(iter[i].name,name)==0){
      checker = 1;
      break;
    }
  }
  if(checker != 1){
    return (-1);
  }
  DB_T tmp;
  if(d->numItems == 1){
    tmp = CreateCustomerDB();
    DestroyCustomerDB(d);
    d = tmp;
  }
  else{

    tmp = CreateCustomerDB();
    int j;
    int brk = 0;
    for(j = 0;j<d->numItems;j++){
      if(j == i){
        brk = -1;
        continue;
      }
      else{
        RegisterCustomer(tmp,iter[j+brk].id,iter[j+brk].name,iter[j+brk].purchase);
      }
    }
    tmp->numItems = d->numItems;
    DestroyCustomerDB(d);
    d = tmp;
    assert(d != NULL);
    d->numItems -=1;
    assert(d->numItems >=0);
  }
  return 0;
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByID(DB_T d, const char* id)
{
  /* fill out this function */
  assert(0);
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetPurchaseByName(DB_T d, const char* name)
{
  /* fill out this function */
  assert(0);
  return (-1);
}
/*--------------------------------------------------------------------*/
int
GetSumCustomerPurchase(DB_T d, FUNCPTR_T fp)
{
  /* fill out this function */
  assert(0);
  return (-1);
}
