#include <stdio.h>
#include <sys/time.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
using namespace std;

/*
int main(int argc, char **argv)
{
  FILE *cpuinfo = fopen("/proc/cpuinfo", "rb");
  char *arg = 0;
  size_t size = 0;
  while(getdelim(&arg, &size, 0, cpuinfo) != -1)
    {
      puts(arg);
    }
  free(arg);
  fclose(cpuinfo);
  return 0;

}
*/
string timenow(double t)
{
  stringstream timestring;
  int days = 0;
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
if(t/(60*60*24) >= 1)
    {
      days = (int)t/(60*60*24);
      //  cout << days << endl;
      t = t - (days*60*60*24);
    }
    if(t/(60*60) >= 1)
      {
	hours = (int)t/(60*60);
	//cout << hours << endl;
	t = t - (hours*60*60);
      }
    if(t/(60)>=1)
      {
	minutes = (int)t/60;
	//cout << minutes << endl;
	t = t - (minutes*60);
      }
    seconds = t;
    //cout << seconds << endl;
   timestring << setfill('0') << setw(2) << days << ':' << setw(2) << hours << ':' << setw(2) << minutes << ':' << setw(2) << seconds << endl;
   string stringt = timestring.str();
   return stringt;
}

int main(int argc, char* argv[])
{
  ifstream in;
  struct timeval now;
  gettimeofday(&now,NULL);
  cout << "Status report as of: " << ctime((time_t *) &now.tv_sec);

  in.open("/proc/sys/kernel/hostname");
  string s;
  in >> s;
  cout << "Machine name: " << s << endl;
  in.close();

  in.open("/proc/cpuinfo");
  string a;
  do{
  in >> a;
  //  cout << a << endl;
  }while(a != "vendor_id");
  in >> a;
  in >> a;
  cout << "CPU Model: " << a << endl;
  do{
  in >> a;
  //cout << a << endl;
  }while(a != "name");
  in >> a;
  in >> a;
  string b = a;
  while(a!="stepping"){
    in >> a;
    if(a!="stepping")
      {
	b +=" "+a;
      }
  }
  cout << "CPU Model: " << b << endl;
  in.close();

  in.open("/proc/version");
  string c;
  string d;
  in >> c;
  d = c;
  for(int i = 0; i < 2; i++)
    {
      in >> c;
      d += " " + c;
    }
  cout << "Kernel version: " << d << endl;
  in.close();

  in.open("/proc/uptime");
  string time;
  in >> time;
  double time1 = stod(time);
  int time2 = stoi(time);
  int days = 0;
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
  // cout << time << endl;
  //cout << time1 << endl;
  if(time1/(60*60*24) >= 1)
    {
      days = (int)time1/(60*60*24);
      //  cout << days << endl;
      time1 = time1 - (days*60*60*24);
    }
    if(time1/(60*60) >= 1)
      {
	hours = (int)time1/(60*60);
	//cout << hours << endl;
	time1 = time1 - (hours*60*60);
      }
    if(time1/(60)>=1)
      {
	minutes = (int)time1/60;
	//cout << minutes << endl;
	time1 = time1 - (minutes*60);
      }
    seconds = time1;
    //cout << seconds << endl;
    cout << "Time since last boot: " << setfill('0') << setw(2) << days << ':' << setw(2) << hours << ':' << setw(2) << minutes << ':' << setw(2) << seconds << endl;
    in.close();

    in.open("/proc/stat");
    string usermode;
    string nice;
    string systemmode;
    string idlemode;
    string iowait;
    string irq;
    string softirq;
    string last;
    in >> usermode;
    in >> usermode; // processes in user
    in >> nice;
    in >> systemmode;//processes in system
    in >> idlemode;
    in >> iowait;
    in >> irq;
    in >> softirq;
    in >> last;
    int usermodenum = stoi(usermode);
    int nicenum = stoi(nice);
    int systemmodenum = stoi(systemmode);
    int idlemodenum = stoi(idlemode);
    int iowaitnum = stoi(iowait);
    int irqnum = stoi(irq);
    int softirqnum = stoi(softirq);
    int lastnum = stoi(last);
    int total = usermodenum+nicenum+systemmodenum+idlemodenum+iowaitnum+irqnum+softirqnum+lastnum;

    double userpercent = (double)(usermodenum)/(total);
    double systempercent = (double)(systemmodenum)/(total);
    double idlepercent = (double)(idlemodenum)/(total);
    //cout << userpercent << endl;
    //cout << systempercent << endl;
    //cout << idlepercent << endl;

    double usertime = time2*userpercent;
    double systemtime = time2*systempercent;
    double idletime = time2*idlepercent;
    
    //cout << usertime << endl;
    //cout << systemtime << endl;
    //cout << idletime << endl;
    string user = timenow(usertime);
    string sys = timenow(systemtime);
    string idl = timenow(idletime);

    cout << "Time spent in user mode: " << user;
    cout << "Time spent in system mode: " << sys;
    cout << "Time spent in idle mode: " << idl;
    
    in.close();
    in.open("/proc/diskstats");
    string diskstat[11][14];

    for(int i = 0; i < 11; i++)
      {
	for(int j = 0; j < 14; j++)
	  {
	    string y;
	    in >> y;
	    diskstat[i][j] = y;
	    //cout << diskstat[i][j] << " ";
	  }
	//cout << " ! " << endl;
      }
    int diskrequests = 0;
    for(int i = 0; i < 11; i++)
      {
	int o = stoi(diskstat[i][3]);
	int p = stoi(diskstat[i][7]);
	//cout << o << " + " << p << endl;
	diskrequests += o + p;
      }
    cout << "Disk Requests made: " << diskrequests << endl;
    in.close();

    in.open("/proc/stat");
    a = " ";
    while(a != "ctxt")
      {
	in >> a;
      }
    string context;
    in >> context;
    int contextnum = stoi(context);
    cout << "Total number of context switches: " << contextnum << endl;

    string btime;
    in >> btime;
    in >> btime;
    double boottime = stod(btime);
    string boot = timenow(boottime);
    cout << "Time since last boot: " << boot;
    string processes;
    in >> processes;
    in >> processes;

    cout << "Number of processes created since boot: " << processes << endl;
    in.close();


    in.open("/proc/meminfo");
    string mem;
    in >> mem;
    in >> mem;

    cout << "Total memory configured: " << mem << " kB" << endl;

    while(mem != "MemAvailable:")
      {
	in >> mem;
      }
    in >> mem;
    cout << "Amount of Memory available: " << mem << " kB" << endl;

    in.close();
    
    if(argv[1] = "-s")
      {
	int interval = atoi(argv[2]);
	int duration = atoi(argv[3]);
	int iteration = 0;
	  
    while(iteration < duration)
      {
	sleep(interval);
	in.open("/proc/loadavg");
	string load;
	in >> load;
	double loadnum = stod(load);
	cout << "Load Average Now: " <<  load << " = " << loadnum*100 << "%" <<  endl;
	in.close();
	iteration = iteration + interval;
      }
      }   

    
  return 1;
}
