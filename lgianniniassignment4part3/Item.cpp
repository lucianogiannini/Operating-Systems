#include <Item.h>
#include <sstream>
#include <stdlib.h>

static bool firstTime = false;
Item::Item()
{
  if(firstTime)
    {
      srand(time(0));
      firstTime = false;
    }
  
  generateTicker();
  generatePrice();
}
void Item::generateTicker()
{
  ticker[0] = 'A' + rand() % 26;
  ticker[1] = 'A' + rand() % 26;
  ticker[2] = 'A' + rand() % 26;
  ticker[3] = '\0';
}

void Item::generatePrice()
{
  price = (rand() % 1000) + 1;
  
}
string Item::toString()
{
  stringstream result;
  result << "[ " <<  ticker << "]=" << price;

  return result.str(); 

}
