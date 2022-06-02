#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::ofstream;

class DeliveryData {
	private:

	public:
		int index;				// 
		string sender_name;		// SENDING_INFO
		string starting_point;	// SENDING_INFO
		int sending_time;		// SENDING_INFO
		string reciving_name;	// RECIVING_INFO
		string ending_point;	// RECIVING_INFO
		int receiving_time;		// RECIVING_INFO
		int delivery_price;		// DELIVERY_INFO
		int transport_type;		// DELIVERY_INFO (0-road, 1-rail, 2-sea, 3-air)
		float weight;			// CONTENT_INFO
		int content_price;		// CONTENT_INFO
		string content_name;	// CONTENT_INFO

		DeliveryData(int _index)
		{
			index = _index;
			sender_name = "SENDER";
			starting_point = "START";
			sending_time = -1;
			reciving_name = "RECIVER";
			ending_point = "END";
			receiving_time = -1;
			delivery_price = -1;
			transport_type = -1;
			weight = -1;
			content_price = -1;
			content_name = "CONTENT";
		}

		friend std::ostream& operator<<(std::ostream &os, const DeliveryData &data)
		{
			os << "Index: " << data.index;
			os << "\nSender: " << data.sender_name << "\nReciver: " << data.reciving_name;
			os << "\nFrom " << data.starting_point << " to " << data.ending_point;
			os << "\nSending time: " << data.sending_time << "\nReciving time: " << data.receiving_time;
			os << "\nDelivery price: " << data.delivery_price << "\nTransport: " << data.transport_type;
			os << "\nContent: " << data.content_name << "\nContent price: " << data.content_price << "\nWeight: " << data.weight << "\n";
			return os;
		}
};

// сделать фабрику
// корректное считывание из файла

class Fabric {
	int ID;
public:
	Fabric()
	{
		ID = 0;
	}
	DeliveryData generateRandom()
	{
		DeliveryData random(++ID);
		generate_str(rand() % 60 + 1, random.sender_name);		//
		generate_str(rand() % 60 + 1, random.starting_point);
		generate_int(60, random.sending_time);
		generate_str(rand() % 60 + 1, random.reciving_name);	//
		generate_str(rand() % 60 + 1, random.ending_point);
		generate_int(60, random.receiving_time);
		generate_int(1000, random.delivery_price);				//
		generate_int(4, random.transport_type);
		generate_float(100, random.weight);
		generate_int(1000, random.content_price);
		generate_str(rand() % 60 + 1, random.content_name);
		return random;
	}

	void generate_int(int max, int& n);
	void generate_float(int max, float& n);
	void generate_str(int max, std::string& str);
};

void Fabric::generate_int(int max, int& n)
{
	n = rand() % max + 1;
}

void Fabric::generate_float(int max, float& n)
{
	n = rand() % max + 1;
}

void Fabric::generate_str(int max, std::string& str)
{
	str = "";
	for (int i = 0; i < max; i++)
	{
		char r = rand() % 26 + 65;
		str += r;
	}
}


int main()
{
	ofstream out;
	out.open("C:\\Users\\User\\source\\repos\\CompanyApp\\CompanyApp\\DB.txt", std::ios::app);
	Fabric fabric;

	if (out.is_open())
	{
		for (int i = 0; i < 1000; i++)
		{
			DeliveryData data = fabric.generateRandom();
			cout << data;
			out << data;
		}
		cout << "\nFile: Succeed\n";
	}
	else
		cout << "\nFile Error: File is not opened\n";

	out.close();
}
