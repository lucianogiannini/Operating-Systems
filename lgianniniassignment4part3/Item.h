#include <string>
using namespace std;

const int TICKER_SIZE=4;

class Item
{
 public:
  char ticker[TICKER_SIZE];
  double price;

  Item();
  void generateTicker();
  void generatePrice();
  string toString();
};
