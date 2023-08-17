#include <iostream>
#include <mutex>
#include <thread>
#include "FineGrainedQueue.h"

int main()
{
	setlocale(LC_ALL, "");

	//создание узлов
	Node* n1 = new Node(10);
	Node* n2 = new Node(20);
	Node* n3 = new Node(30);
	Node* n4 = new Node(40);

	//связывание узлов в список
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;

	FineGrainedQueue* queue = new FineGrainedQueue();
	queue->head = n1;

	std::cout << "Список до вставки:\n";
	queue->showQueue();

	//вставка значений в разных потоках 
	//std::thread t1([&]() {queue->insertIntoMiddle(11, 0); });
	std::thread t1([&]() {queue->insertIntoMiddle(11, 1); });
	std::thread t2([&]() {queue->insertIntoMiddle(33, 3); });
	std::thread t3([&]() {queue->insertIntoMiddle(99, 9); });

	//ожидание завершения потоков
	if (t1.joinable())t1.join();
	if (t2.joinable())t2.join();
	if (t3.joinable())t3.join();

	std::cout << "\nСписок после вставки:\n";
	queue->showQueue();

	delete queue;				//delete Node-ов a, b, c, d в деструкторе ~FineGrainedQueue()

	return 0;
}