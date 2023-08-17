Реализация метода insertIntoMiddle(int value, int pos) для списка мелкогранулярной блокировкой. Часть кода уже дана по заданию — сама структура списка взята из юнита про мелкогранулярную блокировку и приведена ниже.

struct Node
{
  int value;
  Node* next;
  std::mutex* node_mutex;
};

class FineGrainedQueue
{
  Node* head;
  std::mutex* queue_mutex;
};

Функция вставляет узел с переданным значением value в позицию pos. Чтобы не переусложнять реализацию, предполагается следующее:

- очередь не пустая,
  
- элемент вставляется в середину или конец списка, то есть вставку в начало списка не рассматривается (попробовала рассмотреть),
если pos больше длины списка, то элемент вставляется в конец списка.
