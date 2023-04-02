#include <Resource.h>
#include <sstream>
#include <stdlib.h>


Resource::Resource()
{
  token = "";
  used = false;
}
Resource::Resource(string f)
{
  token = f;
  used = false;
}
string Resource::toString()
{
  stringstream result;
  result << token << " " << used;

  return result.str(); 

}

