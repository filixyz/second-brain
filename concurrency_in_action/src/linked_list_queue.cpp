#include <memory>
#include <iostream>

template <class T>
class simple_queue{
	struct node {
		T data;
		std::unique_ptr<node> next;
		node(T data_): data(std::move(data_)) {}
	};
	std::unique_ptr<node> head;
	node* tail;
public:
	simple_queue(): tail{nullptr} {}
	simple_queue(const simple_queue&) = delete;
	simple_queue& operator=(const simple_queue&) = delete;
	
	void push(T& new_data){
		std::unique_ptr<node> new_node {new node(std::move(new_data))};
		node* new_node_raw_ptr = new_node.get();
		if (tail)
			tail->next = std::move(new_node);
		else
			head = std::move(new_node);
		tail = new_node_raw_ptr;
	}
	std::shared_ptr<T> try_pop(){
		if(!head)
			return std::shared_ptr<T> {};
		std::unique_ptr<node> old_head = std::move(head);
		head = std::move(old_head->next);
		if(!head)
			tail = nullptr;
		return std::make_shared<T>(std::move(old_head->data));
	}
};

int main()
{
  simple_queue<int> q;
  int a = 1;
  int b = 2;
  int c = 3;
  q.push(a);
  q.push(b);
  q.push(c);
  for (int i = 0; i < 3; ++i)
    std::cout << *q.try_pop() << ' ';
  std::cout << '\n';
}
