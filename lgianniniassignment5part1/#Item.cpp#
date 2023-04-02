#include <Item.h>
#include <sstream>
#include <stdlib.h>

static bool firstTime = false;
Item::Item()
{
  first = "";
  action = "";
  last = "";
}
Item::Item(string f, string a, string l)
{
  first = f;
  action = a;
  last = l;
}


string Item::toString()
{
  stringstream result;
  result << first << " " << action << " " << last;

  return result.str(); 

}
