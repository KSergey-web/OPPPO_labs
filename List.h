#pragma once
#include"EncryptedText.h"
#include <functional>

template<typename T>
class List
{
private:
	template<typename T1>
	class Node
	{
	public:
		T1 data;
		int ind;
		Node<T1>* next = NULL;
		Node<T1>* prev = NULL;
	};
	Node<T>* _top = NULL;
	Node<T>* _end = NULL;
	Node<T>* _current_pos = NULL;
	int _size = 0;
	Node<T>* at(int ind);
	void swap(Node<T>* ptr1, Node<T>* ptr2);
	void deletenode(Node<T>* ptr1){
		Node<T>* prevptr1 = ptr1->prev;
		Node<T>* nextptr1 = ptr1->next;
		if (prevptr1 == NULL) {
			_top = ptr1->next;
		}
		else {
			prevptr1->next = nextptr1;
		}
		if (nextptr1 == NULL) {
			_end = ptr1->prev;
		}
		else {
			nextptr1->prev = prevptr1;
		}
		if (_current_pos == ptr1) {
			if (ptr1->next != NULL)
				_current_pos = ptr1->next;
			else
				_current_pos = ptr1->prev;
		}
		delete ptr1;
		--_size;
	};
	void deletenodeforT(Node<T>* ptr1) {
		delete ptr1->data;
		deletenode(ptr1);
	};
public:
	~List() {
		deletealldata();
		while (_top != NULL) {
			_current_pos = _top;
			_top = _top->next;
			delete _current_pos;
		}
	};
	T& operator[](int ind);
	T& last();
	int getsize() const ;
	void display();
	void deletealldata();
	void push_back(T data);
	friend ostream& operator<< (ostream& out, List<T>& list) {
		out << "[\n";
		for (int i = 0; i < list.getsize(); ++i) {
			out << list[i] << ",\n";
		}
		out << "]";
		return out;
	};
	void remove(function<bool(T)> ptrfcn);
	void sort(function<bool(T,T)> ptrfcn);
};


template<typename T>
T& List<T>::operator[](int ind) {
	return at(ind)->data;
}

template<typename T>
inline T& List<T>::last()
{
	return _end->data;
}

template<typename T>
int List<T>::getsize() const {
	return _size;
}

template<typename T>
void List<T>::display() {
	cout << "Container :" << endl;
	for (int i = 0; i < _size; ++i) {
		cout << " number:" << i << "| " << (*this)[i] << endl;
	}
}

template<typename T>
void List<T>::deletealldata() {
	Node<T>* ptr = _top;
	while (ptr != NULL) {
		_current_pos = ptr;
		ptr = ptr->next;
		if (_current_pos->data != NULL) {
			delete _current_pos->data;
			_current_pos->data = NULL;
		}
	}
}

template<typename T>
void List<T>::push_back(T data) {
	Node<T>* ptr = new Node<T>();
	ptr->data = data;
	if (_size == 0) {
		_top = ptr;
		_top->ind = _size++;
		_end = ptr;
		_current_pos = _top;
	}
	else {
		_end->next = ptr;
		ptr->prev = _end;
		ptr->ind = _size++;
		_end = _end->next;
	}
}


template<typename T>
void List<T>::sort(function<bool(T, T)> ptrfcn)
{
	for (int startIndex = 0; startIndex < _size; ++startIndex)
	{
		int bestIndex = startIndex;
		for (int currentIndex = startIndex + 1; currentIndex < _size; ++currentIndex)
		{
			if (ptrfcn((*this)[bestIndex], (*this)[currentIndex])) 
				bestIndex = currentIndex;
		}
		swap(at(startIndex), at(bestIndex));
	}
}

template<typename T>
List<T>::Node<T>* List<T>::at(int ind) {
	if ( (ind < 0) || (ind >= _size) ) {
		throw(string("index is out of range"));
	}
	int distancetop = ind;
	int distanceend = _end->ind - ind;
	int distancecurrent = _current_pos->ind - ind;
	distancecurrent = (int)sqrt(distancecurrent * distancecurrent);
	if (distancetop < distanceend && distancetop < distancecurrent) {
		_current_pos = _top;
	}
	else if (distancetop > distanceend && distanceend < distancecurrent) {
		_current_pos = _end;
	}
	for (int i = _current_pos->ind; i < _size; i = _current_pos->ind) {
		if (i == ind) {
			return _current_pos;
		}
		_current_pos->ind < ind ? _current_pos = _current_pos->next : _current_pos = _current_pos->prev;
	}
	return NULL;
}

template<typename T>
void List<T>::swap(Node<T>* ptr1, Node<T>* ptr2) {
	Node<T>* prevptr1 = ptr1->prev;
	Node<T>* nextptr1 = ptr1->next;
	Node<T>* prevptr2 = ptr2->prev;
	Node<T>* nextptr2 = ptr2->next;
	if (prevptr1 == NULL) {
		_top = ptr2;
	}
	else {
		if (prevptr1 == ptr2)
			ptr1->next = ptr2;
		else
			prevptr1->next = ptr2;
	}
	if (prevptr2 == NULL) {
		_top = ptr1;
	}
	else {
		if (prevptr2 == ptr1)
			ptr2->next = ptr1;
		else
			prevptr2->next = ptr1;
	}
	if (nextptr1 == NULL) {
		_end = ptr2;
	}
	else {
		if (nextptr1 == ptr2)
			ptr1->prev = ptr2;
		else
			nextptr1->prev = ptr2;
	}
	if (nextptr2 == NULL) {
		_end = ptr1;
	}
	else {
		if (nextptr2 == ptr1)
			ptr2->prev = ptr1;
		else
			nextptr2->prev = ptr1;
	}
	int buf;
	buf = ptr1->ind;
	ptr1->ind = ptr2->ind;
	ptr2->ind = buf;
	if (prevptr1 != ptr2)
	ptr2->prev = prevptr1;
	if (nextptr1 != ptr2)
	ptr2->next = nextptr1;
	if (prevptr2 != ptr1)
	ptr1->prev = prevptr2;
	if (nextptr2 != ptr1)
	ptr1->next = nextptr2;
}


template<typename T>
void List<T>::remove(function<bool(T)> ptrfcn) {
	int decline = 0;
	int size = _size;
	int bufsize = _size;
	for (int i = 0, ind = 0; i < size; ++i) {
		_size = size;
		Node<T>* ptr = at(i);
		if (ptrfcn(ptr->data)) {
			_size = bufsize;
			deletenodeforT(ptr);
			bufsize = _size;
			++decline;
		}
		else {
			ptr->ind -= decline;
		}
	}
	_size = bufsize;
}


/*template<>
void List<EncryptedText*>::deletenodeforT(Node<EncryptedText*>* ptr1) {
	delete ptr1->data;
	deletenode(ptr1);
}*/

/*template<>
List<EncryptedText*>::~List() {
	deletealldata();
	while (_top != NULL) {
		_current_pos = _top;
		_top = _top->next;
		delete _current_pos;
	}
}*/