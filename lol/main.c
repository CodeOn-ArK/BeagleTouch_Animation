#include <stdio.h>
#include <unistd.h>
#include<malloc.h>

void func(int *a){
  a = (int *)malloc(sizeof(int));
  scanf("%d", a);
  printf("\nthe value is %d\n", *a);
  
}
int main(){
  int *ptr;
  func(ptr);

  printf("\nthe value is %d\n", *ptr);


  return 0;
}
