/*
NOTES:
-This program is a WIP console implementation of a No Limit Texas Holdem Heads Up Display (HUD)
-This program is currently being implemented as an Android application
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include "Player.h"
#include "Table.h"
#include "Hand.h"
using namespace std;

int main()
{
	char newHand = 'y';
	char updatePlayers = 'y';
	char changeSeats = 'n';
	int swapID;
	int newSeat;
	char addPlayer = 'n';
	char removePlayer = 'n';
	int removeID;
	int playercount = 0;
	int handcount = 0;
	int dealer;
	int curBet;
	map<int, Player> playerMap;
	map<int, Hand> handMap;
	map<Player, int> pfActions;
	map<Player, int> fActions;
	map<Player, int> tActions;
	map<Player, int> rActions;
	Table table;



	table.initPlayers(playerMap, playercount);
	table.printPlayers();
	table.setNames(playerMap);
	table.printPlayers();
	cout << "Set dealer by seat number:  ";
	cin >> dealer;
	table.setDealer(dealer);

	while (newHand == 'y') {
		handMap[++handcount] = Hand(handcount, table); //handMap[1] = Hand ID '1' 
		table.dealCards();

		table.initPreFActions(pfActions);
		int activeHands = pfActions.size();
		table.getPreflopActions(pfActions, activeHands);
		if (activeHands == 1) cout << endl << "HAND COMPLETE" << endl;
		else {
			table.initPostFActions(fActions); 
			cout << endl << endl << "____________________" << endl << "     FLOP     " << endl;
			table.getPostFlopActions(fActions, activeHands);
			if (activeHands == 1) cout << endl << "HAND COMPLETE" << endl;
			else {
				table.initPostFActions(tActions);
				cout << endl << endl << "____________________" << endl << "     TURN     " << endl;
				table.getPostFlopActions(tActions, activeHands);
				if (activeHands == 1) cout << endl << "HAND COMPLETE" << endl;
				else {
					table.initPostFActions(rActions);
					cout << endl << endl << "____________________" << endl << "     RIVER     " << endl;
					table.getPostFlopActions(rActions, activeHands);
				}
			}
		}

		cout << "New hand? (y/n):  ";
		cin >> newHand;
		if (newHand == 'y') {
			table.advanceDealer();
			cout << "Update players? (y/n):  ";
			cin >> updatePlayers;
			if (updatePlayers == 'y') {

				cout << "Did any players change seats? (y/n):  ";
				cin >> changeSeats;
				while (changeSeats == 'y') {
					cout << "Enter ID of player who changed seats:  ";
					cin >> swapID;
					cout << "Enter player's new seat number:  ";
					cin >> newSeat;
					table.swapSeats(swapID, newSeat);
					cout << "Swap another seat? (y/n):  ";
					cin >> changeSeats;
				}

				cout << "Remove player(s)? (y/n):  ";
				cin >> removePlayer;
				while (removePlayer == 'y') {
					cout << "Enter player ID to be removed:  ";
					cin >> removeID;
					table.removePlayer(removeID);
					cout << "Remove another player? (y/n):  ";
					cin >> removePlayer;
				}

				cout << "Add new player(s)? (y/n):  ";
				cin >> addPlayer;
				while (addPlayer == 'y') {
					cout << "Enter seat number:  ";
					cin >> newSeat;
					playerMap[++playercount] = Player(playercount, newSeat); 
					table.addPlayer(playerMap[playercount], newSeat);
					cout << "Add another player? (y/n):  ";
					cin >> addPlayer;
				}

			}
		}

	}
	return 0;




}
