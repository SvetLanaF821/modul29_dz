#include <iostream>
#include <thread>
#include "FineGrainedQueue.h"

FineGrainedQueue::FineGrainedQueue() :head(nullptr), _queue_mutex() {}

FineGrainedQueue::~FineGrainedQueue() {
	Node* node = head;

	while (node) {
		Node* next = node->next;
		delete node;
		node = next;
	}
}

//вставка в середину
void FineGrainedQueue::insertIntoMiddle(const int value, const int pos) {
	// создаем новый узел 
	Node* newNode = new Node(value);
	Node* prev, * cur;
	_queue_mutex.lock();

	if (head == nullptr) {
		std::cout << "Поток " << std::this_thread::get_id() << "\tвставляет: \tзначение - " << value << " \tв позицию - " << pos << "\n";
		// если список пуст, новый узел и будет началом списка
		head = newNode;
		_queue_mutex.unlock();
		return;
	}

	prev = this->head;
	cur = this->head->next;

	prev->node_mutex.lock();

	if (pos == 0) {
		std::cout << "Поток " << std::this_thread::get_id() << "\tвставляет: \tзначение - " << value << " \tв позицию - " << pos << "\n";
		//крайний случай - вставка  в начало списка
		newNode->next = head;
		head = newNode;
		prev->node_mutex.unlock();
		_queue_mutex.unlock();
		return;
	}

	_queue_mutex.unlock();

	if (cur)							//проверили и только потом залочили
		cur->node_mutex.lock();

	int currPos = 0;

	//в цикле идем по списку, пока список не кончится, или пока не дойдем до позиции
	while (currPos < pos - 1 && cur != nullptr) {
		Node* old_prev = prev;
		prev = cur;
		cur = cur->next;
		old_prev->node_mutex.unlock();
		if (cur)						//проверили и только потом залочили
			cur->node_mutex.lock();

		currPos++;
	}

	//меняем указатель на следующий узел на указатель на новый узел
	Node* old_cur = cur;
	cur = newNode;

	newNode->node_mutex.lock();
	std::cout << "Поток " << std::this_thread::get_id() << "\tвставляет: \tзначение - " << value << " \tв позицию - " << pos << "\n";

	//связываем список обратно, меняем указатель на узел, следующий после нового узла, на указатель на узел, следующий за prev
	newNode->next = old_cur;
	if (old_cur)
		old_cur->node_mutex.unlock();
	prev->next = newNode;
	cur->node_mutex.unlock();

	prev->node_mutex.unlock();
}

//показать очередь
void FineGrainedQueue::showQueue()
{
	FineGrainedQueue* curNode = new FineGrainedQueue();
	curNode->head = this->head;
	while (curNode->head)
	{
		std::cout << curNode->head->value << "\t";
		curNode->head = curNode->head->next;
	}
	std::cout << "\n\n";
	delete curNode;
}