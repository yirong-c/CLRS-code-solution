#include "stack_queue.h"
#include "linked_list.h"
#include "stack_by_list__10_2_2.h"
#include "queue_by_list__10_2_3.h"

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

int main_linked_list()
{
	DoublyLinkedListElement<int> *element, *element_b, 
		*element_c, *element_d;
	DoublyLinkedListSentinel<int> list, list_b, list_ret;
	//	DoublyLinkedList<int> list;
	element = list.Search(5);
	list.Insert(1);
	list.Insert(2);
	list.Insert(3);
	list.Insert(4);
	list.Insert(5);
	list.Insert(6);
	list.Insert(7);
	list.Insert(8);
	element = list.Search(5);
	list.Delete(element);
	list.Insert(6);
	element = list.SearchOpt(7);
	element_b = list.SearchOpt(4);

	list_b.Insert(11);
	list_b.Insert(12);
	list_b.Insert(13);
	list_b.Insert(14);
	list_b.Insert(15);
	list_b.Insert(16);
	list_b.Insert(17);
	list_b.Insert(18);
	list_b.Insert(19);
	list_b.Insert(20);
	element_c = list_b.SearchOpt(18);
	element_d = list_b.SearchOpt(13);

	DoublyLinkedListSentinelUnion(element, element_b, element_c, 
		element_d, list_ret);

	SinglyLinkedListElement<int>* singly_element;
	SinglyLinkedListSentinel<int> singly_list;
	singly_element = singly_list.SearchOpt(5);
	singly_element = singly_list.Search(5);
	singly_list.Insert(1);
	singly_list.Insert(2);
	singly_list.Insert(3);
	singly_list.Insert(4);
	singly_list.Insert(5);
	singly_element = singly_list.SearchOpt(5);
	singly_element = singly_list.Search(5);
	singly_list.Insert(6);
	singly_list.Insert(7);
	singly_list.Insert(8);
	singly_list.DeleteLinear(singly_element);
	singly_element = singly_list.SearchOpt(1);
	singly_element = singly_list.Search(1);
	singly_list.DeleteLinear(singly_element);
	singly_list.Insert(6);
	singly_element = singly_list.SearchOpt(6);
	singly_element = singly_list.Search(6);
	singly_list.DeleteLinear(singly_element);

	return 0;
}

int main_10_2_2()
{
	int ret;

	StackImpleBySinglyLinkedList<int> stack_by_list;
	stack_by_list.PushCheck(1);
	stack_by_list.PushCheck(2);
	stack_by_list.PushCheck(3);
	stack_by_list.PushCheck(4);
	stack_by_list.PushCheck(5);
	stack_by_list.PushCheck(6);
	ret = stack_by_list.PopCheck();
	ret = stack_by_list.PopCheck();
	ret = stack_by_list.PopCheck();
	ret = stack_by_list.PopCheck();
	ret = stack_by_list.PopCheck();
	ret = stack_by_list.PopCheck();

	return 0;
}

int main_10_2_3()
{
	int ret;

	QueueImpleBySinglyLinkedList<int> queue_by_list;
	queue_by_list.EnqueueCheck(1);
	queue_by_list.EnqueueCheck(2);
	queue_by_list.EnqueueCheck(3);
	queue_by_list.EnqueueCheck(4);
	queue_by_list.EnqueueCheck(5);
	queue_by_list.EnqueueCheck(6);
	queue_by_list.EnqueueCheck(7);
	queue_by_list.EnqueueCheck(8);
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();
	ret = queue_by_list.DequeueCheck();

	return 0;
}
