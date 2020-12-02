#include <iostream>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

class MyList {

	int* arr;
private:
	class Node {
	public:
		int el;
		Node* nextPtr;
		Node(int el);
	} *head, * tail;
	int cur_size;

public:
	MyList();
	~MyList();
	void push_back(int el);
	void push_front(int el);
	void pop_front();
	void pop_back();
	//Объявление перегрузки []
	int& operator[](int index);
	void print_all();
	//Сортировка
	void sort(int* arr, int n);
	operator int() const;
};

inline MyList::Node::Node(int el)
{
	this->el = el;
	this->nextPtr = nullptr;
}

inline MyList::MyList()
{
	arr = nullptr;
	head = tail = nullptr;
	cur_size = 0;
}

inline MyList::~MyList()
{
	if (cur_size != 0) {
		Node* cur_ptr = head;
		Node* tmp;
		while (cur_ptr->nextPtr != tail->nextPtr) {
			tmp = cur_ptr->nextPtr;
			delete cur_ptr;
			cur_ptr = tmp;
		}
	}
}

inline void MyList::push_back(int el)
{
	Node* tmp = new Node(el);
	if (cur_size == 0) {
		head = tail = tmp;
	}
	else {
		tail->nextPtr = tmp;
		tail = tmp;
	}
	cur_size++;
}

inline void MyList::push_front(int el)
{
	Node* tmp = new Node(el);
	if (cur_size == 0) {
		head = tail = tmp;
	}
	else {
		tmp->nextPtr = head;
		head = tmp;
	}
	cur_size++;
}

inline void MyList::pop_front()
{
	if (cur_size != 0) {
		Node* tmp = head;
		head = head->nextPtr;
		delete tmp;
		cur_size--;
	}
}


inline void MyList::pop_back()
{
	Node* cur_ptr = head;
	if (cur_size == 0) {
		return;
	}
	else if (cur_size == 1) {
		delete head;
		head = tail = nullptr;
		cur_size = 0;
	}
	else {
		while (cur_ptr->nextPtr != tail) {
			cur_ptr = cur_ptr->nextPtr;
		}
		delete tail;
		tail = cur_ptr;
		cur_size--;

	}
}

//Реализация перегрузки оператора []
int& MyList::operator[](int index)
{
	return arr[index];
}

inline void MyList::print_all()
{
	if (cur_size != 0) {
		Node* cur_ptr = head;

		while (cur_ptr != tail->nextPtr) {
			cout << cur_ptr->el << endl;
			cur_ptr = cur_ptr->nextPtr;
		}
	}
}

//реализация сортировки
void MyList::sort(int* arr, int n)
{
	

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
		{
			
			int tmp = arr[j - 1];

			arr[j - 1] = arr[j];
			arr[j] = tmp;

		}
	}

	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << endl;
	}
}

MyList::operator int() const
{
	return MyList();
}

class myVector
{
	int* arr;
	int cur_size;
	int buf_size;
public:
	myVector();
	myVector(int size);

	void push_back(const int& obj);
	void pop_back();

	
	void insert(const int& obj, int pos); //вставка элементов
	void remove(int begin, int end); // удаление элементов
	int size();
	int& operator[](int index); 
	myVector& operator=(const myVector& obj);
	~myVector();
};

myVector::myVector()
{
	arr = nullptr;
	buf_size = 0;
	cur_size = 0;
}

myVector::myVector(int size)
{
	buf_size = size;
	cur_size = 0;
	arr = new int[buf_size];
}

void myVector::push_back(const int& obj)
{
	if (buf_size == 0 && cur_size == 0)
	{
		buf_size = 6;
		arr = new int[buf_size];
	}
	else if (cur_size >= buf_size)
	{
		buf_size *= 2;
		int* tmp;

		tmp = new int[buf_size];
		for (int i = 0; i < cur_size; i++)
		{
			tmp[i] = arr[i];
		}
		delete[] arr;
		arr = tmp;
	}
	arr[cur_size++] = obj;
}

void myVector::pop_back()
{
	cur_size--;
}

void myVector::insert(const int& obj, int pos)
{
	if (cur_size > 0 && pos <= cur_size)
	{
		if (cur_size >= buf_size)
		{
			buf_size *= 2;
		}
	}

	int* tmp = new int[buf_size];
	for (int i = 0; i < pos; i++)
	{
		tmp[i] = arr[i];
	}

	for (int i = pos; i < cur_size; i++)
	{
		tmp[i + 1] = arr[i];
	}
	tmp[pos] = obj;

	delete[] arr;
	arr = tmp;

	cur_size++;
}

// Реализация функции удаления диапазона
void myVector::remove(int begin, int end)
{
	int* tmp = new int[cur_size];
	int ii = 0;
	for(int i = 0; i < begin; i++)
	{
		tmp[ii++] = arr[i];
	}

	for(int i = end; i < cur_size; i++)
	{
		tmp[ii] = arr[i];
	}
	delete[] arr;
	arr = tmp;
	cur_size = ii;
	buf_size = cur_size;
}


int myVector::size()
{
	return cur_size;
}

int& myVector::operator[](int index)
{
	return arr[index];
}

myVector& myVector::operator=(const myVector& obj)
{
	arr = new int[obj.buf_size];
	buf_size = obj.buf_size;
	cur_size = obj.cur_size;
	for (int i = 0; i < cur_size; i++)
	{
		arr[i] = obj.arr[i];
	}
	return *this;
}

myVector::~myVector()
{
	if (arr != nullptr)
		delete[] arr;

}

int main()
{
	const int n = 10;
	int arr[n] = { 12, 5, 3, 2, 45, 96, 6, 8, 11, 24 };

	cout << "List: " << endl;
	
	MyList l;
	
	l.sort(arr, n);
	
	
	cout << "\n\nVector: " << endl;

	myVector v;
	myVector v1;
	
	for(int i = 0; i < 10; i++)
	{
		v.push_back(i+1);
	}
	v.insert(100, 0);
	v.remove(7, 10);
	
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

