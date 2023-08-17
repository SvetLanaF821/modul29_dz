#pragma once

#include <mutex>

struct Node {
	int value;							//значение узла
	Node* next;							//указатель на следующий узел
	std::mutex node_mutex;				//мьютекс		

public:
	Node() = default;
	Node(int val) : value(val), next(nullptr), node_mutex() {}
	~Node() = default;
};

class FineGrainedQueue {
	std::mutex _queue_mutex;

public:
	Node* head;
	FineGrainedQueue();
	~FineGrainedQueue();

	//вставка в середину
	void insertIntoMiddle(const int value, const int pos);
	//показать очередь
	void showQueue();
};