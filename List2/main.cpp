#include<iostream>
using namespace std;
#define tab "\t"
#define delimiter "\n-----------------------------\n"

class List
{
	class Element
	{
		int Data;			//«начение элемента
		Element* pNext;		//”казатель на следующий элемента
		Element* pPrev;		//”казатель на предыдущий элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) 
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;			//ќбьекты и указатели на обьекты можно обь€вл€ть сразу же после описани€ класса.
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//		
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}
	void pop_front()
	{
		Head = Head->pNext;
		delete Head->pPrev;
		size--;
	}
	void pop_back()
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//			Methods;
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp -> pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "количество элементов списка: " << size << endl;
	}
	void reverse_print()const // ƒурак думал пол часа, а надо было просто в print помен€ть 2 слова........... XD
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "количество элементов списка: " << size << endl;
	}

};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.push_back(555);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	list.reverse_print(); // ѕќѕ–ќ—»“№ ЌјѕќћЌ»“№  ј  –јЅќ“ј“№ ¬ ќ“Ћјƒ„» ≈... 
}