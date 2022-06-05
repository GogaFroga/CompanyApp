#include <iostream>
#include <fstream>
#include "fabric.h"
#include "AVL.h"

using std::string;
using std::cout;
using std::cin;
using std::fstream;
using std::ofstream;
using std::ifstream;


int main()
{
	Fabric fabric;
	ifstream in;
	in.open("DB.txt");
	ofstream out;
	out.open("DB.txt");
	ofstream output;
	output.open("DBtemp.txt");
	//ofstream gen;
	//gen.open("DB.txt");  // add ", std::ios::app"  n// C:\\Users\\User\\Documents\\GitHub\\CompanyApp

	DeliveryData data_buff;		// временный буферный объект
	DeliveryData user_input;	// вводимые данные
	DeliveryData findobj;
	int amount = 0;
	int action = 0;
	int ch = -1;
	int found = 0;
	int ID;

	/* выбор коллекции */
	cout << "Choose: (1)AVL (2)Map\n>";
	std::cin >> action;
	BaseCollection *collection = nullptr;
	if (action == 1)
		collection = new AVL;
	else if (action == 2)
		collection = new STL_unordered_map;


	/* выбор действий */
	while (ch != 5) 
	{
		cout << "Choose: (1)Find (2)Add (3)Delete (4)Generate (5)Exit\n>";
		std::cin >> action;
		switch (action)
		{
			case 1:		/* найти */
				cout << "		Enter ID:\n>";
				cin >> ID;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < amount / 10; j++)
					{
						in >> data_buff;
						collection->insert(data_buff.index, data_buff);
					}
					findobj = collection->find(ID);
					if (found != 1 && findobj.index > 0)
					{
						found = 1;
						cout << "		Data was found: \n" << findobj;
					}
				}
				found = 0;
				break;

			case 2:		/* добавить */
				cout << "Enter data:\n>";
				cin >> user_input.index >> user_input.sender_name >> user_input.reciving_name >> user_input.starting_point
					>> user_input.ending_point >> user_input.sending_time >> user_input.receiving_time >> user_input.delivery_price
					>> user_input.transport_type >> user_input.content_name >> user_input.content_price >> user_input.weight;
				out << user_input;
				break;

			case 3:		/* удалить */
				cout << "Enter ID: ";
				cin >> ID;

				in >> data_buff;
				cout << "data\n" << data_buff;
				collection->insert(data_buff.index, data_buff);
				in >> data_buff;
				cout << "data\n" << data_buff;
				collection->insert(data_buff.index, data_buff);
				in >> data_buff;
				cout << "data\n" << data_buff;
				collection->insert(data_buff.index, data_buff);

				findobj = collection->find(ID);
				collection->remove(ID);
				
				//output << collection;
				collection->clear();
				/*for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < amount / 10; j++)
					{
						in >> data_buff;
						cout << "data\n" << data_buff;
						collection->insert(data_buff.index, data_buff);
					}

					findobj = collection->find(ID);
					if (found != 1 && findobj.index >= 0) // !!!!!!!!!!!!!!
					{
						found = 1;
						collection->remove(ID);
					}
					output << collection; // write to file
					collection->clear(); // !!!!!!!!!!!!!!
				}
				*/
				found = 0;
				ID = -1;
				break;

			case 4:		/* генерация */
				cout << "Generated amount:\n>";
				cin >> amount;
				if (out.is_open())
				{
					DeliveryData data_o;
					for (int i = 0; i < amount; i++)
					{
						data_o = fabric.generateRandom();
						cout << data_o;
						out << data_o;
					}
					cout << "\n			File: Succeed\n";
					break;
				}
				else
					cout << "\n			File Error: File is not opened\n";
			case 5:		/* выход */
				ch = 5;
				break;
		}
	}
}

	/* считывание по частям и работа */
			 /*
	if (in.is_open())
	{
		DeliveryData data_i;
		cout << endl << "TEST:\n";
		for (int i = 0; i < amount/10; i++)
		{
			for (int j = 0; j < amount/10; j++)
			{
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
	*/
