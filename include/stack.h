#include <iostream>
using namespace std;

template <class ValType>
class Stack
{
protected:
	ValType *ps;					//Указатель на эл-ты стека
	int Size;						// Mаксимальное количество элементов в стеке
	int top;						// Номер текущего элемента стека
public:
	Stack(int s = 5);							// Конструктор 
	~Stack();									// Деструктор
	void push(const ValType&v);					// Вставка элемента
	ValType pop();								// Извлечение элемента
	ValType peek() const;						// Просмотр верхнего элемента (без удаления)
	bool empty() const;							// Проверка на пустоту
	int GetIndex() const { return top + 1; }	// Получение количества элементов в стеке
	void clears() { top = -1; }					// Очистка стека

};

template <class ValType>						// Конструктор 
Stack <ValType>::Stack(int s)
{
	Size = s;	
	top = -1;
	ps = new ValType[Size];
}

template <class ValType>						// Деструктор
Stack<ValType>::~Stack()
{
	delete[]ps;
}

template<class ValType>							// Вставка элемента
void Stack<ValType>::push(const ValType& v)
{
	if (top == (Size - 1))
	{
		Size *= 2;
		ValType *ps1 = new ValType[Size];
		for (int i = 0; i < (top + 1); i++)
			ps1[i] = ps[i];		
		delete[] ps;
		ps = ps1;
	}
	ps[++top] = v;
}

template<class ValType>							// Извлечение элемента
ValType Stack<ValType>::pop()
{
	if (top!=-1)
	return ps[top--];
	else throw " ";
}


template<class ValType>							// Просмотр верхнего элемента (без удаления)
ValType Stack<ValType>::peek() const
{ 
	if (top!=-1)
	return ps[top];
	else throw " ";
}

template<class ValType>							// Проверка на пустоту
bool Stack<ValType>::empty() const
{
	return top == -1;
}









