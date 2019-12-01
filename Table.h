#pragma once
#include "Player.h"
#include <vector>
#include <unordered_map>
#include <map>
class Table
{
private:
	struct Node {
		Player* elem;
		Node* next = NULL;
		Node* prev = NULL;
	};
	Node* head;
	Node* tail;
	Node* curAction;
	Node* dealer;
	Node* sb;
	Node* bb;
	Node* firstActPre;
	Node* firstActPost;
	int size;
	//bool seats[10];



	vector<Player> listPlayers();
public:
	Table();
	~Table();
	Table(int);

	//players
	void pushbackPlayer(Player&); // back = tail
	void addPlayer(Player&, int);
	void removePlayer(int);
	void swapSeats(int, int);

	//pointers
	void advanceTail();
	void advanceHead();
	void retreatTail();
	void advanceDealer();
	void retreatDealer();
	void advanceCurAction();
	void retreatCurAction();
	void setDealer(Player&);
	void updatePointers();

	void setFirstActionPre();
	void setFirstActionPost();
	void advanceFirstActionPost();

	//getters
	int getSize();
	int getDealear();
	int getCurrentAction();
	Player* getCurPlayer();
	Player* getFirstPre();
	Player* getFirstPost();
	Player* getBB();
	Player* getSB();


	void dealPre(); // new
	void initPlayers(map<int, Player>&, int&); // new
	void setNames(map<int, Player>&); // new
	void initPreFActions(map<Player, int>&); // new
	void initPostFActions(map<Player, int>&);


	void getPreflopActions(map<Player, int>&, int&);
	void getPostFlopActions(map <Player, int>&, int&);
	void getTurnActions(map<Player, int>&, int&);
	void getRiverActions(map<Player, int>&, int&);
	void printPlayers();
	void printPlayers(map<Player, int>);
	void setPlayerName(int, string);
	void setDealer(int);
	void setCurrentAction();
	void dealCards();
	void curActionFolds();
};