#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cmath>
#include "heap.h"
using namespace std ::chrono;

int* manuel_array(int k)
{
	int x;
	bool flag = false;
	int* array = new int[k];
	for (int i = 0;i < k;i++)
	{
		cout << "Unesite element niza: ";
		cin >> x;
		for (int j = 0;j < i;j++)
		{
			if (x == array[j])
			{
				i--;
				flag = true;
			}
		}
		if (flag)
		{
			cout << "Ponovljena vrednost kljuca;ponovo unesite element" << endl;
			flag = false;
		}
		else
			array[i] = x;
	}
	return array;
}

int* random(int k)
{
	int low, high;
	cout << "Unesite donju granicu niza: ";
	cin >> low;
	cout << "Unesite gornju granicu niza: ";
	cin >> high;
	int* array = new int[k];
	for (int i = 0;i < k;i++)
	{
		bool flag = true;
		int x = low + rand() % ((high + 1) - low);
		for (int j = 0;j < i;j++)
		{
			if (x == array[j])
			{
				i--;
				flag = false;
			}
		}
		if (flag) array[i] = x;
	}
	return array;
}

int* read_from_file(int k,string file)
{
	int* array = new int[k];
	int i = 0;
	cout << endl;
	ifstream File;
	File.open(file);
	while (!File.eof())
	{
		File >> array[i];
		i++;
	}
	File.close();
	return array;
}

int main(int argc,char** argv)
{
	int x, m, k,steps=1;
	cout << "Unesite red hipa i broj elemenata: ";
	cin >> m >> k;
	cout << endl;
	cout << "1. Rucni unos elemenata" << endl;
	cout << "2. Unos elemenata iz datoteke" << endl;
	cout << "3. Stvaranje slucajnih vrednosti za unos" << endl;
	cout << "4. Unos elemenata iz komandne linije" << endl;
	cout << "5. Prazan hip" << endl << endl;
	cout << "Izaberite jednu opciju: ";
	cin >> x;

	int* array=nullptr;
	switch (x)
	{
	case 1:
	{
		array = manuel_array(k);
		break;
	}
	case 2:
	{
		string file;
		cout << "Unesite ime datoteke: ";
		cin >> file;
		cout<<endl << "10, 100, 1 000, 10 000, 100 000 ? : ";
		cin >> k;
		array = read_from_file(k,file);
		break;
	}
	case 3:
	{
		array = random(k);
		break;
	}
	case 4:
	{
		if (argc <= 1) cout << "Nema parametara";
		array = new int[argc - 1];
		for (int i = 0;i < argc - 1;i++)
		{
			array[i] = atoi(argv[1 + i]);
		}
		k = argc - 1;
		break;
	}
	case 5:
	{
		array = nullptr;
		break;
	}
	}
	
	Heap* heap = new Heap(m, &steps, array, k);

	cout << "1. Dodavanje novog elementa" << endl;
	cout << "2. Brisanje minimalnog elementa" << endl;
	cout << "3. Dohvatanje minimalnog elementa" << endl;
	cout << "4. Proveri da li je hip prazan" << endl;
	cout << "5. Pretvaranje hipa u hip zadatog reda" << endl;
	cout << "6. Dodavanje jednog hipa drugom" << endl;
	cout << "7. Ispis hipa u obliku m-arnog stabla" << endl;
	cout << "8. Brisanje hipa" << endl;
	cout << "9. Promena vrednosti proizvoljnom kljucu" << endl;
	cout << "10. Merenje performansi" << endl;
	cout << "11. Prekid programa" << endl << endl;

	int option;
	while (true)
	{
		cout<<endl << "Izabreite jednu od ponudjenih opcija: ";
		cin >> option;
		cout << endl;
		if (option == 1)
		{
			int elem;
			cout << "Unesite vrednost novog elementa: ";
			cin >> elem;
			heap->insert(elem, &steps);
		}
		else if (option == 2)
		{
			heap->remove(&steps);
		}
		else if (option == 3)
		{
			cout << "Minimalni element na hipu je: " << heap->get()<<endl;
		}
		else if (option == 4)
		{
			if (heap->is_empty()) cout << "Hip nije prazan" << endl;
		}
		else if (option == 5)
		{
			int new_m;
			cout << "Unesite novi red hipa: ";
			cin >> new_m;
			heap->convertTo(new_m, &steps);
		}
		else if (option == 6)
		{
			int m2, k2,*array2,steps2;
			cout << "Unesite red i broj elemenata drugog hipa: ";
			cin >> m2 >> k2;
			array2 = manuel_array(k2);
			Heap* heap2 = new Heap(m2, &steps2, array2, k2);
			heap->unionn(*heap2, &steps2);
		}
		else if (option == 7)
		{
			cout << *(heap) << endl << endl;
		}
		else if (option == 8)
		{
			heap->destroy();
		}
		else if (option == 9)
		{
			int key1, key2;
			cout << "Unesite kljuc koji zelite da zamenite i zamenu: ";
			cin >> key1 >> key2;
			heap->change_key(key1, key2);
		}
		else if (option == 10)
		{
			cout << "Data number and m_row" << '\t';
			cout << "Insert time" << '\t';
			cout << "Insert steps" << '\t';
			cout << "Remove time" << '\t';
			cout << "Remove steps" <<endl;
			int steps_add = 1, steps_remove = 1, steps_remove_sum = 0,*data,m=2,k=10;
			string file1="test_100.txt", file2="test_1000.txt", file3="test_10000.txt", file4="test_100000.txt";
			string file;
			for (int i = 2;i < 6;i++)
			{
				for (int s = 0;s < 3;s++)
				{
					if (i - 1 == 1) file = file1;
					else if (i - 1 == 2) file = file2;
					else if (i - 1 == 3) file = file3;
					else file = file4;
					data = read_from_file(pow(k, i),file);
					auto start_add = high_resolution_clock::now();
					Heap* heap1 = new Heap(m, &steps_add, data, pow(k, i));
					auto end_add = high_resolution_clock::now();
					duration<double, std::milli>time_add = end_add - start_add;
					auto start_remove = high_resolution_clock::now();
					for (int j = 0;j < pow(k, i);j++)
					{
						heap1->remove(&steps_remove);
						steps_remove_sum += steps_remove;
						steps_remove = 0;
					}
					auto end_remove = high_resolution_clock::now();
					duration<double, std::milli>time_remove = end_remove - start_remove;
					cout <<pow(k,i)<< ","<<m<<'\t'<<'\t' << '\t';
					cout <<time_add.count()<<"ms "<< '\t';
					cout <<steps_add<< '\t' << '\t';
					cout <<time_remove.count()<<"ms "<< '\t' << '\t';
					cout <<steps_remove_sum<< endl;
					m = m * 2;
				    steps_add = 1, steps_remove = 1, steps_remove_sum = 0;
					delete heap1;
				}
				m = 2;
			}
		}
		else if (option == 11)
		{
			break;
		}
	}
	
	return 0;
}