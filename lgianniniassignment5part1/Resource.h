#include <string>
using namespace std;

class Resource
{
 public:
  string token;
  bool used;
  Resource();
  Resource(string f);
  string toString();
};
