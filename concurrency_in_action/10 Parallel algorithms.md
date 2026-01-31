The  C++17 standard added the concept of parallel algorithms to STD. They are additional overloads to algorithms that operate on ranges that accept execution policy objects as arguments. These execution policy objects can alter the execution process of the algorithms the are applied upon, potentially granting them the ability to execute in parallel.

An example illustrating the parallel overload for  `std::sort`:
```c++
std::vector<int> my_data;
std::sort(std::execution::par, my_data.begin(), my_data.end());
```
The execution policy of `std::execution::par` indicates to the std that it’s allowed to perform this call as a parallel algorithm. It should be noted that this is a permission not a requirement; std can still execute the code on a single thread if it wishes so.

## Execution policies
The standard specifies three execution policies:
- `std::execution::sequenced_policy`
- `std::execution::parallel_policy`
- `std::execution::parallel_unsequenced_policy`

They are classes defined in the `<execution>` header, the header also defines three corresponding policy object to pass into algorithms
- `std::execution::seq`
- `std::execution::par`
- `std::execution::par_unseq`

we cannot rely on being able to construct these objects from their classes themselves, except by copying the above policy objects. This is because they might require special initialization information that are platform specific.

We also cannot define our own execution policies.

### General effects of specifying an execution policy
Once an execution policy is passed into any of std library algorithms, the behavior of that algorithm is now governed by the execution policy. This affects several aspects of the executions behavior, like:
1) The algorithm’s complexity
2) Behavior when an exception is thrown
3) Where, how and when steps of the algorithm are executed.
#### Effects on Algorithm complexity
If an execution policy is supplied to an algorithm, that algorithms complexity might change, the precise details of the complexity’s change varies with the algorithm.

The general policy is that if an algorithm specifies something will happen exactly *some-expression* or at most *some-expression* times, the execution policy will slacken the requirement to $O(SomeExpression)$; meaning that the overload with the execution policy may perform some multiple of the number of operations it’s counterpart without an execution policy should perform.

#### Exceptional Behavior
Execution policies also determine the consequence of an exception being thrown during an algorithms execution.

All standard execution policies will call `std::terminate` if there are any uncaught exception.

The only exception that may be thrown by a call to an std algorithm governed by some execution policy is `std::bad_alloc`, which occurs when the library was unsuccessful in securing memory resources for it’s internal operations.

For example, the following call to `std::for_each` without an execution policy will propagate the exception:
```c++
std::for_each(v.begin(), v.end(), [](auto x){ throw my_exception(); });
```
whereas the corresponding call with an exception policy will terminate the program:
```c++
std::for_each(
	std::execution::seq, v.begin(), v.end(),
	[](auto x){ return my_exception; };
);
```
This is one of the key difference between using `std::sequential::seq` and not providing an execution policy.

#### Where and when Algorithm steps are executed
This is the fundamental aspect of an execution policy. The policy specifies the agents used to perform the steps of the algorithm, be they “normal”  threads, vector streams, GPU threads or anything else.

Execution policies also specify ordering constraints on execution steps; like whether:
- they are ran in any particular order or not
- parts of the algorithms steps may be interleaved with each other or not
- to run in parallel with each other or not
and so forth.

### `std::execution::sequenced_policy`
This policy is not a policy for parallelism, `sequenced_policy` enforces that that execution of the algorithm bearing this policy must happen on the same thread that called the function.

Not only must all the operations occur on the same thread, the y must also occur in some definite order, so they are not interleaved. Precise order in unspecified and may differ with different invocations of the function. The order of execution may also differ from the order of execution of it’s overload without an execution policy.

An example of this; `std::for_each` invoked to populate a vector of 1000 items will do so in a sequenced order if invoked with it’s overload without an execution policy parameter, This is in contrast with the execution policy accepting overload which will populate in an unspecified order:
```c++
std::vector<int> v(1000);
int count=0;
std::for_each(std::execution::seq, v.begin(), v.end(),
			  [&](auto& x){ x=++count; });
```

### `std::execution::parallel_policy`
This is parallel policy that allows execution among a number of threads, operations  on a given thread must occur in a definite (unspecified) order and not interleaved with each other.

A given operation will run a fixed thread for it’s entire duration. This imposes certain restrictions on iterators, values and callable objects used with the algorithm governed by this policy:
1) they must cause data races if invoked in parallel
2) must not rely being ran on the same thread as any other operations
3) or must not rely on **Not** being ran on the same thread as any other operation
One can mostly use `parallel_policy` in cases where one would had opted to use an algorithm without an execution policy. It’s only in cases that a race condition could occur that this becomes problematic, An example:

This is fine; since there is no shared state that requires a defined order to access:
```c++
std::for_each(std::execution::par,v.begin(),v.end(), [](auto& x){ ++x; });
```
but this would could be problematic if we defined each variable in the vector by incrementing some shared state, since no order is guaranteed with `parallel_policy` and execution of operations can happen on different threads, this is an insidious recipe for a race condition that could lead us to undefined behavior:
```c++
std::for_each(std::execution::par, v.begin(), v.end(),
			  [&](auto& x){ x=++count; });
```
The requirements for `std::execution::parallel_policy` pre-empt’s that it is undefined behavior to invoke this call, even if all operations are executed on a single thread.

Whether or not something exhibits undefined behavior is a static property of the call, rather than some internal implementation detail of the library.

**Synchronization between function invocation is permitted though**, meaning we can make the previous call valid be operating on a vector of `atomic` objects or utilizing some mutex to enforce serialization, but this defeats the purpose of wanting parallel execution.

### `std::execution::parallel_unsequenced_policy`
Parallel unsequenced policy offers the greatest scope for concurrency in exchange for imposing the strictest requirements on the iterators, values and callable object used with  it’s algorithms

An algorithm invoked with this policy may perform it’s steps on an unspecified number of threads, unordered and unsequenced with respect to one another. Meaning that operation can be interleaved with one another on the same thread.

Parallel unsequenced policy forbids that any form of synchronization within calls to iterators, values and callable objects supplied to the algorithm. Functions called must not synchronize with another, or it should not have some code synchronizes with it.

This means that operations must only operate on the relevant element, or any data that can be accessed based on that element. It must modify any state shared between threads, or between elements.

## The parallel algorithms form the c++ standard library
for a comprehensive list refer back to the text or consult [cppreference](https://cppreference.com)

* If the “normal” algorithm allows input/output iterator overload with an execution policy require Forward iterators, instead. This is because Input iterators are single pass; you can only access the current element and any advance made to that iterator invalidates previously stored variables to that iterator, meaning we cannot access previous elements.
The text provides a figure that explains the iterator types c++ offers. So if that needed you can refer to it.

The choice of forward iterators compared to single pass iterators like output/input iterators is important for parallelism, this is because each thread can have a copy of iterators unique to itself without the fear of invalidating the copies of other threads, with this the thread is allowed to operate on an element while backtracking or forward-tracking in any way it chooses to operate on later or further elements.

Input/output iterators return proxy object that changes it’s actual object reference once advanced compared to forward iterators that return actual references to the object it currently represents access to; this is why they are favored for parallelism.

### Examples of using parallel algorithms

Parallel algorithms on a class with internal synchronization should be performed in parallel with `std::execution::parallel_policy`:
```c++
class X {
	mutable std::mutex m;
	int data;
public:
	X(): data(0) {}
	void get_value() const { std::scoped_lock guard(m); return data; }
	void increment()       { std::scoped_lock guard(m); ++data; }
};
void increment_all(std::vector<X>& v){
	std::for_each(std::execution::par, v.begin(), v.end(),
		[](auto& x){ x.increment(); } 
	);
}
```
This is an alternative that can be used with `std::execution::parallel_unsequenced_policy` if the ownership of the whole container to be operated on has been secured beforehand, allowing the algorithm to operate on a data structure with no concern with synchronization:
```c++
class X{
	int data;
public:
	X(): data(0) {}
	void get_value() const { return data; }
	void increment()       { ++data; }
};
class ProtectedX{
	std::mutex m;
	std::vector<X> v;
public:
	void lock(){ m.lock(); }
	void unlock(){ m.unlock(); }
	std::vector<X>& get_vec() { return v; }
};
void increment_all(ProtectedX& data)
{
	std::scoped_lock guard(data);
	auto& v=data.get_vec();
	std::for_each(std::execution::par_unseq, v.begin(), v.end(),
		[](auto& x){ x.increment(); }
	);
}
```
### Counting visits
```c++
#include <vector>
#include <string>
#include <unordered_map>
#include <numeric>

struct log_info{
	std::string page;
	time_t visit_time;
	std::string browser;
	// any other fields
};

extern log_info parse_log_line(std::string const& line);
using visit_map_type std::unordered_map<std::string, unsigned long long>;

visit_map_type count_visits_per_page(
	std::vector<std::string> const& log_lines)
{
	struct combine_visit{
		visit_map_type
		operator() (visit_map_type lhs, vist_map_type rhs) const {
			if(rhs.size()>lhs.size())
				std::swap(lhs, rhs);
			for(auto& const log: rhs)
				lhs[log.first]+=log.second;
			return lhs;
		)
		visit_map_type operator()(log_info lg, visit_map_type map) const{
			++map[lg.page];
			return map;
		}
		visit_map_type operator()(visit_map_type map, log_info lg) const{
			++map[lg.page];
			return map;
		}
		visit_map_type operator()(log_info log1, log_info log2) const {
			visit_map_type map;
			++map[log1.page];
			++map[log2.page];
			return map;
		}
	};
	return std::transform_reduce(
		std::excecution::par, log_lines.begin(), log_lines.end(),
		visit_map_type(), combine_visits(), parse_log_line
		);
}
```
