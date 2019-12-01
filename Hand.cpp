#include "Hand.h"
Hand::Hand() {};
Hand::~Hand() {};
Hand::Hand(int _id, Table _table) {
	ID = _id;
	table = _table;
}

//getters
int Hand::getID() {
	return ID;
}

Table Hand::getTable() {
	return table;
}

//mutators
void Hand::setID(int _id) {
	ID = _id;
}

void Hand::setTable(Table _table) {
	table = _table;
}