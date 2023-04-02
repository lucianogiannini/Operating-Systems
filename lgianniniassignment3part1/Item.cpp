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
  
  generateFood();
}
void Item::generateFood()
{
  int pick = rand() % 3;

  if(pick  == 0)
    {
      food = "jimmies";
    }
  else if(pick == 1)
    {
      food = "ice cream";
    }
  else
    {
      food = "chocolate sauce";
    }
}

string Item::toString()
{
  stringstream result;
  result << "Miss Crabtree puts " <<  food << " on the table";
  return result.str(); 
}
