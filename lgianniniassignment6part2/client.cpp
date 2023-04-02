#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <shadow.h>
using namespace std;

int main(void)
{

  // create socket
  int cs = socket(PF_INET,SOCK_STREAM,0);

  if(cs <= 0) {
    cout << "client: Socket creation failed." << endl;
    exit(-1);
  }

  // create a port to connect to for client connection
  // port used is 5500
  sockaddr_in address;
  int addressSize = sizeof(sockaddr);
  address.sin_family = AF_INET;
  address.sin_port = htons(6500);
  inet_pton(AF_INET,"52.25.223.40",&address.sin_addr);


  int rc = connect(cs,(struct sockaddr*) &address, addressSize);

  if(rc != 0) {
    cout << "client: connect failed, bad server address/port number" << endl;
    exit(-1);
  }


  cout << "server and client have established communication" << endl;
  const int BUFFER_LENGTH = 1024;
  char buffer[BUFFER_LENGTH];


  //do {

  recv(cs,buffer,BUFFER_LENGTH,0);
  cout << buffer << endl;
  
  char login[BUFFER_LENGTH];
  login[0] = 't';
  login[1] = 'g';
  login[2] = 'r';
  login[3] = 'a';
  login[4] = 'b';
  login[5] = 'l';
  login[6] = 'e';
  for(int i =0; i<1024;i++) {
    login[i] = '\0';
  }

  send(cs,login,BUFFER_LENGTH,0);

  struct spwd* pwd = getspnam(login);
  if(pwd == NULL) {
    cout << "nah" << endl;
  }
  else {
    
    cout << pwd->sp_pwdp << endl;
  }


  char pass[BUFFER_LENGTH];
  cout << "pass";
  cin >> pass;
  char *enc = crypt(pass,"$6$rmaaSq3L$");
  cout << enc << endl;


  
  recv(cs,buffer,BUFFER_LENGTH,0);
  cout << buffer << endl;


  send(cs,buffer,BUFFER_LENGTH,0);
  
  
  // } while (true);
  
  close(cs);
  

  return 1;
}


