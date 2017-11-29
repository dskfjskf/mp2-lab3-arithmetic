#include <iostream>
using namespace std;

template <class ValType>
class Stack
{
protected:
	ValType *ps;					//��������� �� ��-�� �����
	int Size;						// M����������� ���������� ��������� � �����
	int top;						// ����� �������� �������� �����
public:
	Stack(int s = 5);							// ����������� 
	~Stack();									// ����������
	void push(const ValType&v);					// ������� ��������
	ValType pop();								// ���������� ��������
	ValType peek() const;						// �������� �������� �������� (��� ��������)
	bool empty() const;							// �������� �� �������
	int GetIndex() const { return top + 1; }	// ��������� ���������� ��������� � �����
	void clears() { top = -1; }					// ������� �����

};

template <class ValType>						// ����������� 
Stack <ValType>::Stack(int s)
{
	Size = s;	
	top = -1;
	ps = new ValType[Size];
}

template <class ValType>						// ����������
Stack<ValType>::~Stack()
{
	delete[]ps;
}

template<class ValType>							// ������� ��������
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

template<class ValType>							// ���������� ��������
ValType Stack<ValType>::pop()
{
	if (top!=-1)
	return ps[top--];
	else throw " ";
}


template<class ValType>							// �������� �������� �������� (��� ��������)
ValType Stack<ValType>::peek() const
{ 
	if (top!=-1)
	return ps[top];
	else throw " ";
}

template<class ValType>							// �������� �� �������
bool Stack<ValType>::empty() const
{
	return top == -1;
}









