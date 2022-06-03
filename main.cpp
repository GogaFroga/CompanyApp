#include <iostream>
#include <fstream>
#include "fabric.h"
#include "AVL.h"

using std::string;
using std::cout;
using std::fstream;
using std::ofstream;
using std::ifstream;

#define amount 100

/*
template <typename N>
class Container
{
public:
	virtual ~Container() = default;
	virtual void push_back(N&) = 0;
	virtual void insert(int, N&) = 0;
	virtual void pop_back() = 0;
	virtual void pop(int) = 0;
	virtual int size_() = 0;
	virtual void clear() = 0;
	virtual N& operator[] (int) = 0;
};

template <typename N>
class DynamicArray : public Container<N>
{
	int size{};
	int capacity = 1;
	N* data_base;
public:
	DynamicArray();
	DynamicArray(const DynamicArray&);
	~DynamicArray();
	N& operator[] (int);
	void insert(int, N&) override;
	void push_back(N&) override;
	void pop_back() override;
	void pop(int i) override;
	void resize(int);
	void clear() override;
	int size_() override;
};

*/



int main()
{
	ofstream out;
	out.open("DB.txt");  // add ", std::ios::app"  n// C:\\Users\\User\\Documents\\GitHub\\CompanyApp
	Fabric fabric;
	AVL avl;
	
	/* генерация */
	if (out.is_open())
	{
		//DeliveryData data = fabric.generateRandom();
		//node* root = new node(0, data); // создаём корневой node
		//avl.insert(0, data);

		for (int i = 0; i < amount; i++)
		{
			DeliveryData data_o = fabric.generateRandom();
			cout << data_o;
			out << data_o;
		}
		cout << "\nFile: Succeed\n";
		out.close();
	}
	else
		cout << "\nFile Error: File is not opened\n";

	/* считывание по частям и работа */
	ifstream in;
	in.open("DB.txt");
	if (in.is_open())
	{
		cout << endl << "TEST:\n";
		for (int i = 0; i < amount/10; i++)
		{
			for (int j = 0; j < amount/10; j++)
			{
				DeliveryData data_i;
				in >> data_i;
				cout << "data\n" << data_i;
				avl.insert(j, data_i);
			}
			// do smth (if found -> clear avl and break)
			// clear avl
		}
		in.close();
	}
	else
		cout << "\nFile Error: File is not opened\n";
}
