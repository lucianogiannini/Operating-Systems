#include <string>
using namespace std;

const int TICKER_SIZE=4;

class Item
{
 public:
  int number;

  Item(int n);
  string toString();
};
