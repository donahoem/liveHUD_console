#include "Table.h"
#include <map>
#include <iostream>
#include "Player.h"
using namespace std;

Table::Table() {
	size = 0;
	head = NULL;
	tail = NULL;
	curAction = NULL;
	dealer = NULL;
	sb = NULL;
	bb = NULL;
}
Table::~Table() {};

Table::Table(int n) {
	//create n players and push back each one
	//map in Session holds players
	/*	for (i = mapsize ; i < (mapsize + n) ; i++){
			pushbackPlayer(map[i]);		*/
}

void Table::pushbackPlayer(Player &p) {
	if (size > 9) {
		cout << "Table is full" << endl;
	}
	else {
		Node* v = new Node;
		v->elem = &p;
		if (tail == NULL) { // table is empty
			v->next = v;
			v->prev = v;
			tail = v;
			head = v;
			dealer = v;
		}
		else {
			v->next = tail->next;
			v->prev = tail;
			tail->next = v;
			head->prev = v;
			advanceTail();
		}
		size++;
	}
	setCurrentAction();
	setFirstActionPre();
	setFirstActionPost();
}

void Table::addPlayer(Player &_player, int _seat) {
	Node* v = new Node;
	v->elem = &_player;
	v->elem->setSeat(_seat);

	Node* prev = dealer;
	Node* suc = dealer;

	int min = 11;
	int max = -1;
	int prevSeat;
	int sucSeat;
	vector<int> seats;

	for (int i = 0; i < size; i++) { // all current seats stored in vector
		seats.push_back(suc->elem->getSeatnumber());
		if (seats.at(i) > max && max != 0) max = seats.at(i); // gets max seat number
		if (seats.at(i) == 0) max = 0;
		if (seats.at(i) < min && seats.at(i) != 0) min = seats.at(i);
		suc = suc->next;
	}

	bool defined = false;
	for (int i = 1; i < size; i++) {
		if (seats.at(i) > _seat && (seats.at(i - 1) < _seat || seats.at(i - 1) == max)) {
			sucSeat = seats.at(i);
			prevSeat = seats.at(i - 1);
			defined = true;
		}
	}
	if (!defined) {
		sucSeat = min;
		prevSeat = max;
	}

	// now we have prevSeat and sucSeat numbers

	while (prev->elem->getSeatnumber() != prevSeat) prev = prev->next;
	while (suc->elem->getSeatnumber() != sucSeat) suc = suc->next;

	prev->next = v;
	suc->prev = v;
	v->next = suc;
	v->prev = prev;

	dealer = sb->prev;
	size++;
}


void Table::removePlayer(int _id) {
	Node* cursor = dealer;
	while (cursor->elem->getId() != _id) cursor = cursor->next; // cursor points to node to be removed
	cursor->prev->next = cursor->next;
	cursor->next->prev = cursor->prev;

	if (cursor == dealer) this->retreatDealer();
	if (cursor == head) this->advanceHead();
	if (cursor == tail) this->retreatTail();
	delete cursor;
	size--;
}

void Table::swapSeats(int _id, int _newSeat) {
	Node* cursor = dealer;
	while (cursor->elem->getId() != _id) cursor = cursor->next; // cursor = target id
	if (cursor == dealer) this->retreatDealer();
	if (cursor == head) this->advanceHead();
	if (cursor == tail) this->retreatTail();
	
	if (_newSeat < this->head->elem->getSeatnumber()) head = cursor;
	if (_newSeat > this->tail->elem->getSeatnumber()) tail = cursor;

	Node* prev = cursor;
	Node* suc = cursor;

	int max = -1;
	int min = 11;
	int prevSeat;
	int sucSeat;
	vector<int> seats;


	for (int i = 0; i < size; i++) { // all current seats stored in vector
		seats.push_back(suc->elem->getSeatnumber());
		if (seats.at(i) > max && max != 0) max = seats.at(i); // gets max seat number
		if (seats.at(i) == 0) max = 0;
		if (seats.at(i) < min && seats.at(i) != 0) min = seats.at(i);
		suc = suc->next;
	}

	bool defined = false;
	for (int i = 1; i < size; i++) {
		if (seats.at(i) > _newSeat && (seats.at(i - 1) < _newSeat || seats.at(i - 1) == max)) { 
			sucSeat = seats.at(i);
			prevSeat = seats.at(i - 1);
			defined = true;
		}
	}
	if (!defined) {
		sucSeat = min;
		prevSeat = max;
	}

	while (prev->elem->getSeatnumber() != prevSeat) prev = prev->next;
	while (suc->elem->getSeatnumber() != sucSeat) suc = suc->next;

	cursor->prev->next = cursor->next;
	cursor->next->prev = cursor->prev;

	prev->next = cursor;
	suc->prev = cursor;
	cursor->next = suc;
	cursor->prev = prev;

	cursor->elem->setSeat(_newSeat);
}

void Table::advanceTail() {
	tail = tail->next;
}
void Table::advanceHead(){
	head = head->next;
}
void Table::retreatTail(){
	tail = tail->prev;
}
void Table::advanceDealer() {
	dealer = dealer->next;
	sb = sb->next;
	bb = bb->next;
}
void Table::retreatDealer() {
	dealer = dealer->prev;
}
void Table::setDealer(Player &p) {

}
void Table::advanceCurAction() {
	curAction = curAction->next;
}

void Table::retreatCurAction() {
	curAction = curAction->prev;
}


//getters
int Table::getSize() {
	return size;
}

int Table::getDealear() {
	return dealer->elem->getSeatnumber();
}

int Table::getCurrentAction() {
	return curAction->elem->getSeatnumber();
}

Player* Table::getCurPlayer() {
	return curAction->elem;
}

Player* Table::getFirstPre() {
	return firstActPre->elem;
}

Player* Table::getFirstPost() {
	return firstActPost->elem;
}

Player* Table::getBB() {
	if (size > 2) return dealer->next->next->elem;
	else return dealer->next->elem;
}

Player* Table::getSB() {
	if (size > 2) return dealer->next->elem;
	else return dealer->elem;
}





void Table::dealPre() {

}

void Table::initPlayers(map<int, Player>& _playerMap, int& _playercount) {
	string occupiedSeats;
	cout << "Enter occupied seats in order without spaces" << endl;
	cout << "Use '0' for seat 10" << endl << endl;
	cout << "occupied seats:  ";
	cin >> occupiedSeats;

	//instantiates all seated players and pushes to playerMap
	for (string::iterator it = occupiedSeats.begin(); it != occupiedSeats.end(); ++it) {
		_playerMap[++_playercount] = Player(_playercount, *it - '0'); // swap ++ ??????? did i fuck this up
		this->pushbackPlayer(_playerMap[_playercount]); // create node in table
	}
}

void Table::setNames(map<int, Player>& _playerMap) {
	char choice;
	cout << "Assign names? (y/n):  ";
	cin >> choice;
	while (choice == 'y') {
		int tempId;
		string tempName;
		cout << "Which player ID?:  ";
		cin >> tempId;
		cout << "Enter new name:  ";
		cin >> tempName;
		_playerMap[tempId].setName(tempName);
		this->setPlayerName(tempId, tempName);
		cout << "Assign another name? (y/n):  ";
		cin >> choice;
	}
}

void Table::initPreFActions(map<Player, int>& _actions) {
	for (int i = 0; i < size; i++) {
		Player* curPlayer = this->getCurPlayer();
		_actions[*curPlayer] = 0;
		this->advanceCurAction();
	}
	this->updatePointers();

	if (size == 2) {
		Player* sb = this->getSB();
		Player* bb = this->getBB();
		_actions[*sb] = 1;
		_actions[*bb] = 2;
	}
	else {
		for (int i = 0; i < _actions.size() - 2; i++) {
			Player* curPlayer = this->getCurPlayer();
			_actions[*curPlayer] = 0;
			this->advanceCurAction();
		}
		Player* sb = this->getSB();
		Player* bb = this->getBB();
		_actions[*bb] = 2;
		_actions[*sb] = 1;
		this->updatePointers();
	}
}

void Table::initPostFActions(map<Player, int>& _actions) {
	this->curAction = dealer->next;
	for (int i = 0; i < size; i++) {
		if (!curAction->elem->folded()){
			Player* curPlayer = this->getCurPlayer();
			_actions[*curPlayer] = 0;
		}
		this->advanceCurAction();
	}
	this->curAction = dealer->next;
}


void Table::getPreflopActions(map<Player, int>& _actions, int& _activeHands) {
	int _curBet = 2;
	cout << endl << endl << endl << "____________________" << endl << "     PREFLOP     " << endl;
	this->printPlayers(_actions);
	cout << "1 = fold\n2 = check/call\n3 = raise" << endl << endl;
	cout << "Enter action:  ";

	bool limpedAround = false;
	int limpedAroundCount = 0;
	//loops for every preflop action
	while (1) {
		limpedAround = false;
		bool _actionOpen = false;
		int action;
		cin >> action;
		switch (action) {
		case 1:
			_actions[*this->getCurPlayer()] = -1;
			--_activeHands;
			this->curActionFolds();
			break;
		case 2:
			_actions[*this->getCurPlayer()] = _curBet;
			break;
		case 3:
			_actions[*this->getCurPlayer()] = ++_curBet;
			break;
		}

		if (_activeHands == 1) return;



		/////////// 

		int limpCount = 0;
		int advanceCount = 0;
		for (int i = 0; i < _actions.size(); i++) {
			if (_actions[*this->getCurPlayer()] == 2 || _actions[*this->getCurPlayer()] == -1) ++limpCount;
			this->advanceCurAction();
			++advanceCount;
		}
		for (int i = 0; i < advanceCount; i++) this->retreatCurAction();
		advanceCount = 0;
		if (limpCount == _actions.size() && limpedAroundCount != 1) {
			limpedAround = true;
			++limpedAroundCount;
		}

		///////////////////




		for (int i = 0; i < _actions.size() - 1; i++) {
			Player* cur;
			cur = this->getCurPlayer();
			Player* next;
			this->advanceCurAction();
			++advanceCount;
			while (this->getCurPlayer()->folded()) {
				this->advanceCurAction();
				++advanceCount;
			}
			next = this->getCurPlayer();
			if (_actions[*cur] != -1 && _actions[*cur] != _actions[*next]) {
				_actionOpen = true;
			}
		}
		for (int i = 0; i < advanceCount; i++) this->retreatCurAction();
		advanceCount = 0;

		if (limpedAround) _actionOpen = true;
		if (!_actionOpen) return;




		this->advanceCurAction();
		while (this->getCurPlayer()->folded()) this->advanceCurAction();
		this->printPlayers(_actions);
		cout << "1 = fold\n2 = check/call\n3 = raise" << endl << endl;
		cout << "Enter action:  ";
	}

}

void Table::getPostFlopActions(map<Player, int>& _actions, int& _activeHands) {
	int _curBet = 0;
	this->curAction = this->dealer->next;
	while (curAction->elem->folded()) this->advanceCurAction();

	this->printPlayers(_actions);
	cout << "1 = fold\n2 = check/call\n3 = raise" << endl << endl;
	cout << "Enter action:  ";

	bool limpedAround = false;
	int limpedAroundCount = 0;
	//loops for every flop action
	int loopCounter = 1;
	while (1) {
		bool _actionOpen = false;
		int action;
		cin >> action;
		switch (action) {
		case 1:
			_actions[*this->getCurPlayer()] = -1;
			--_activeHands;
			this->curActionFolds();
			break;
		case 2:
			_actions[*this->getCurPlayer()] = _curBet;
			break;
		case 3:
			_actions[*this->getCurPlayer()] = ++_curBet;
			break;
		}
		if (_activeHands == 1) return;

		/////////// 
		int advanceCount = 0;

		if (loopCounter == _actions.size()) {
			int limpCount = 0;
			for (int i = 0; i < _actions.size(); i++) {
				if (_actions[*this->getCurPlayer()] == 0 || _actions[*this->getCurPlayer()] == -1) ++limpCount;
				this->advanceCurAction();
				++advanceCount;
			}
			for (int i = 0; i < advanceCount; i++) this->retreatCurAction();
			advanceCount = 0;
			if (limpCount == _actions.size() && limpedAroundCount != 1) {
				limpedAround = true;
				++limpedAroundCount;
			}
		}
		///////////////////


		for (int i = 0; i < size - 1; i++) { //actions.size

			Player* cur;
			while (this->getCurPlayer()->folded()) {
				this->advanceCurAction();
				++advanceCount;
			}
			cur = this->getCurPlayer();

			Player* next;
			this->advanceCurAction();
			++advanceCount;
			while (this->getCurPlayer()->folded()) {
				this->advanceCurAction();
				++advanceCount;
			}
			next = this->getCurPlayer();

			//
			if ((_actions[*cur] != _actions[*next]) || (_actions[*cur] == 0)) {
				_actionOpen = true;
			}
			//

		}

		for (int i = 0; i < advanceCount; i++) this->retreatCurAction();
		advanceCount = 0;

		if (limpedAround) _actionOpen = true;
		if (!_actionOpen) return;

		this->advanceCurAction();
		while (this->getCurPlayer()->folded()) this->advanceCurAction();
		this->printPlayers(_actions);
		cout << "1 = fold\n2 = check/call\n3 = raise" << endl << endl;
		cout << "Enter action:  ";
		++loopCounter;
	}

}

void Table::getTurnActions(map<Player, int>&, int&) {

}

void Table::getRiverActions(map<Player, int>&, int&) {

}



void Table::printPlayers() {
	Node* cursor = curAction->prev;
	cout << "______________________________" << endl;
	for (int i = 0; i < size; i++) {
		cout << endl;
		if (i == 0) cout << endl << endl << endl;
		if (!cursor->elem->folded()) cout << "          [][]";
		if (cursor == dealer->next) cout << "." << endl;
		else if (cursor == dealer->next->next) cout << ".." << endl;
		else cout << endl;
		if (i == size - 1) cout << "####ACTION####" << endl;
		else cout << "##############" << endl;
		if (cursor == dealer) cout << "<D>" << endl;
		cout << "Player ID: ";
		cout << cursor->elem->getId() << endl;
		cout << "Seat number: ";
		cout << cursor->elem->getSeatnumber() << endl;
		cout << "Name: " << cursor->elem->getName() << endl;
		cout << "##############" << endl << endl;
		cursor = cursor->prev;
	}
}


void Table::printPlayers(map<Player, int> _actions) {
	Node* cursor = curAction->prev;
	for (int i = 0; i < size; i++) {
		cout << endl;
		if (i == 0) cout << endl << endl << endl << endl << "________________________________________" << endl;
		if (!cursor->elem->folded()) {
			cout << "          [][]";

			//FOR LOOP WOULDNT WORK HERE
			int j = 0;
			while (j < _actions[*cursor->elem]) {
				cout << ".";
				j++;
			}
			////////////////////////////

			cout << endl;
			if (i == size - 1) cout << "~CURRENT ACTION~" << endl;
			//else cout << "##############" << endl;
			if (cursor == dealer) cout << "______________<D>" << endl;
			cout << "Player ID: ";
			cout << cursor->elem->getId() << endl;
			cout << "Seat number: ";
			cout << cursor->elem->getSeatnumber() << endl;
			cout << "Name: " << cursor->elem->getName() << endl;
			if (cursor == dealer) cout << "______________" << endl;
			//else cout << endl;
			if (i == size - 1) {
				cout << "~~~~~~~~~~~~~~~~" << endl << endl;
			}
		}
		cursor = cursor->prev;

	}
}

void Table::setPlayerName(int _id, string _name) {
	Node* cursor = dealer;
	for (int i = 0; i < size; i++) {
		if (_id == cursor->elem->getId()) {
			cursor->elem->setName(_name);
		}
		cursor = cursor->next;
	}
}

void Table::setDealer(int _seat) {
	while (dealer->elem->getSeatnumber() != _seat) {
		advanceDealer();
	}
	setCurrentAction();
	setFirstActionPost();
	setFirstActionPre();
}

void Table::updatePointers() {
	setCurrentAction();
	setFirstActionPost();
	setFirstActionPre();
}

void Table::setCurrentAction() {
	if (size == 2) {
		curAction = dealer->next->next;
		sb = dealer;
		bb = dealer->next;
	}
	if (size > 2) {
		curAction = dealer->next->next->next;
		sb = dealer->next;
		bb = dealer->next->next;
	}
}

void Table::setFirstActionPre() {
	firstActPre = curAction;
}

void Table::setFirstActionPost() {
	firstActPost = dealer->next;
}

void Table::advanceFirstActionPost() {
	firstActPost = firstActPost->next;
}

void Table::dealCards() {
	Node* cursor = dealer;
	dealer->elem->dealCards();
	while (1) {
		cursor->elem->dealCards();
		cursor = cursor->next;
		if (cursor == dealer) break;
	}
	this->setCurrentAction();
}

void Table::curActionFolds() {
	curAction->elem->playerFolds();
}