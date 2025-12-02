#include <atomic>
#include <chrono>
#include <iostream>
#include <stack>
#include <thread>

class spinlock_mutex {
  std::atomic_flag lk;

public:
  void lock() {
    while (lk.test_and_set(std::memory_order_acquire));
  }
  void unlock() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    lk.clear(std::memory_order_release);
  }
};

spinlock_mutex mutex;
std::stack<int> global_stack;
bool first_thread_flag = false;

void push_to_stack(int value) {
  const auto start = std::chrono::high_resolution_clock::now();
  mutex.lock(); global_stack.push(value); mutex.unlock();
  const auto end = std::chrono::high_resolution_clock::now();

  if (!first_thread_flag) {
    first_thread_flag = true;
    std::cout << "exclusive ownership of stack took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms from t=0 [First thread]. Pushed " << value << '\n';
  } 
  else
    std::cout << "exclusive ownership of stack took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms from t=0 [ 1 second later from previous thread]. Pushed " << value << '\n';
}

int main() {
  std::thread a(push_to_stack, 1);
  std::thread b(push_to_stack, 2);
  std::thread c(push_to_stack, 3);
  std::thread d(push_to_stack, 4);
  std::thread e(push_to_stack, 5);
  a.join(); b.join(); c.join(); d.join(); e.join();
  std::cout << "----------------------------------------------------------------------------------------------\n";
  std::cout << "    if measured data checks out; thread serialization occured hence spinlock mutex works.\n";
  std::cout << "----------------------------------------------------------------------------------------------\n";
}
