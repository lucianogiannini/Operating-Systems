#include <Item.h>
#include <sstream>
#include <stdlib.h>

static bool firstTime = false;
Item::Item(int n)
{
  number = n;
}

string Item::toString()
{
  stringstream result;
  result << "Patient " <<  number;

  return result.str(); 

}
