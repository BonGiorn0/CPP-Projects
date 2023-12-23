#include <stdio.h>

class Item{
public:
	int data;
	class Item *next, *prev;
};

class Deque{
	Item *first, *last;
public:
	Deque(){first = NULL; last = NULL;};
	~Deque(){
		while(first){
			Item *tmp = first;
			first = first->next;
			delete tmp;
		}
	};
	void push_front(int val){
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
	int pop_front(){
		if(!first)
			return 0;
		Item *tmp = first;
		int val = tmp->data;
		first = tmp->next;
		if(first)
			first->prev = NULL;
		else
			last = first;
		delete tmp;
		return val;
	}
	void push_back(int val)
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
	int pop_back(){
		if(!last)
			return 0;
		Item *tmp = last;
		int val = tmp->data;
		last = tmp->prev;
		if(last)
			last->next = NULL;
		else
			first = last;
		delete tmp;
		return val;
	}
	void print() const{
		while(first){
			printf("%d ", first->data);
			first = first->next;
		}
		printf("\n");
	}
	
};

int main()
{
	Deque dq;
	dq.push_front(6);
	dq.print();
	dq.push_front(8);
	dq.print();
	dq.push_front(11);
	dq.print();
	dq.push_back(12);
	dq.print();
	dq.push_back(15);
	dq.print();
	dq.pop_front();
	dq.print();
	dq.pop_front();
	dq.print();
	dq.pop_front();
	dq.print();
}

