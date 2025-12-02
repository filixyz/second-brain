#include <stack>
#include <iostream>

int main()
{
  std::stack<int> list {};
  list.push(1);
  list.push(2);
  list.push(3);
  list.push(4);
  std::cout << "Last element is 4\n";
  auto topp = std::move(list.top());
  std::cout << "Last element now is " << list.top() << '\n';
  std::cout << "POP!"; list.pop();
  std::cout << "Last element now is " << list.top() << '\n';

}
