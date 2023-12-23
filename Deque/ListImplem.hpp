#include "list.hpp"

template<class T>
List<T>::List(){};

template<class T>
List<T>::List(const List<T> &other)
{
	Item *tmp = other.first;
	while(tmp){
		push_back(tmp->data);
		tmp = tmp->next;
	}
}

template<class T>
bool List<T>::isEmpty() const
{
	return first == NULL;
}

template<class T>
void List<T>::operator=(const List<T> &other)
{
	clear();
	Item *tmp = other.first;
	while(tmp){
		push_back(tmp->data);
		tmp = tmp->next;
	}
}

template <class T>
List<T>::~List()
{
	clear();
}

template <class T>
void List<T>::push_front(const T &val)
{
	Item *tmp = new Item;
	tmp->data = val;
	tmp->next = first;
	tmp->prev = NULL;
	if(first)
		first->prev = tmp;
	else
		last = tmp;
	first = tmp;
}

template <class T>
T List<T>::pop_front()
{
	if(!first)
		throw "Cannot pop_front empty list";
	Item *tmp = first;
	T val = tmp->data;
	first = tmp->next;
	if(first)
		first->prev = NULL;
	else
		last = first;
	delete tmp;
	return val;
}

template <class T>
void List<T>::push_back(const T &val)
{
	Item *tmp = new Item;
	tmp->data = val;
	tmp->prev = last;
	tmp->next = NULL;
	if(last)
		last->next = tmp;
	else
		first = tmp;
	last = tmp;
}

template <class T>
T List<T>::pop_back()
{
	if(!last)
		throw "Cannot pop_front empty list";
	Item *tmp = last;
	T val = tmp->data;
	last = tmp->prev;
	if(last)
		last->next = NULL;
	else
		first = last;
	delete tmp;
	return val;
}

template <class T>
void List<T>::clear()
{
	while(first){
		Item *tmp = first;
		first = first->next;
		delete tmp;
	}
	first = last = NULL;
}

template<class T>
std::ostream &operator<<(std::ostream &out, const List<T> &other)
{
	auto tmp = other.first;
	while(tmp){
		out << tmp->data << ' ';
		tmp = tmp->next;
	}
	out << '\n';
	return out;
}


