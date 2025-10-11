#include <chrono>
#include <iostream>

typedef std::chrono::duration<int, std::ratio<24*60*60, 1>> day;

int main()
{
  std::chrono::minutes mins {100000};
  std::cout << std::chrono::duration_cast<day>(mins).count() << std::endl;
}
