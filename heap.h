#ifndef _heap_h_
#define _heap_h_
#include <iostream>
using namespace std;

class Heap
{
private:
	int* front;
	int capacity;
	int m;
public:
	Heap(int m_row,int*steps,int* array, int cap);
	Heap(const Heap&,int*);
	Heap(Heap&&);
	~Heap();
	Heap& operator=(const Heap&);
	Heap& operator=(Heap&&);
	Heap& insert(int,int*);
	Heap& remove(int*);
	int get()const;
	bool is_empty()const;
	Heap& convertTo(int new_m,int*);
	void destroy();
	Heap& unionn(const Heap&,int*);
	friend ostream& operator << (ostream&, const Heap&);
	Heap& change_key(int,int);
};
#endif