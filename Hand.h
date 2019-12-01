#pragma once
#include "Table.h"
class Hand
{
private:
	int ID;
	Table table;


public:
	Hand();
	Hand(int, Table);
	~Hand();

	//getters
	int getID();
	Table getTable();


	//mutators
	void setID(int);
	void setTable(Table);


};
