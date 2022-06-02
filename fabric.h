#pragma once
#include <iostream>
#include "data.h"


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
