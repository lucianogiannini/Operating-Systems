#include <iostream>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <main.h>
#include <fstream>
#include <queue>
using namespace std;

int main(void)
{
  srand(time(NULL));
  string line;
  string delimiter = " ";

  size_t pos = 0;
  string token;
  string sequence [100];
  int c = 0;
  getline(cin,line);
    while ((pos = line.find(delimiter)) != string::npos) {
      token = line.substr(0, pos);
      sequence[c] =  token;
      line.erase(0, pos + delimiter.length());
      c++;
    }
  
      sequence[c] =  line;
  
 
  
  
 
      /* for(int i = 0; i <=c; i++)
      {
       cout << sequence[i] << endl;
       }*/
  cout << "FIFO Algorithm" << endl;
  queue<string> q;
  int FIFOpf = 0;
  for(int i = 0; i <= c; i++)
    {
      bool found = false;
      for(int j = 0; j < q.size(); j++)
	{
	  string temp = q.front();
	  q.pop();
	  if(temp == sequence[i])
	    {
	      found = true;
	    }
	  q.push(temp);
	}
      bool pagefault = false;
      if(!found)
	{
	  pagefault = true;
	  if(q.size() == 4)
	    {
	      q.pop();
	      q.push(sequence[i]);
	    
	    }
	  else
	    {
	      q.push(sequence[i]);
	    
	    }
	}
      
      cout << "Page Frames: ";
      for(int p = 0; p < q.size(); p++)
	{
	  string t = q.front();
	  cout << t << " ";
	  q.pop();
	  q.push(t);
	}
      if(pagefault)
	{
	  cout << "Page Fault!";
	  FIFOpf++;
	}
      cout << endl;
     
    }
   cout << "Page Faults: " << FIFOpf << endl;
  cout << endl;
  cout << "LRU Algorithm" << endl;
   queue<string> q1;
   int LRUpf = 0;
  for(int i = 0; i <= c; i++)
    {
      bool found = false;
      int index = 0;
      for(int j = 0; j < q1.size(); j++)
	{
	  string temp = q1.front();
	  q1.pop();
	  if(temp == sequence[i])
	    {
	      found = true;
	      index = j;
	    }
	  q1.push(temp);
	}
      bool pagefault = false;
      if(!found)
	{
	  pagefault = true;
	  if(q1.size() == 4)
	    {
	      q1.pop();
	      q1.push(sequence[i]);
	    
	    }
	  else
	    {
	      q1.push(sequence[i]);
	    
	    }
	}
      else
	{
	  int s = q1.size();
	  for (int k = 0; k < s; k++)
	    {
	      if(k == index)
		{
		  q1.pop();
		}
	      else
		{
		  string tmp =  q1.front();
		   q1.pop();
		 q1.push(tmp);
		}
	    }
	  q1.push(sequence[i]);
	}
      
      cout << "Page Frames: ";
      for(int p = 0; p < q1.size(); p++)
	{
	  string t = q1.front();
	  cout << t << " ";
	  q1.pop();
	  q1.push(t);
	}
      if(pagefault)
	{
	  cout << "Page Fault!";
	  LRUpf++;
	}
      cout << endl;
    }
     cout << "Page Faults: " << LRUpf << endl;
     cout << endl;


     cout << "Optimal Algorithm" << endl;
   queue<string> q2;
   int OPpf = 0;
  for(int i = 0; i <= c; i++)
    {
      bool found = false;
     
      for(int j = 0; j < q2.size(); j++)
	{
	  string temp = q2.front();
	  q2.pop();
	  if(temp == sequence[i])
	    {
	      found = true;
	    }
	  q2.push(temp);
	}
      bool pagefault = false;
      if(!found)
	{
	  pagefault = true;
	  if(q2.size() == 4)
	    {
	      string value [4];
	      int timeuntil[4];
	      for(int b = 0; b < 4; b++)
		{
		  value[b] = q2.front();
		  q2.pop();
		  q2.push(value[b]);
		  // cout << value[b] << " ";
		}
	      //      cout << endl;
	     
	      for(int d = 0; d < 4; d++)
		{bool no = false;
	      for(int b = i; b <= c; b++)
		{
		  if(value[d] == sequence[b])
		    {
		      //  cout << value[d] << " " << sequence[b] << endl;
		      timeuntil[d] = b-i;
		      no = true;
		      break;
		    }
		  if(!no)
		    {
		      timeuntil[d] = 100;
		    }
		}
		}
	      int max = 0;
	      int idx = 0;
	      for(int b= 0; b<4;b++)
		{//cout << timeuntil[b] << " ";
		  if(max < timeuntil[b])
		    {
		      max = timeuntil[b];
		      idx = b;
		    }
		}
	      //cout << endl;
	       int s = q2.size();
	  for (int k = 0; k < s; k++)
	    {
	      if(k == idx)
		{
		  q2.pop();
		}
	      else
		{
		  string tmp =  q2.front();
		   q2.pop();
		 q2.push(tmp);
		}
	    }
	  q2.push(sequence[i]);
	    }
	  else
	    {
	      q2.push(sequence[i]);
	    
	    }
	}
      
      cout << "Page Frames: ";
      for(int p = 0; p < q2.size(); p++)
	{
	  string t = q2.front();
	  cout << t << " ";
	  q2.pop();
	  q2.push(t);
	}
      if(pagefault)
	{
	  cout << "Page Fault!";
	  OPpf++;
	}
      cout << endl;
    }
     cout << "Page Faults: " << OPpf << endl;
   



  
  return 1;
}
