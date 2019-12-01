//
//  Player.cpp
//  liveHUD_cpp_working
//
//  Created by Michael Donahoe on 11/22/19.
//  Copyright © 2019 liveHUD. All rights reserved.
//

#include <stdio.h>
#include "Player.h"



// Default constructor never called -- needs revision if implemented
Player::Player() {
	ID = 0;
	name = "DEFAULT";

	// Initialize stats
	hands = 0;
	VPIP = 0;
	PFR = 0;
	ATS = 0;
	threebet = 0;
	f3b = 0;
	fourbet = 0;
	f4b = 0;
	fivebet = 0;
	f5b = 0;

	// initialize trackers
	walks = 0;
	pfRaises = 0;
	pfCalls = 0;
	stealAttempts = 0;
	stealOpportunities = 0;
	threeBets = 0;
	called2bets = 0;
	num3betFolds = 0;
	num3betCallsAfter2b = 0;
	fourBets = 0;
	num3betCalls = 0;
}

Player::~Player() {};

Player::Player(int playercount, int seat) {
	ID = playercount;
	hasCards = false;
	seatnumber = seat;

	// Initialize stats
	hands = 0;
	VPIP = 0;
	PFR = 0;
	ATS = 0;
	threebet = 0;
	f3b = 0;
	fourbet = 0;
	f4b = 0;
	fivebet = 0;
	f5b = 0;

	// initialize trackers
	walks = 0;
	pfRaises = 0;
	pfCalls = 0;
	stealAttempts = 0;
	stealOpportunities = 0;
	threeBets = 0;
	called2bets = 0;
	num3betFolds = 0;
	num3betCallsAfter2b = 0;
	fourBets = 0;
	num3betCalls = 0;
}

//getters
string Player::getName() {
	return name;
}

int Player::getId() {
	return ID;
}

int Player::getSeatnumber() {
	return seatnumber;
}

bool Player::folded() {
	if (hasCards) return false;
	else return true;
}

//mutators
void Player::playerFolds() {
	hasCards = false;
}
void Player::dealCards() {
	hasCards = true;
}
void Player::setName(string newName) {
	name = newName;
}

void Player::setSeat(int _seat) {
	this->seatnumber = _seat;
}


//trackering mutators
void Player::addHand() {
	hands++;
}
void Player::addWalk() {
	walks++;
}
void Player::addPfRaise() {
	pfRaises++;
}
void Player::addPfCall() {
	pfCalls++;
}
void Player::addStealAtt() {
	stealAttempts++;
}
void Player::addStealOpp() {
	stealOpportunities++;
}
void Player::addThreeBet() {
	threeBets++;
}
void Player::addCalled2bet() {
	called2bets++;
}
void Player::add3betFold() {
	num3betFolds++;
}
void Player::add3betCallAfter2b() {
	num3betCallsAfter2b++;
}
void Player::addFourBet() {
	fourBets++;
}
void Player::add3betCall() {
	num3betCalls++;
}


//stats
int Player::numHands() {
	return hands;
}
void Player::calculateVPIP() {
	VPIP = (pfRaises + pfCalls) / hands;
}
double Player::displayVPIP() {
	return VPIP;
}
void Player::calculatePFR() {
	PFR = pfRaises / (hands - walks);
}
double Player::displayPFR() {
	return PFR;
}
void Player::calculateATS() {
	ATS = stealAttempts / stealOpportunities;
}
double Player::displayATS() {
	return ATS;
}
void Player::calculate3bet() {
	threebet = threeBets / (called2bets + threeBets);
}
double Player::display3bet() {
	return threebet;
}
void Player::calculatef3bet() {
	f3b = num3betFolds / (num3betCallsAfter2b + num3betFolds);
}
double Player::displayf3bet() {
	return f3b;
}
void Player::calculate4bet() {
	fourbet = fourBets / (fourBets + num3betCalls);
}
double Player::display4bet() {
	return fourbet;
}
void Player::calculatef4bet() {
	//add 4bet formula
}
double Player::displayf4bet() {
	return fourbet;
}
void Player::calculate5bet() {
	//add 5bet formula
}
double Player::display5bet() {
	return fivebet;
}


