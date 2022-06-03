#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "data.h"

using std::cout;


struct node	// ��������� ��� ������������� ����� ������
{
	int key;				// ���� ����
	unsigned char height;	// ������ ��������� � ������ � ������ ���� -1 0 1
	node* left;				// ��������� �� ����� ���������
	node* right;			// ��������� �� ������ ���������
	DeliveryData data;		// ������� !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	node(int k, DeliveryData d) { key = k; data = d;  left = right = 0; height = 1; }
	// node(int k) { key = k; left = right = 0; height = 1; }
};

void print_nodes(node* cur_elem)
{
	if (cur_elem->left != NULL) {
		print_nodes(cur_elem->left);
	}
	cout << "Value = " << cur_elem->key << std::endl;
	if (cur_elem->right != NULL) {
		print_nodes(cur_elem->right);
	}
}

class BaseCollection	// ����������� ����� ������� ���������
{
public:
	//	virtual void insert(BaseIterator &it, Ticket &) = 0;
	//	virtual void erase(size_t) = 0;
	virtual bool empty() = 0;
	virtual void clear() = 0;
	virtual void insert(int, DeliveryData&) = 0;
	virtual void remove(int key) = 0;
	virtual DeliveryData operator[](int) = 0;
	virtual ~BaseCollection() = default;
};

// ��� AVL � ��� (�������� clear)
class AVL : public BaseCollection	// AVL-�����, ������� �� ��������� �� ������ ������� ���������
{
	public:
		int height();
		void insert(int key, DeliveryData& data) override;
		void remove(int key) override;
		bool empty() override;
		virtual void clear() {}; //�������� �� ���� while(!empty) remove(root)!!!!!!!!!!!
		DeliveryData operator[](int);
		AVL();
		node* root;  // root �������� �� PUBLIC!!!!!!!!!!!


	private:
		int bfactor(node*);
		void fixheight(node* p);
		DeliveryData find(node*, int);
		node* rotateright(node* p);
		node* rotateleft(node* q);
		node* balance(node* p);
		node* gavno_insert(node* p, int k, DeliveryData&);
		node* gavno_remove(node* p, int k);
		node* findmin(node* p);
		node* removemin(node* p);
};

int AVL::height()
{
	return root ? root->height : 0;
}

int AVL::bfactor(node* p)
{
	if (p->left != nullptr && p->right != nullptr)
		return (p->right)->height - (p->left)->height;
}

void AVL::fixheight(node* p)
{
	int hr = 0, hl = 0;
	if (p->right != nullptr)
		hr = (p->right)->height;
	if (p->left != nullptr)
		hl = (p->left)->height;
	p->height = (hl > hr ? hl : hr) + 1;
}

node* AVL::rotateright(node* p) // ������ ������� ������ p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* AVL::rotateleft(node* q) // ����� ������� ������ q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* AVL::balance(node* p)  // �� �����?
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}

node* AVL::findmin(node* p) // ����� ���� � ����������� ������ � ������ p 
{
	return p->left ? findmin(p->left) : p;
}

node* AVL::removemin(node* p)  // �������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}


// edit this below
// 
// my old insert edited:
node* AVL::gavno_insert(node* p, int k, DeliveryData& data)  // ������� ����� k � ������ � ������ p
{
	if (!p) return new node(k, data);
	if (k < p->key)
		p->left = gavno_insert(p->left, k, data);
	else
		p->right = gavno_insert(p->right, k, data);
	return balance(p);
}

/* OLD
node* insert(node* p, int k)
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}
*/

void AVL::insert(int key, DeliveryData& data)
{
	if (root == nullptr)
		root = gavno_insert(root, key, data);
	else
		gavno_insert(root, key, data);
}

void AVL::remove(int key)
{
	if (key == root->key and !root->left and !root->right)
	{
		delete root;
		root = nullptr;
	}
	else
		gavno_remove(root, key);
}

// my old remove:
node* AVL::gavno_remove(node* p, int k) // �������� ����� k �� ������ p
{
	// � ��� �� ������ ������ ���� �������� ������?
	if (!p) return 0;
	if (k < p->key)
		p->left = gavno_remove(p->left, k);
	else if (k > p->key)
		p->right = gavno_remove(p->right, k);
	else //  k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
// edit this above

AVL::AVL()
{
	root = nullptr;
}

DeliveryData AVL::operator[](int key)
{
	return find(root, key);
}

DeliveryData AVL::find(node* r, int key)
{
	if (r == nullptr)
	{
		return DeliveryData();  // �� ������
	}
	if (r->key == key)
	{
		return r->data; // �����!!!
	}

	if (key <= r->key)
	{
		// left
		if (r->left != nullptr)
			return find(r->left, key); // ����������� ����� �����
		else
		{
			return DeliveryData(); // �� ������
		}
	}
	else
	{
		//right
		if (r->right)
			return find(r->right, key);// ����������� ����� ������
		else
		{
			return DeliveryData(); // �� ������
		}
	}
}

bool AVL::empty()
{
	if (root)
		return true;
	return false;
}


// ��������� ����� unordered_map � ���
class STL_unordered_map : public BaseCollection  // -�����, ������� �� ��������� �� ������ ������� ���������
{
public:
	void insert(int key, DeliveryData& data) override;
	void remove(int key) override;
	bool empty() override;
	void clear() override;
	STL_unordered_map() {};  // ������� {} !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DeliveryData operator[](int) override;
private:
	std::unordered_map<int, DeliveryData> _map;
};

void STL_unordered_map::insert(int key, DeliveryData& data)
{
	_map.emplace(key, data);
}

void STL_unordered_map::remove(int key)
{
	_map.erase(key);
}

bool STL_unordered_map::empty() 
{
	return _map.empty();
}

void STL_unordered_map::clear() 
{
	_map.clear();
}

DeliveryData STL_unordered_map::operator[](int key) 
{
	return _map.at(key);
}

//STL_unordered_map::STL_unordered_map() = default;
