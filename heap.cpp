#include "heap.h"

Heap:: Heap(int m_row, int* steps_final, int* array, int cap)
{
	int steps = 0;
	m = m_row;
	capacity = 0;
	if (array == nullptr)
	{
		front = nullptr;
	}
	else
	{
		for (int i = 0;i < cap;i++)
		{
			insert(array[i], &steps);
			(*steps_final) += steps;
			steps = 0;
		}
	}
}

Heap::Heap(const Heap& heap2,int*steps)
{
	capacity = 0;
	m = heap2.m;
	for (int i = 0;i < heap2.capacity;i++) insert(heap2.front[i],steps);
}

Heap::Heap(Heap&& heap2)
{
	m = heap2.m;
	capacity = heap2.capacity;
	front = heap2.front;
	heap2.front = nullptr;
	heap2.capacity = 0;
}

Heap:: ~Heap()
{
	delete[] front;
	front = nullptr;
	capacity = 0;
	m = 0;
}

Heap& Heap:: operator=(const Heap& heap2)
{
	if (this != &heap2)
	{
		int* steps = new int;
		steps = 0;
		this->destroy();
		capacity = 0;
		m = heap2.m;
		for (int i = 0;i < heap2.capacity;i++) insert(heap2.front[i],steps);
	}
	return *this;
}

Heap& Heap:: operator=(Heap&& heap2)
{
	if (this != &heap2)
	{
		this->destroy();
		m = heap2.m;
		capacity = heap2.capacity;
		front = heap2.front;
		heap2.front = nullptr;
		heap2.capacity = 0;
	}
	return *this;
}

Heap& Heap::insert(int node,int*steps)
{
	if (capacity==0)
	{
		capacity = 1;
		front = new int[capacity];
		front[0] = node;
	}
	else
	{
		int* pom = front;
		front = new int[capacity+1];
		for (int i = 0;i < capacity;i++) front[i] = pom[i];
		front[capacity] = node;
		capacity++;
		delete[] pom;

		int index = capacity - 1;
		int father = (index - 1) / m;
		(*steps)++;
		while (index != 0 && front[index] < front[father])
		{
			int tmp = front[index];
			front[index] = front[father];
			front[father] = tmp;
			index = father;
			father = (index - 1) / m;
			(*steps)++;
		}
	}
	return *this;
}

Heap& Heap::remove(int*steps)
{
	*steps = 0;
	if (capacity == 0) cout << "Hip je prazan" << endl;
	else
	{
		front[0] = front[capacity - 1];
		capacity--;
		int min_son_index=1, index = 1, father=0;
		while (true)
		{
			if (index >= capacity) break;
			for (int i = 0;i < m;i++)
			{
				(*steps)++;
				if (index<capacity && front[index] < front[min_son_index]) min_son_index = index;
				index++;
			}
			(*steps)++;
			if (front[father] > front[min_son_index])
			{
				(*steps)++;
				int tmp = front[father];
				front[father] = front[min_son_index];
				front[min_son_index] = tmp;
				father = min_son_index;
				min_son_index = m * father + 1;
				index = min_son_index;
			}
			else break;
		}
	}
	return *this;
}

int Heap::get()const
{
	if (front == nullptr)
	{
		cout << "Hip je prazan" << endl;
		return -1;
	}
	else return (front[0]);
}

bool Heap::is_empty()const
{
	if (this->get() >= 0) return true;
	else return false;
}

void Heap::destroy()
{
	delete[] front;
	front = nullptr;
	capacity = 0;   
}

ostream& operator << (ostream& os, const Heap& heap)
{
	if (heap.front == nullptr)
	{
		cout << "Hip je prazan" << endl;
		return os;
	}
	cout<<"["<<heap.front[0]<<"]"<<endl;
	int index = 1;
	int count = heap.m;
	while (true)
	{
		for (int i = 0;i <count;i++)
		{
			if (index >= heap.capacity) return os;
			cout << heap.front[index]<<' ';
			index++;
			if (i % heap.m == heap.m-1) cout << "->";
			if (i == count - 1) cout<< endl;
		}
		count = count * heap.m;
	}
	return os;
}

Heap& Heap::change_key(int key, int new_key)
{
	bool found = false;
	int index, father, min_son,pom;
	for (int i = 0;i < capacity;i++)
	{
		if (front[i] == key)
		{
			found = true;
			index = i;
			break;
		}
	}
	if (!found)
	{
		cout << "Kjuc ne postoji" << endl;
		return *this;
	}
	front[index] = new_key;
	father = (index - 1) / m;
	min_son = m * index + 1;
	pom = min_son;
	for (int i = 0;i < m;i++)
	{
		if (pom >= capacity) break;
		if (front[pom] < front[min_son]) min_son = pom;
		pom++;
	}
	if (front[index] < front[father])
	{
		while (index != 0 && front[index] < front[father])
		{
			int tmp = front[index];
			front[index] = front[father];
			front[father] = tmp;
			index = father;
			father = (index - 1) / m;
		}
	}
	else if (min_son<capacity && front[index]>front[min_son])
	{
		int tmp = front[index];
		front[index] = front[min_son];
		front[min_son] = tmp;
		father = min_son;
		min_son =m * father + 1;
		index = min_son;
		while (true)
		{
			if (index >= capacity) break;
			for (int i = 0;i < m;i++)
			{
				if (index < capacity && front[index] < front[min_son]) min_son = index;
				index++;	
			}
			if (front[father] > front[min_son])
			{
				tmp = front[father];
				front[father] = front[min_son];
				front[min_son] = tmp;
				father = min_son;
				min_son = m * father + 1;
				index = min_son;
			}
			else break;
		}
	}
	return *this;
}

Heap& Heap:: unionn(const Heap& heap2,int*steps)
{
	int* mask = new int[capacity + heap2.capacity];
	int len = capacity + heap2.capacity;
	for (int i = 0;i < capacity;i++) mask[i] = front[i];
	for (int i = capacity,j=0;i < len;i++,j++) mask[i] = heap2.front[j];
	*this = Heap(m,steps,mask, len);
	return *this;
}

Heap& Heap::convertTo(int new_m,int*steps)
{
	Heap* heap = new Heap(*this,steps);
	*this = Heap(new_m,steps,heap->front, heap->capacity);
	delete heap;
	return *this;
}