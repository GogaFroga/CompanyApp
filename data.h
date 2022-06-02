#pragma once
#include <iostream>

using std::string;


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

	friend std::ostream& operator<<(std::ostream& os, const DeliveryData& data)
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
