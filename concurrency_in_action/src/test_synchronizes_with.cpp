#include <thread>
#include <atomic>
#include <iostream>

std::atomic<int> data[5];
std::atomic<bool> sync(false);

void thread_1()
{
  std::cout << "--------------------------------------------------------\n";
  std::cout << " This is thread_1; my values are multiples of 5 till 25\n";
  std::cout << "--------------------------------------------------------\n";

  data[0].store(5, std::memory_order_relaxed);
  data[1].store(10, std::memory_order_relaxed);
  data[2].store(15, std::memory_order_relaxed);
  data[3].store(20, std::memory_order_relaxed);
  data[4].store(25, std::memory_order_relaxed);
  sync.store(true, std::memory_order_release);

  std::cout << "--------------------------------------------------------\n";
  std::cout << " Thread_1 Done\n";
  std::cout << "--------------------------------------------------------\n\n";
  
}

void thread_2()
{
  std::cout << "--------------------------------------------------------\n";
  std::cout << " Thread_2 now running, if output corresponds with what\n";
  std::cout << " Thread_1 stated Then we both successfully Synchronized-With\n";
  std::cout << "--------------------------------------------------------\n";

  while(!sync.load(std::memory_order_acquire));
  std::cout << '\t' << data[0].load(std::memory_order_relaxed) << '\n';
  std::cout << '\t' << data[1].load(std::memory_order_relaxed) << '\n';
  std::cout << '\t' << data[2].load(std::memory_order_relaxed) << '\n';
  std::cout << '\t' << data[3].load(std::memory_order_relaxed) << '\n';
  std::cout << '\t' << data[4].load(std::memory_order_relaxed) << '\n';

  std::cout << "--------------------------------------------------------\n";
  std::cout << " Thread_2 Done\n";
  std::cout << "--------------------------------------------------------\n\n";
}

int main()
{
  std::thread t2 {thread_2};
  std::thread t1 {thread_1};
  t2.join(); t1.join();
}
