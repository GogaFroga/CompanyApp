#include <iostream>
#include <fstream>
#include "fabric.h"
#include "AVL.h"

using std::string;
using std::cout;
using std::ofstream;

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
	out.open("C:\\Users\\User\\Documents\\GitHub\\CompanyApp\\DB.txt ", std::ios::app);
	Fabric fabric;

	if (out.is_open())
	{
		for (int i = 0; i < 10; i++)
		{
			DeliveryData data = fabric.generateRandom();
			cout << data;
			out << data;
		}
		cout << "\nFile: Succeed\n";
	}
	else
		cout << "\nFile Error: File is not opened\n";

	

	int a[7] = { -3, 1, -5, 42, 2, -6, 8 };
	node* root = new node(0);

	for (int i = 0; i < 7; i++) {
		insert(root, a[i]);
	}
	print_nodes(root);

	out.close();
}
