#include<iostream>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

template<typename T>class List
{
	class Element
	{
		T Data;	//значение элемента
		Element* pNext;	//указатель на следующий элемент
		Element* pPrev;	//указатель на предыдущий элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;	//объекты и указатели на объекты можно объявлять сразу же после описания класса.
	size_t size;
	class ConstBaseIterator
	{
		//Generalisation
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp);
		~ConstBaseIterator();

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator();

		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}

		T& operator*();
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin()const;
	ConstIterator end()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;

	//						Constructors:
	List();
	List(int size);
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//				Operators:
	List<T>& operator=(const List<T>& other);

	//				Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);
	void erase(int Index);

	//				Removing elements:
	void pop_front();
	void pop_back();

	//				Methods:
	void print()const;
	void reverse_print()const;
};
///////////////////////////////////////////////////////////////////////////////////
//////////                 Element member function           /////////////////////
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
//////////                 Element member function              ///////////////////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//////////             ConstIterator  member function         /////////////////// 
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//////////             ConstIterator  member function         /////////////////// 
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
//////////          ConstReversIterator  member function      ///////////////////
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//////////////////////////////////////////////////////////////////////////////////
//////////              ReversIterator  member function      ///////////////////
template<typename T> List<T>::Iterator::~Iterator() {}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//////////              ReversIterator  member function      ///////////////////
//////////////////////////////////////////////////////////////////////////////////
 

//////////////////////////////////////////////////////////////////////////////////
//////////                 ConstBaseIterator                 ///////////////////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}

template<typename T> bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	//return !(*this == other);
	return this->Temp != other.Temp;	//так быстрее;-)
}
template<typename T> const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//////////                 ConstBaseIterator                 ///////////////////
///////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////
 //////////					List member function				/////////////

template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>:: rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}

//						Constructors:
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(int size) :List()
{
	while (size--)push_back(int());
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	//begin()
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	//while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//				Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	//1) Удаляем старое значение объекта:
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}

//				Adding elements:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	/*Element* New = new Element(Data);
	New->pNext = Head;
	Head->pPrev = New;
	Head = New;*/
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		/*Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index == 0)return push_front(Data);
	if (Index == size)return push_back(Data);
	if (Index > size)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}
template<typename T>void List<T>::erase(int Index)
{
	if (Index == 0)return pop_front();
	if (Index == size - 1)return pop_back();
	if (Index >= size)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	//1) Исключаем элемент из списка:
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	//2) Удаляем элемент из памяти:
	delete Temp;
	size--;
}

//				Removing elements:
template<typename T>void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size = 0;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

//				Methods:
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}
//////////					List member function				/////////////
////////////////////////////////////////////////////////////////////////////
//#define BASE_CHECK
#define HOME_WORK_1
//#define ITERATORS_PREFORMANCE
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
	/*list.~List();
	list.pop_front();
	list.pop_front();
	list.pop_back();
	list.pop_back();
	list.pop_back();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);

	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_PREFORMANCE
	clock_t t_start, t_end;
	int sum = 0;
	t_start = clock();
	List list(20000000);
	t_end = clock();
	cout << "Список создан за " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
	//List list = { 3, 5, 8, 13, 21 };
	//list.print();
#ifdef HOME_WORK_1
	t_start = clock();
	for (int i : list)
	{
		//cout << i << tab;
		sum += i;
	}
	t_end = clock();
	cout << endl;
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
	cout << delimiter << endl;
	/*List::Iterator begin = list.begin();
	List::Iterator end = list.end();
	for (List::Iterator it = begin; it != end; ++it)*/
	int sum2 = 0;
	t_start = clock();
	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		//cout << *it << tab;
		sum2 += *it;
	}
	t_end = clock();
	cout << endl;
	cout << "Сумма найдена за " << double(t_end - t_start) / CLOCKS_PER_SEC << " секунд\n";
#endif // HOME_WORK

#endif // ITERATORS_PREFORMANCE

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	/*for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{

	}*/
#endif // ITERATORS_CHECK

	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 34,55,89 };
	List<int> list3 = list1 + list2;	//CopyConstructor

	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	for (List<int>::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 10;
	}
	for (int i : list3)cout << i << tab; cout << endl;
	List<double> d_list = { 2.5, 5.3, 3.14, 43.213, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	List<std::string> s_list_1 = { "Куда", "идем", "мы", "с", "Пяточеком" };
	for (std::string i : s_list_1)cout << i << tab; cout << endl;
	List<std::string> s_list_2 = { "большой", "большой", "секрет!" };
	for (std::string i : s_list_2)cout << i << tab; cout << endl;
	List<std::string> s_list_3 = s_list_1 + s_list_2;
	for (std::string i : s_list_3)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list_3.rbegin(); it != s_list_3.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}