#include <stdlib.h>
#include <stdio.h>

struct Node{
  int data;
  struct Node* next;
}Node;

struct Node* head;

void Insert(int x);
void Print();

int main(){
  head = NULL;
  int n , i,x;
  printf("How many numbers?\n" );
  scanf("%d",&n );
  for(i  = 0; i< n ; i++){
    printf("Enter the number \n" );
    scanf("%d",&x );

    Insert(x);

    Print();
  }
}

void Insert(int x){
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
  temp->data = x;
  temp->next = NULL;
  if(head != NULL) temp->next = head;
  head = temp;
}

void Print(){
  struct Node* temp = head;
  printf("List is: \n" );
  while(temp != NULL){
    printf("%d ", temp->data);
    temp = temp->next;
  }
  printf("\n" );
}
