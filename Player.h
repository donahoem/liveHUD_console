//
//  Player.h
//  liveHUD_cpp_working
//
//  Created by Michael Donahoe on 11/22/19.
//  Copyright © 2019 liveHUD. All rights reserved.
//

#ifndef Table_h
#define Table_h
#include <string>
#include <vector>
using namespace std;

class Player {
private:
	string name;
	int ID;
	bool hasCards;
	int seatnumber;

	//preflop stats (displayed)
	int hands;
	double VPIP, PFR, ATS, threebet, f3b, fourbet, f4b, fivebet, f5b;

	//preflop stats (not displayed)
	int walks;
	int pfRaises;
	int pfCalls;
	int stealAttempts;
	int stealOpportunities;
	int threeBets;
	int called2bets;
	int num3betFolds;
	int num3betCallsAfter2b;
	int fourBets;
	int num3betCalls;

	//flop stats
	//double flop_cbet, flop_fcbet;

		//flop situations to track
		//
		//

	//turn stats
	//double turn_delayed_cbet, turn_f_delayed_cbet, turn_double_barrel, turn_f_double_barrel;

		//turn situations to track
		//
		//

	//river stats
	//double river_steal, river_f_steal, river_double_barrel, river_f_double_barrel, river_triple_barrel, river_f_triple_barrel;

		// River situations to track
		//
		//

public:
	Player(int, int);

	//default constructor, only exists for map
	Player();
	~Player();

	//getters
	string getName();
	int getId();
	int getSeatnumber();
	bool folded();

	//mutators
	void playerFolds();
	void dealCards();
	void updateCurAction(int);
	int displayCurAction(int);
	void setName(string);
	void setSeat(int);


	//tracking mutators
	void addHand();
	void addWalk();
	void addPfRaise();
	void addPfCall();
	void addStealAtt();
	void addStealOpp();
	void addThreeBet();
	void addCalled2bet();
	void add3betFold();
	void add3betCallAfter2b();
	void addFourBet();
	void add3betCall();


	//stats
	int numHands();
	void calculateVPIP();
	double displayVPIP();
	void calculatePFR();
	double displayPFR();
	void calculateATS();
	double displayATS();
	void calculate3bet();
	double display3bet();
	void calculatef3bet();
	double displayf3bet();
	void calculate4bet();
	double display4bet();
	void calculatef4bet();
	double displayf4bet();
	void calculate5bet();
	double display5bet();



	friend bool operator< (const Player& a, const Player& b) {
		if (a.ID < b.ID) return true;
		else return false;
	}

	friend bool operator==(const Player& a, const Player& b) {
		if (a.ID == b.ID) return true;
		else return false;
	}
};


#endif /* Player_h */