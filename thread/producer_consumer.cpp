/*
Date: Sometime in 2018 first quarter
Author: Maulik Soni
Author's github id: soni-maulik
Author email: Maulik.Soni@GMail.com


Program Description:
This program shows simple thread creation.
It creates producer and consumer threads operating on a queue.

*/

#include <pthread.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define SIZE 10

void* fun(void* arg)
{
  for(int i=0; i<100; ++i)
      cout << ".";
  cout << "Inside thread" << endl;
}

typedef struct Data
{
  int a[SIZE];
  int head, tail;
  int isFull, isEmpty;
  pthread_mutex_t bufLock;
  pthread_cond_t *notEmpty, *notFull;

  Data()
  {
    head = tail = 0;
    isFull = isEmpty = 0;
    pthread_mutex_init(&bufLock, NULL);
    notEmpty = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
    notFull = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

    pthread_cond_init(notEmpty, NULL);
    pthread_cond_init(notFull, NULL);
  }
}Data;

void* produce(void* d)
{
  Data* q = (Data *)d;
  for(int i=0; i<SIZE*2; ++i)
  {
    pthread_mutex_lock(&q->bufLock);
    while(q->isFull) {
      pthread_cond_wait(q->notFull, &q->bufLock);
    }

    //cout << "produced: " << i << ",";
    cout << "-";
    q->a[q->tail] = i;
    q->tail = (q->tail + SIZE + 1)%SIZE;
    if(q->tail == q->head)	q->isFull = 1;
    q->isEmpty = 0;
    pthread_mutex_unlock(&q->bufLock);

    pthread_cond_signal(q->notEmpty);
  }

  return NULL;
}

void* consume(void* d)
{
  Data* q = (Data*)d;
  cout << "Consumer created" << endl;
  for(int i=0; i<SIZE*2; ++i)
  {
    pthread_mutex_lock(&q->bufLock);
    while(q->isEmpty) {
      pthread_cond_wait(q->notEmpty, &q->bufLock);
    }

    //cout << "Consumed: " << q->a[q->head] << ",";
    cout << "|";
    q->head = (q->head + SIZE + 1) % SIZE;
    if(q->head == q->tail)	q->isEmpty  = 1;
    q->isFull = 0;
    pthread_mutex_unlock(&q->bufLock);

    pthread_cond_signal(q->notFull);
  }

  return NULL;
}

int main(int gc, char* gv[])
{
  pthread_t th;
  pthread_create(&th, NULL, fun, NULL);
  cout << "Created!" << endl;

  pthread_join(th, NULL);


  pthread_t prod, cons;
  Data d;

  pthread_create(&cons, NULL, consume, &d);
  pthread_create(&prod, NULL, produce, &d);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);
  cout << "Joined main thread!" << endl;
  return 0;
}

