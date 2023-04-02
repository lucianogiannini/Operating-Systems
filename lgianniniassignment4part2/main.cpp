#include <iostream>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <main.h>
#include <Item.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int BUFFER_SIZE = 10;
queue<Item> q;
sem_t chairs;
sem_t examining;
sem_t patients[13];
void *patient(void *param)
{
  int p = *((int*)param);
  Item next(p);
  while(true)
    {
      //create spce for local copy of item
      
       cout << next.toString() << " knocks on doctors door"<< endl;
      //critical section
       if(q.size() > 10)
	 {
	   cout << "There are no available chairs to wait in" << endl;
	   cout << next.toString() << " leaves the doctors office"<< endl;
	   sleep(rand()%10+5);
	   continue;
	 }
      sem_wait(&chairs); // <--subtract one from used // blook if used is 0
      if(!q.empty())
	{
	  cout << next.toString() << " is waiting in a chair"<< endl;
	  q.push(next);
	  sem_post(&examining);// add one to count of empty
      
	  sem_wait(&patients[p-1]);
	}
      else
	{
	  cout << next.toString() << " walks into doctors examining room"<< endl;
	  q.push(next);
	  sem_post(&examining);// add one to count of empty
	  sem_wait(&patients[p]);
	  cout << next.toString() << " leaves the doctors office" << endl;
	  sleep(rand()%10+5);
	}
      //critical section
      
      
    }

}
int main(void)
{ srand(time(NULL));
  sem_init(&chairs,0,BUFFER_SIZE);
  sem_init(&examining,0,0);
  sem_init(&patients[0],0,0);
  sem_init(&patients[1],0,0);
  sem_init(&patients[2],0,0);
  sem_init(&patients[3],0,0);
  sem_init(&patients[4],0,0);
  sem_init(&patients[5],0,0);
  sem_init(&patients[6],0,0);
  sem_init(&patients[7],0,0);
  sem_init(&patients[8],0,0);
  sem_init(&patients[9],0,0);
  sem_init(&patients[10],0,0);
  sem_init(&patients[11],0,0);
  sem_init(&patients[12],0,0);
  
  
  pthread_t p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
  pthread_create(&p1,NULL,patient,new int(1));
  pthread_create(&p2,NULL,patient,new int(2));
  pthread_create(&p3,NULL,patient,new int(3));
  pthread_create(&p4,NULL,patient,new int(4));
  pthread_create(&p5,NULL,patient,new int(5));
  pthread_create(&p6,NULL,patient,new int(6));
  pthread_create(&p7,NULL,patient,new int(7));
  pthread_create(&p8,NULL,patient,new int(8));
  pthread_create(&p9,NULL,patient,new int(9));
  pthread_create(&p10,NULL,patient,new int(10));
  pthread_create(&p11,NULL,patient,new int(11));
  pthread_create(&p12,NULL,patient,new int(12));
  pthread_create(&p13,NULL,patient,new int(13));
  
  while(true)
    {
     //create a new item to put in shared memory
      
      if(q.empty())
	{
	  cout << "Doctor: I start to fall asleep" << endl;
	}
      //begin critical section
      sem_wait(&examining); // if empty = 0 wait and subtract one from empty
      Item next = q.front();
      
      sem_post(&chairs); // <-- adds one to used 
      //end critical section
      
      cout << "Doctor: Examining " << next.toString() << endl;
      sleep(rand()%5);
      q.pop();
      cout << "Doctor: Goodbye " << next.toString() << endl;
      sem_post(&patients[next.number-1]);
    }
  sem_destroy(&examining);
  sem_destroy(&chairs);
  sem_destroy(&patients[0]);
  
  return 1;
}
