#include<iostream>
#include<time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"

class Element
{
	int Data;			//Значение элемента
	Element* pNext;		//Адрес сл. элемента
	static int count;	//Счетчик элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;

#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
	friend class ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0; // статическую переменную можно проинитиализировать только 
// за переделами класса.
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
};
class ForwardList
{
	Element* Head; //Голова - указатель на начальный элемент списка, так же 
	//как в массиве, имя массива содержит адрес 0 элемента, голова списка содержит
	//адрес начального элемента 
	unsigned int size; //Кол-во элементов списка
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr; //Когда список пуст, его голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList&& other) :ForwardList()
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//				Operators

	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssugment:\t" << this << endl;
		return *this;
	}
	//				Adding elements:
	void push_front(int Data)
	{
		//	Element* New = new Element(Data);	//1) Создаем новый элемент.
		//	New->pNext = Head;					//2) Включаем новый элемент в список.
		//	Head = New;							//3) Переносим Голову на новый элемент.
		Head = new Element(Data, Head);
		size++;

	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//Element* New = new Element(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index < size)return;
		//__________________________________
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;

		//3) Вставляем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//				Removing Elements:
	void pop_front()
	{
		Element* erased = Head; //	1)Запоминаем адрес удаляемого элемента
		Head = Head->pNext;//		2)Исключаем удаляемый элемент из списка
		delete erased;	//			3)Удаляем элемент из памяти
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
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
		size--;
	}

	//				Methods:
	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			pop_front();
			size++;
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;

	}
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
		cout << "Кол-во элементов списка: " << size << endl;
		cout << "Общее кол-во элементов списка: " << Head->count << endl;
	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList Buffer = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
	{
		Buffer.push_back(Temp->Data);
	}
	return Buffer;
}
//#define BASE_CHECK
//#define COPY_CHECK
//#define PREFORMANCE_CHACK
//#define RANGE_BASE_FOR_ARRAY
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
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

	list.insert(3, 3);
	list.print();
	//list.erase(4);
	//list.print();
	//ForwardList = { 3, 5, 8, 13, 21 };
#endif
#ifdef PREFORMANCE_CHACK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	cout << "Список созда, идет загрузка данных " << endl;
	clock_t t_start = clock();
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t t_end = clock();
	cout << "Данные загружены за " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	//list.print();
	cout << delimiter << endl;

	cout << "Копируем список: " << endl;
	t_start = clock();
	ForwardList list2 = list;
	t_end = clock();
	cout << "Cписок скопирован за " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	//list2.print();  
#endif // PREFORMANCE_CHACK
#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY

#ifdef ITERATORS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list1)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	ForwardList list1 = { 3, 5, 8, 13, 21 };
	for (int i : list1)cout << i << tab; cout << endl;
	ForwardList list2 = { 39, 55, 98 };
	for (int i : list2)cout << i << tab; cout << endl;
	ForwardList list3 = list1 + list2;
	for (int i : list3)
	{
		cout << i << tab;
	}
	cout << endl;
}