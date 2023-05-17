#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class Element
{
	int Data;			//Значение элемента
	Element* pNext;		//Адрес сл. элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
class ForwardList
{
	Element* Head; //Голова - указатель на начальный элемент списка, так же 
	//как в массиве, имя массива содержит адрес 0 элемента, голова списка содержит
	//адрес начального элемента 
public:
	ForwardList()
	{
		Head = nullptr; //Когда список пуст, его голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);	//1) Создаем новый элемент.
		New->pNext = Head;					//2) Включаем новый элемент в список.
		Head = New;							//3) Переносим Голову на новый элемент.

	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		Element* n = Head;
		while (n->pNext != nullptr)
		{
			n = n->pNext;
		}
		n->pNext = new Element(Data);
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		//__________________________________
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//				Removing Elements:
	void pop_front()
	{
		Element* erased = Head; //	1)Запоминаем адрес удаляемого элемента
		Head = Head->pNext;//		2)Исключаем удаляемый элемент из списка
		delete erased;	//			3)Удаляем элемент из памяти
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;

	}
	void erase(int Index)
	{
		if (Index == 0)return pop_front();
		//_________________________________
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}

	//				Methods:
	void print()const
	{

		/* Для того что бы перемещаться по списку нужно 2 вещи:
		* Итератор
		* Цикл
		*/
		Element* Temp = Head;		//Temp - это итератор.
		//Итератор - это указатаель, при помощи которого можно получить доступ к 
		//элементам файла
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //переход на сл. элемент
		}
	}
	//				Operators
	ForwardList& operator=(const ForwardList& other)
	{
		this->Head = other.Head;
		Element* Temp = Head->pNext;
		//for (Temp; Temp != nullptr; Head->pNext)
		//{
		//	push_front()
		//}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		int number = rand() % 100;
		cout << number << tab;
		//list.push_front(number);
		list.push_back(number);
	}
	//list.push_back(123);
	list.print();
	list.insert(3, 4);
	list.print();
	list.erase(4);
	list.print();
	//ForwardList = { 3, 5, 8, 13, 21 };

}