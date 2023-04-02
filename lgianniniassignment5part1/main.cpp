#include <iostream>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <main.h>
#include <Item.h>
#include <fstream>
#include <queue>
#include <Resource.h>
#include <list>
using namespace std;
Item list1[100];
Item key[100];

int index_of(Item find, int size)
{
  int counter = 0;
  for(int i = 0; i < size; i++)
    {
      if(find.toString() == list1[i].toString())
	{
	  return i;
	}
    }
  return -1;
}
int main(void)
{
  srand(time(NULL));
  string line;
  int count = 0;
  int c = 0;
  string first = "", second= "", third = "";
  ifstream file("input.txt");
  while(getline(file,line,' '))
    {
      if(count == 0)
	{
	  first  = line;
	  count++;
	}
      else if(count == 1)
	{
	  second = line;
	  count++;
	}
      else
	{
	  third = line;
	  list1[c] = Item(first,second,third);
	  c++;
	  count = 0;
	}
    }
 
  for(int i = 0; i < c; i++)
    {
      key[i] = list1[i];
    }
  string resources [100];
  int in = 0;
  for(int i = 0; i < c; i++)
    {
      cout << list1[i].toString() << endl;
      bool here = false;
           
      for(int j = 0; j < 100; j++)
	{
	  if(list1[i].last == resources[j])
	    {
	      here = true;
	      //cout << list[i].last << endl;

	    }
	}
      if(here == false)
	{
	  resources[in] = list1[i].last;
	  in++;
	}
    }
  Resource reslist[in];
  for(int i = 0; i < in; i++)
    {
      //cout << resources[i] << endl;
      reslist[i] = Resource(resources[i]);
      //cout << reslist[i].toString() << endl;
    }
  int order= 1;
  while(true)
    {
      bool DL = false;
      cout << "ORDER " << order << ": ";
      for(int i = 0; i <c; i++)
	{
	      
	      if(list1[i].action == "req")
		{
	      bool changed = false;
	      for(int j = 0; j < in; j++)
		{
		  if(list1[i].last == reslist[j].token && reslist[j].used == false)
		    {
		      reslist[j].used = true;
		      changed = true;
		      if(i < c-1)
			{
			  cout << list1[i].toString() << ", ";
			}
		      else
			{
			   cout << list1[i].toString() << endl;
			}
		    }
		  
		}
	      if(!changed)
		{
		  cout << list1[i].toString();
		  DL = true;
		      cout << " DEADLOCK!" << endl;
		      break;
		}
	      changed = false;
	    }
	  else
	    {
	      if(i <c-1)
		{
		  cout << list1[i].toString() << ", ";
		}
	      else
		{
		  cout << list1[i].toString() << endl;
		}
	       for(int j = 0; j < in; j++)
		{
		  if(list1[i].last == reslist[j].token)
		    {
		      reslist[j].used = false;
		    }
		}
	    }
	 if(DL)
	   {
	     break;
	   } 
	}
      // if(DL)
       // {
	   // break;
	//	}
      // break;
      //do re order//
      order++;
      ///////////////
      for(int i =0; i < in; i++)
	{
	  reslist[i].used = false;
	}
      bool checked = false;
      while(!checked)
	{
	  for(int i = 0; i < c;i++)
	    {
	      
	      int a = rand() % (c-1);
	      Item temp = list1[a];
	      list1[a] = list1[i];
	      list1[i] = temp;
	      
	    }
	  int n = 0;
	  for( int i = 0; i < c; i = i+n)
	    {
	      int ops = 0;
	      string start = key[i].first;
	      for(int j = i; j < c; j++)
		{
		  if(start == key[j].first)
		    {
		      ops++;
		    }
		}
	      //cout << ops << endl;
	      int references [ops];
	      int pop = 0;
	      for(int j =i; j < i+ops; j++)
		{
		  references[pop] = index_of(key[j],c);
		  pop++;
		}
	      
	      bool swit = false;
	      switch(ops/2)
		{
		case 1:
		  {
		    if(references[0] < references[1])
		      {
			checked = true;
		      }
		    else
		      {
			checked = false;
			swit = true;
			break;
		      }
		    break;
		  }
		case 2:
		  {//cout << "in here" << endl;
		    if(references[0] < references[1])
		      {
			if(references[0] < references[2])
			  {
			    if(references[1] < references[3])
			      {
				checked = true;
			      }
			    else
			      {
				checked = false;
				swit = true;
				break;
			      }
			  }
			else
			  {
			    checked = false;
			    swit = true;
			    break;
			  }
		      }
		     else
		       {
			 checked = false;
			 swit = true;
			 break;
		       }
		    break; 
		  }
		case 3:
		  {
		    if(references[0] < references[1] && references [1] < references[2])
		      {
			if(references[0] < references[3] && references[1] < references[4] && references[2] < references[5])
			  {
			    checked = true;
			  }
			 else
			   {
			     checked = false;
			     swit = true;
			     break;
			   }
		      }
		     else
		       {
			 checked = false;
			 swit = true;
			 break;
		       }
		    break;
		  }
		}
	      if(swit)
		{
		  checked = false;
		  break;
		}
	      n = ops;
	    }
	  
	  //cout << "_______________" << endl;
	}
    }
  
  return 1;
}
