#include <iostream>

template<class T>
class List{
public:
	List();
	List(const List<T> &);
	~List();
	
	bool isEmpty() const;
	void push_front(const T &val);
	T pop_front();
	void push_back(const T &val);
	T pop_back();
	void clear();

	void operator=(const List<T> &other);

	template<class U>
	friend std::ostream 
	&operator<<(std::ostream &out, 
				const List<U> &other);
private:
	struct Item{
		T data;
		class Item *next, *prev;
	};
	Item *first = NULL, *last = NULL;
};