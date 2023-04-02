#include <iostream>
#include <main.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//#include <stdio.h>      /* printf, fgets */
//#include <stdlib.h> 
#include <cmath> 
#include <bits/stdc++.h>
//#include <ctime>
#include <semaphore.h>
using namespace std;

double** cylinder;
double** nextCylinder;
bool done[100] = {false};
long FLOPS = 0;
int height;
int width;
double c0;
double c1;
double c2;
double delta;
int max1;
sem_t ending[100];
sem_t starting[100];
int iter = 0;
sem_t addvalue;
int threads;

int findvaluei(int i, int j,int t)
{
  int value = 0;
  for(int q = i; q < height; q++)
    {
      for(int w = j; w < width; w++)
	{
	  if(value == t)
	    return q;
	  else
	    value++;
	}
      j = 0;
    }
  return 100;
  
}
int findvaluej(int i, int j,int t)
{
  int value = 0;
  //cout << t << endl;
  for(int q = i; q < height; q++)
    {
      for(int w = j; w < width; w++)
	{
	  if(value == t)
	    return w;
	  else
	    value++;
	}
      j =0;
    }
  return 100;
  
}
       
void *forloop(void *param)
{
  double first = 0;
  double second = 0;
  double third = 0;
  double final = 0;
  double previousfinal = 0;
  double difference = 0;
  int p = *((int*)param);
 
  while(iter < max1)
    {
      sem_wait(&starting[p]);
      int j;
      int i;
      sem_wait(&addvalue);
      for(int o = 0; o < ((height*width)/threads)+1;o++)
	{
	  if(o == 0)
	    {
	      j = findvaluej(0,0,p);
	      i = findvaluei(0,0,p);
	      // cout << "i: " << i << " j: " << j << endl;
	    }
	  else
	    {
	      int lastj = j;
	      j = findvaluej(i,lastj,threads);
	      i = findvaluei(i,lastj,threads);
	      //cout << "i: " << i << " j: " << j << endl;
	    }
	  if(j < 10 && i < 10)
	    {
	  //cout << "value: "<<cylinder[i][j] << endl;
	 
	  if(i == 0)
	    {
	      if(j == 0)
		{
		  FLOPS = FLOPS+8;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i+1][j] + cylinder[i][j+1])*(c1/.5));
		  third = ((cylinder[i+1][j+1])*c2);
		  final = (first+second+(third*4));
		  
		}//i ==0 j ==0
	      else if(j==(width-1))
		{
		  FLOPS = FLOPS+8;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i+1][j] + cylinder[i][j-1])*(c1/.5));
		  third = ((cylinder[i+1][j-1])*c2);
		  final = (first+second+(third*4));
		 
		}//i==0 j == width-1
	      else
		{
		  FLOPS = FLOPS+10;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i][j-1] + cylinder[i][j+1] + cylinder[i+1][j])*(c1/.75));
		  third = ((cylinder[i+1][j-1] + cylinder[i+1][j+1])*(c2/.5));
		  final = (first+second+third);
		  // cout << final<< endl;
		}//if i ==0 and j!= 0 or width-1
	    }//if i = 0;
	  else if (i < (width -1))
	    {
	      if(j==0)
		{
		  FLOPS = FLOPS+10;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j+1] + cylinder[i+1][j])*(c1/.75));
		  third = ((cylinder[i-1][j+1] + cylinder[i+1][j+1])*(c2/.5));
		  final = (first+second+third);
		  
		}//i is 1 to width -2 and j ==0
	      else if(j==(width-1))
		{
		  FLOPS = FLOPS+10;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j-1] + cylinder[i+1][j])*(c1/0.75));
		  third = ((cylinder[i-1][j-1] + cylinder[i+1][j-1])*(c2/.5));
		  final = (first+second+third);
		  
		}//i is 1 to width-2 and j == width-1
	      else
		{
		  FLOPS = FLOPS+11;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j-1] + cylinder[i][j+1] + cylinder[i+1][j])*c1);
		  third = ((cylinder[i-1][j-1] + cylinder[i-1][j+1] + cylinder[i+1][j-1] + cylinder[i+1][j+1])*c2);
		  final = (first+second+third);
		  
		}//i is between 1 and width-2 and j is between 1 adn width-2
	    }//i is between 1 and width
	  else if(i == (width-1))
	    {
	      if(j==0)
		{
		  FLOPS = FLOPS+8;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j+1])*(c1/.5));
		  third = ((cylinder[i-1][j+1])*c2);
		  final = (first+second+(third*4));
		  
		}//i==width-1 and j ==0
	      else if(j == (width-1))
		{
		  FLOPS = FLOPS+8;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j-1])*(c1/.5));
		  third = ((cylinder[i-1][j-1])*c2);
		  final = (first+second+(third*4));
		  
		}//i == width-1 j == width-1
	      else
		{
		  FLOPS = FLOPS+10;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i-1][j] + cylinder[i][j-1] + cylinder[i][j+1])*(c1/0.75));
		  third= ((cylinder[i-1][j-1] + cylinder[i-1][j+1])*(c2/0.5));
		  final = (first+second+third);
		  
		}
	    }// i == width-1
	  //  cout << "i: " << i << " j: " << j << endl;
	  //cout << final << endl;
	  nextCylinder[i][j] = final;
	    }
	  sem_post(&addvalue);
	  //cout << final << endl;
       
      
	}//end big forloop
      sem_post(&ending[p]);
    }
  pthread_exit(0);
}






int main(int argc, char* argv[])
{
  
  clock_t start;
  clock_t end;
  start = clock();
  srand(time(NULL));
  height = atoi(argv[1]);
  width = atoi(argv[2]);
  double temp = atof(argv[3]);
  
  c0 = atof(argv[4]);
  c1 = atof(argv[5]);
  c2 = atof(argv[6]);
  delta = atof(argv[7]);
  max1 = atoi(argv[8]);
  threads = atoi(argv[9]);
  //cout << findvaluei(1,1,50)<< endl;
  //cout << findvaluej(1,1,50)<< endl;
 

 
      cylinder = new double*[height];
      nextCylinder = new double*[height];
      for(int i = 0; i < width; ++i) {
	cylinder[i] = new double[width];
      }
     
      for(int i = 0; i < width; ++i) {
	nextCylinder[i] = new double[width];
      }

  for(long i = 0; i < height; i++)
    {
      for(long j = 0;j < width; j++)
	{
	  //do{
	  //  double d = rand()%(int)temp + 10;

	  //cylinder[i][j] = d;
	  //nextCylinder[i][j] = d;


	  ///////////////////////
	  ///////////////////////
	  /////Constant Temp/////
	  //Uncomment below//////
	   cylinder[i][j] = temp;
	  nextCylinder[i][j] = temp;
	  /////////////////////////

	  
	  //}while(cylinder[i][j] == temp);
	}
    }

  /*  for(int i = 0; i < height; i++)
    {
      for(int j = 0;j < width; j++)
	{
	  cout << cylinder[i][j];
	}
      cout << endl;
    }
  */
  cout << "Starting Array" << endl;
  //////////////////////////////////////////
  //////////////Test Variables//////////////
  //////////////////////////////////////////
  // Uncomment below
  cylinder[height/2][width/2] = 40;
  cylinder[height/4][width/4] = 0;
  cylinder[height-3][width-3] = 0;
  for(int i = 0; i < height; i++)
    {
      for(int j = 0;j < width; j++)
	{
	  cout << cylinder[i][j] << " ";

	}
      cout << endl;
    }
  pthread_t threadss[threads];
  for(int i = 0; i < threads; i++)
    {
      sem_init(&ending[i],0,0);
      sem_init(&starting[i],0,1);
      
    }
  sem_init(&addvalue,0,1);
  for(int i = 0; i < threads; i++)
    {
     pthread_create(&threadss[i],NULL,forloop,new int(i));
    }
  /////////////////
  //parent thread//
  bool first = true;
  double maxdelta = 0;
  while(iter < max1)
    {
      for(int i = threads-1; i>=0; i--)
	{
	  sem_wait(&ending[i]);
	}
     
      maxdelta = 0;
      for(int i = 0; i < height; i++)
	{
	  for(int j = 0;j < width; j++)
	    {
	      if((abs(cylinder[i][j]-nextCylinder[i][j]))>maxdelta)
		{
		  
		      maxdelta = abs(cylinder[i][j]-nextCylinder[i][j]);
		}
	     
	    }
	  	  
	} //end forloop
       cout << "Max Delta" << maxdelta << endl;
      /*     for(int i = 0; i < height; i++)
	     {
	     for(int j = 0;j < width; j++)
	     {
	     cout << nextCylinder[i][j] << " ";
	     }
	     cout << endl;
	     }
      */
      for(int i = 0; i < height; i++)
	{
	  for(int j = 0;j < width; j++)
	    {
	      cylinder[i][j]=nextCylinder[i][j];
	    }
	  
	}
      iter++;
      if(maxdelta <= delta)
	{
	  break;
	}
       for(int i = threads-1; i>=0; i--)
	{
	  sem_post(&starting[i]);
	}
	
    }
  cout<< "_____________End Simulation____________"<< endl;
  cout << " " << endl;
  cout << " " << endl;
  for(int i = 0; i < height; i++)
    {
      for(int j = 0;j < width; j++)
	{
	  cout << nextCylinder[i][j] << " ";
	}
      cout << endl;
    }
  
  int size = height*width;
  double total= 0;
  for(int i = 0; i < height; i++)
    {
      for(int j = 0;j < width; j++)
	{
	  total += nextCylinder[i][j];
	}
      
    }
  int average = total/size;
  
  end = clock();
  cout << "The maximum delta across the cells is: " << maxdelta << endl;
  cout<< "The average temperature across the cells is: "<<average << endl;
  double time_elapsed_ms = double(end-start);
  cout << "CPU time used: " << time_elapsed_ms << " ms\n";
  if(iter == max1)
    {
      cout<< "Exited on Max Iterations" << endl;
    }
  cout << "Estimate of number of FLOPS " << FLOPS/((time_elapsed_ms/100)*2) << endl;
  // delete argv;

  for(int i = 0; i < height; ++i) {
    delete [] cylinder[i];
    delete [] nextCylinder[i];
    sem_destroy(&starting[i]);
    sem_destroy(&ending[i]);
    sem_destroy(&addvalue);
  
  }
  delete [] cylinder;
  delete [] nextCylinder;
  
  return 1;

    }


