#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAX 5
#define MAX_MSG_LEN 100
typedef struct {
  char message[MAX_MSG_LEN];
}
Message;
typedef struct {
  Message messages[MAX];
  int front;
  int rear;
}
MessageQueue;
void initQueue(MessageQueue * q) {
  q -> front = -1;
  q -> rear = -1;
}
int isEmpty(MessageQueue * q) {
  return q -> front == -1;
}
int isFull(MessageQueue * q) {
  return (q -> rear + 1) % MAX == q -> front;
}
void enqueue(MessageQueue * q, char * msg) {
  if (isFull(q)) {
    printf("Chat is full! Can't send any more messages right now.\n");
    return;
  }
  if (isEmpty(q)) {
    q -> front = 0;
  }
  q -> rear = (q -> rear + 1) % MAX;
  strcpy(q -> messages[q -> rear].message, msg);
  printf("You: %s\n", msg);
}
void dequeue(MessageQueue * q) {
  if (isEmpty(q)) {
    printf("No new messages at the moment.\n");
    return;
  }
  printf("Friend: %s\n", q -> messages[q -> front].message);
  if (q -> front == q -> rear) {
    q -> front = -1;
    q -> rear = -1;
  } else {
    q -> front = (q -> front + 1) % MAX;
  }
}
int main() {
  MessageQueue chatQueue;
  initQueue( & chatQueue);
  int choice;
  char message[MAX_MSG_LEN];
  printf("Welcome to the Chat!\n");
  while (1) {
    printf("\nOptions:\n1. Send a message\n2. Receive a message\n3. Exit\n");
    printf("Choose an option: ");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
      printf("Type your message: ");
      getchar();
      fgets(message, MAX_MSG_LEN, stdin);
      message[strcspn(message, "\n")] = '\0';
      enqueue( & chatQueue, message);
      break;
    case 2:
      dequeue( & chatQueue);
      break;
    case 3:
      printf("Thanks for chatting! Goodbye.\n");
      return 0;
    default:
      printf("Oops! Please enter a valid option.\n");
    }
  }
}
