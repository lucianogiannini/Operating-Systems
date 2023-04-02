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
using namespace std;

int main(int argc, char* argv[])
{
  clock_t start;
  clock_t end;
  start = clock();
  srand(time(NULL));
  int height = atoi(argv[1]);
  int width = atoi(argv[2]);
  
  double temp = atof(argv[3]);
  
  double c0 = atof(argv[4]);
  double c1 = atof(argv[5]);
  double c2 = atof(argv[6]);
  double delta = atof(argv[7]);
  int max = atoi(argv[8]);

      
      double**  cylinder = new double*[height];
      double**  nextCylinder = new double*[height];
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
	  do{
	    double d = rand()%(int)temp + 10;

	  cylinder[i][j] = d;
	  nextCylinder[i][j] = d;


	  ///////////////////////
	  ///////////////////////
	  /////Constant Temp/////
	  //Uncomment below//////
	  // cylinder[i][j] = temp;
	  //nextCylinder[i][j] = temp;
	  /////////////////////////

	  
	  }while(cylinder[i][j] == temp);
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
  // cylinder[height/2][width/2] = 40;
  //cylinder[height/4][width/4] = 0;
  //cylinder[height-3][width-3] = 0;
       for(int i = 0; i < height; i++)
       {
	 for(int j = 0;j < width; j++)
	   {
	     cout << cylinder[i][j] << " ";
	   }
	 cout << endl;
       }
       
  double first = 0;
  double second = 0;
  double third = 0;
  double final = 0;
  double maxdelta = 0;
  bool done = false;
  int iter = 0;
  double previousfinal = 0;
  double difference = 0;
  long FLOPS = 0;
  while(iter < max)
  {
      
    maxdelta = 0;
      for(int i = 0; i < height; i++)
	{
      for(int j = 0;j < width; j++)
	{
	  
	  if(i == 0)
	    {
	      if(j == 0)
		{
		  FLOPS = FLOPS+8;
		  first = cylinder[i][j] * c0;
		  second  = ((cylinder[i+1][j] + cylinder[i][j+1])*(c1/.5));
		  third = ((cylinder[i+1][j+1])*c2);
		  final = (first+second+(third*4));
		  //cout << final<< endl;
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
		  third = ((cylinder[i-1][j-1] + cylinder[i-1][j+1])*(c2/0.5));
		  final = (first+second+third);
		  
		}
	    }// i == width-1

	  
	  nextCylinder[i][j] = final;
	  //cout << final << endl;
	}//end inner big forloop
      
	}//end big forloop
      cout << " " << endl;
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
  if(iter == max)
    {
      cout<< "Exited on Max Iterations" << endl;
    }
  cout << "Estimate of number of FLOPS " << FLOPS/((time_elapsed_ms/100)*2) << endl;
  // delete argv;

  for(int i = 0; i < height; ++i) {
    delete [] cylinder[i];
    delete [] nextCylinder[i];
  }
  delete [] cylinder;
  delete [] nextCylinder;
    
  return 1;
}
