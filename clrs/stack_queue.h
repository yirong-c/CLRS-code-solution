#include "stdafx.h"

//suggest let T be basic data type
template <class T>
class Stack
{
	T* stack_;
	int size_;
	int top_;

public:
	Stack(int size)
	{
		size_ = size;
		stack_ = new T[size];
		top_ = -1;
	}

	~Stack()
	{
		delete[] stack_;
	}

	bool StackEmpty()
	{
		if (top_ == -1)
			return true;
		else
			return false;
	}

	bool StackFull()
	{
		if (top_ == size_ - 1)
			return true;
		else
			return false;
	}

	//do NOT check overflow
	void Push(T element)
	{
		stack_[++top_] = element;
	}

	//do NOT check underflow
	T Pop()
	{
		--top_;
		return stack_[top_ + 1];
	}

	//check overflow
	void PushCheck(T element)
	{
		if (StackFull())
			throw "overflow";
		else
			Push(element);
	}

	//check underflow
	T PopCheck()
	{
		if (StackEmpty())
			throw "underflow";
		else
			return Pop();
	}
};

/*
10.1-2
*/
template <class T>
class TwoStack
{
	T* stack_;
	int size_;
	int a_top_;
	int b_top_;

public:
	TwoStack(int size)
	{
		size_ = size;
		stack_ = new T[size];
		a_top_ = -1;
		b_top_ = size;
	}

	~TwoStack()
	{
		delete[] stack_;
	}

	bool AStackEmpty()
	{
		if (a_top_ == -1)
			return true;
		else
			return false;
	}

	bool BStackEmpty()
	{
		if (b_top_ == size_)
			return true;
		else
			return false;
	}

	//do NOT check overflow
	void APush(T element)
	{
		stack_[++a_top_] = element;
	}

	//do NOT check underflow
	T APop()
	{
		--a_top_;
		return stack_[a_top_ + 1];
	}

	//do NOT check overflow
	void BPush(T element)
	{
		stack_[--b_top_] = element;
	}

	//do NOT check underflow
	T BPop()
	{
		++b_top_;
		return stack_[b_top_ - 1];
	}
};

//suggest let T be basic data type
template <class T>
class Queue
{
protected:
	T* queue_;
	int size_;//size of allocate memory; actual queue size = size_ - 1
	int tail_;
	int head_;

public:
	Queue(int size)
	{
		size_ = size + 1;
		queue_ = new T[size_];
		head_ = 0;
		tail_ = 0;
	}

	~Queue()
	{
		delete[] queue_;
	}
	
	//do NOT check overflow
	void Enqueue(T element)
	{
		queue_[tail_] = element;
		if (tail_ == size_ - 1)
			tail_ = 0;
		else
			++tail_;
	}

	//do NOT check underflow
	T Dequeue()
	{
		T& element = queue_[head_];
		if (head_ == size_ - 1)
			head_ = 0;
		else
			++head_;
		return element;
	}

	/*
	10.1-4
	*/
	bool QueueEmpty()
	{
		if (tail_ == head_)
			return true;
		else
			return false;
	}

	/*
	10.1-4
	*/
	bool QueueFull()
	{
		if (tail_ + 1 == head_ || 
			(tail_ == size_ - 1 && head_ == 0))
			return true;
		else
			return false;
	}

	/*
	check overflow
	10.1-4
	*/
	void EnqueueCheck(T element)
	{
		if (QueueFull())
			throw "overflow";
		else
			Enqueue(element);
	}

	/*
	check underflow
	10.1-4
	*/
	T DequeueCheck()
	{
		if (QueueEmpty())
			throw "underflow";
		return Dequeue();
	}
};

/*
double-ended queue
10.1-5
*/
template <class T>
class Deque : public Queue<T>
{
	using Queue<T>::queue_;
	using Queue<T>::size_;
	using Queue<T>::tail_;
	using Queue<T>::head_;
	using Queue<T>::QueueFull;
	using Queue<T>::QueueEmpty;

public:
	Deque(int size) : Queue<T>(size) {}
	//do NOT check overflow
	void EnqueueTailEnd(T element)
	{
		if (head_ == 0)
			head_ = size_ - 1;
		else
			--head_;
		queue_[head_] = element;
	}

	//do NOT check underflow
	T DequeueTailEnd()
	{
		if (tail_ == 0)
			tail_ = size_ - 1;
		else
			--tail_;
		return queue_[tail_];
	}

	/*
	check overflow
	*/
	void EnqueueTailEndCheck(T element)
	{
		if (QueueFull())
			throw "overflow";
		else
			EnqueueTailEnd(element);
	}

	/*
	check underflow
	*/
	T DequeueTailEndCheck()
	{
		if (QueueEmpty())
			throw "underflow";
		return DequeueTailEnd();
	}
};

/*
10.1-6
*/
template <class T>
class QueueImpleByTwoStacks
{
	Stack<T> stack_a_;
	Stack<T> stack_b_;

public:
	QueueImpleByTwoStacks(int size) : stack_a_(size), stack_b_(size) {}
	
	/*
	check overflow
	O(1)
	*/
	void EnqueueCheck(T element)
	{
		stack_a_.PushCheck(element);
	}

	/*
	check underflow
	stack_b is NOT empty: O(1)
	stack_b is empty: O(n)
	*/
	T DequeueCheck()
	{
		if (stack_b_.StackEmpty())
		{
			while (!stack_a_.StackEmpty())
			{
				stack_b_.PushCheck(stack_a_.Pop());
			}
		}
		return stack_b_.PopCheck();
	}
};

/*
10.1-7
*/
template <class T>
class StackImpleByTwoQueues
{
	Queue<T> queue_a_;
	Queue<T> queue_b_;
	bool current_a_;

public:
	StackImpleByTwoQueues(int size) : queue_a_(size), queue_b_(size)
	{
		current_a_ = true;
	}

	/*
	check overflow
	O(1)
	*/
	void PushCheck(T element)
	{
		Queue<T>& queue = current_a_ ? queue_a_ : queue_b_;
		queue.EnqueueCheck(element);
	}

	/*
	check underflow
	O(n)
	*/
	T PopCheck()
	{
		T element;
		Queue<T>& queue = current_a_ ? queue_a_ : queue_b_;
		Queue<T>& queue_dst = current_a_ ? queue_b_ : queue_a_;
		current_a_ = !current_a_;
		element = queue.DequeueCheck();
		while (!queue.QueueEmpty())
		{
			queue_dst.Enqueue(element);
			element = queue.Dequeue();
		}
		return element;
	}
};

int main_stack_queue()
{
	int ret;

	StackImpleByTwoQueues<int> stack_by_queues(6);
	stack_by_queues.PushCheck(1);
	stack_by_queues.PushCheck(2);
	stack_by_queues.PushCheck(3);
	stack_by_queues.PushCheck(4);
	stack_by_queues.PushCheck(5);
	stack_by_queues.PushCheck(6);
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	stack_by_queues.PushCheck(7);
	stack_by_queues.PushCheck(8);
	stack_by_queues.PushCheck(9);
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();
	ret = stack_by_queues.PopCheck();

	QueueImpleByTwoStacks<int> queue_by_stacks(6);
	queue_by_stacks.EnqueueCheck(1);
	queue_by_stacks.EnqueueCheck(2);
	queue_by_stacks.EnqueueCheck(3);
	queue_by_stacks.EnqueueCheck(4);
	queue_by_stacks.EnqueueCheck(5);
	queue_by_stacks.EnqueueCheck(6);
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();
	queue_by_stacks.EnqueueCheck(7);
	queue_by_stacks.EnqueueCheck(8);
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();
	ret = queue_by_stacks.DequeueCheck();

	Deque<int> deque(10);
	deque.EnqueueCheck(4);
	deque.EnqueueCheck(1);
	deque.EnqueueCheck(3);
	deque.EnqueueTailEndCheck(4);
	deque.EnqueueTailEndCheck(1);
	deque.EnqueueTailEndCheck(3);
	ret = deque.DequeueCheck();
	ret = deque.DequeueTailEndCheck();
	ret = deque.DequeueCheck();
	ret = deque.DequeueTailEndCheck();

	Queue<int> queue(6);
	queue.EnqueueCheck(4);
	queue.EnqueueCheck(1);
	queue.EnqueueCheck(3);
	ret = queue.DequeueCheck();
	queue.EnqueueCheck(8);
	ret = queue.DequeueCheck();

	/*
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	ret = queue.DequeueCheck();
	queue.EnqueueCheck(4);
	queue.EnqueueCheck(1);
	queue.EnqueueCheck(3);
	queue.EnqueueCheck(4);
	queue.EnqueueCheck(1);
	queue.EnqueueCheck(3);
	*/

	TwoStack<int> two_stack(6);
	two_stack.APush(6);
	two_stack.BPush(4);
	two_stack.APush(3);
	ret = two_stack.BPop();
	two_stack.BPush(8);
	ret = two_stack.APop();

	Stack<int> stack(6);
	stack.Push(4);
	stack.Push(1);
	stack.Push(3);
	ret = stack.PopCheck();
	stack.Push(8);
	ret = stack.PopCheck();

	return 0;
}

