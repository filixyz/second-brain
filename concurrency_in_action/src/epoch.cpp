#include <chrono>
#include <iostream>

int main()
{
  std::chrono::time_point<std::chrono::steady_clock,
    std::chrono::seconds> past (std::chrono::seconds(10));
  auto now = std::chrono::steady_clock::now();
  auto negative_time_elapsed = past - now;
  std::cout << "Time elapsed : " << negative_time_elapsed.count() << std::endl;
}
