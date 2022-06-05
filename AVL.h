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
	node(int k, DeliveryData d) { key = k; data = d;  left = right = nullptr; height = 1; }
	// node(int k) { key = k; left = right = 0; height = 1; }
	/*
	~node() { 
	if (this->left) 
		delete this->left;
	if (this->right)
		delete this->right;
	if (this->key)
		this->key = -1;
	} */
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
		virtual DeliveryData find(int key) = 0;
		virtual void insert(int, DeliveryData&) = 0;
		virtual void remove(int key) = 0;
		virtual DeliveryData operator[](int) = 0;
		virtual ~BaseCollection() = default;
};

class AVL : public BaseCollection	// AVL-�����, ������� �� ��������� �� ������ ������� ���������
{
	public:
		int height();
		void insert(int key, DeliveryData& data) override;
		void remove(int key) override;
		bool empty() override;
		DeliveryData find(int key);
		void clear() override; //�������� �� ���� while(!empty) remove(root)!!!!!!!!!!!
		DeliveryData operator[](int);
		AVL();
		node* root;  // root �������� �� PUBLIC!!!!!!!!!!!
		
	private:
		int bfactor(node*);
		void fixheight(node* p);
		node* rotateright(node* p);
		node* rotateleft(node* q);
		node* balance(node* p);
		node* rec_insert(node* p, int k, DeliveryData&);
		node* rec_remove(node* p, int k);
		DeliveryData rec_find(node* r, int key);
		node* findmin(node* p);
		node* removemin(node* p);
};

int AVL::height()
{
	return root ? root->height : 0;
}

void AVL::clear()
{
	while (!empty())
		remove(root->key);
}

int AVL::bfactor(node* p)
{
	if (p->left != nullptr && p->right != nullptr)
		return (p->right)->height - (p->left)->height;
	else if (p->left == nullptr)
		return ((p->right)->height);
	else if (p->right == nullptr)
		return ((p->left)->height);
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
	node* rret = p->left;
	p->left = rret->right;
	rret->right = p;
	fixheight(p);
	fixheight(rret);
	return rret;
}

node* AVL::rotateleft(node* q) // ����� ������� ������ q
{
	node* lret = q->right;
	q->right = lret->left;
	lret->left = q;
	fixheight(q);
	fixheight(lret);
	return lret;
}

node* AVL::balance(node* balance_node)  // �� �����?
{
	fixheight(balance_node);
	if (bfactor(balance_node) == 2)
	{
		if (bfactor(balance_node->right) < 0)
			balance_node->right = rotateright(balance_node->right);
		balance_node = rotateleft(balance_node);
		return balance_node; // ��� �������� �� ���� ��������� ������ ����
	}
	if (bfactor(balance_node) == -2)
	{
		if (bfactor(balance_node->left) > 0)
			balance_node->left = rotateleft(balance_node->left);
		return rotateright(balance_node);
	}
	return balance_node;
}

node* AVL::findmin(node* p) // ����� ���� � ����������� ������ � ������ p 
{
	if (p == nullptr)
		return nullptr;
	else if (p->left != nullptr)
		return p->left ? findmin(p->left) : p;

	
}

node* AVL::removemin(node* p)  // �������� ���� � ����������� ������ �� ������ p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

void AVL::insert(int key, DeliveryData& data)
{
	if (root == nullptr)
	{
		root = rec_insert(root, key, data);
	}
	else
		AVL::root = rec_insert(root, key, data);
}

node* AVL::rec_insert(node* rec_insert_node, int k, DeliveryData& data)  // ������� ����� k � ������ � ������ p
{
	if (!rec_insert_node)
		return new node(k, data); 
	if (k < rec_insert_node->key)
		rec_insert_node->left = rec_insert(rec_insert_node->left, k, data);
	else
		rec_insert_node->right = rec_insert(rec_insert_node->right, k, data);
	//std::cout << p->data;
	node* temporary_node = balance(rec_insert_node);
	return temporary_node;
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

void AVL::remove(int key)
{
	if (key == root->key and !root->left and !root->right)
	{
		delete root;
		root = nullptr;
	}
	else
		rec_remove(root, key);
}

node* AVL::rec_remove(node* p, int k) // �������� ����� k �� ������ p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = rec_remove(p->left, k);
	else if (k > p->key)
		p->right = rec_remove(p->right, k);
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

DeliveryData AVL::find(int key)
{
	DeliveryData temp = rec_find(root, key);
	return(temp);
}

DeliveryData AVL::rec_find(node* r, int key)  // ��������� ������ ����� ����������
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
			return rec_find(r->left, key); // ����������� ����� �����
		else
		{
			return DeliveryData(); // �� ������
		}
	}
	else
	{
		//right
		if (r->right)
			return rec_find(r->right, key); // ����������� ����� ������
		else
		{
			return DeliveryData(); // �� ������
		}
	}
}

DeliveryData AVL::operator[](int key)
{
	return rec_find(root, key);
}

AVL::AVL()
{
	root = nullptr;
}

bool AVL::empty()
{
	if (root == nullptr)
		return true;
	return false;
}



// ��������� ����� unordered_map � ���
class STL_unordered_map : public BaseCollection  // -�����, ������� �� ��������� �� ������ ������� ���������
{
public:
	void insert(int key, DeliveryData& data) override;
	void remove(int key) override;
	DeliveryData find(int key) override;
	bool empty() override;
	void clear() override;
	STL_unordered_map() {};  // ������� {} !!!!!!!!!!!!!!!!!!!!!!!!!!!!
	DeliveryData operator[](int) override;
	friend std::ifstream& operator>>(std::ifstream& is, STL_unordered_map& a)
	{
		is >> a;
		return is;
	}
	friend std::ostream& operator<<(std::ostream& os, STL_unordered_map& a)
	{
		os << a;
		return os;
	}
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

DeliveryData STL_unordered_map::find(int key)
{
	//_map.clear();
	return(0);
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
