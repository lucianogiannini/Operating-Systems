#include <iostream>
#include <fstream>

#include <string>
#include <main.h>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>  
#include <algorithm>
using namespace std;

int main()
{
  srand (time(NULL));
  cout<<"Please enter the monoalphabetic ciper: ";
  string cipher = "";
  getline(cin,cipher);
  string alpha []= {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

  string reference []= {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
 
  string cipher_sentence [100];
  string delimiter = " ";
  int count = 0;
  size_t pos = 0;
  string token = "";
  while ((pos = cipher.find(delimiter)) != string::npos) {
    token = cipher.substr(0, pos);
    cipher_sentence[count] = token;
    count++;
    cipher.erase(0, pos + delimiter.length());
  }
  cipher_sentence[count] = cipher;
  string real [count+1];
  for(int j = 0; j < count+1; j++)
    {
      real[j] = cipher_sentence[j];
    }
  while(true)
    {
      for(int j = 0; j < count+1; j++)
    {
      cipher_sentence[j] = real[j];
    } 
      for(int i = 0; i < count+1;i++)
        {
	  for(int j = 0; j < cipher_sentence[i].length();j++)
            {
	      char tem = cipher_sentence[i].at(j);
	      string s;
	      s+=tem;
	      //cout << s << endl;
	      int index = 0;
	      for( int l = 0; l < 26; l++)
		{
		  if(s == reference[l])
		    {
		      index = l;
		      break;
		    }
		}
	      cipher_sentence[i].replace(j,1,alpha[index]);
	      //cout << cipher_sentence[i] << endl;
            }
	  // cout << cipher_sentence[i] << " ";
            
        }
      //cout << endl;
      bool found = false;
	  for(int p = 0; p < count+1; p++)
	    {
	      found = false;
	      string line;
	      ifstream myfile ("dict.txt");
	      while ( getline (myfile,line) )
		{
		  if(cipher_sentence[p] == line)
		    {
		      // cout << cipher_sentence[p] << endl;
		      found = true;
		      break;
		    }
		  
		}
	      
	      myfile.close();
	      if(found == false)
		{
		  break;
		}
	    }
	  if(found)
	    {
	      for(int j = 0; j < count+1; j++)
		{
		  cout << cipher_sentence[j] << " ";
		}
	      cout << endl;
	      for(int j = 0; j < 26; j++)
		{
		  cout << reference[j] << " ";
		}
	      cout << endl;
	    }
	  for(int i = 0; i < 26;i++)
        {
	  int t = rand()%26;
	  string temp = reference[t];
	  reference[t] = reference[i];
	  reference[i] = temp;
        }
      
    }
  return 0;
}
