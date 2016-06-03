// ConsoleApplication2.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <float.h>
#include "Player.h"
using namespace std;

/* Assumptions made for this calculation:
	-Each "hit" is a single and base-runners only advances one base
	-Batters do not hit fielder's choice
*/

const int numberOfInnings = 8;
const int mercyRule = 7;

bool didHitBall(float battingAvg) {
	float randomNumber = (rand() % 1000)/1000.0f;
	if (battingAvg > randomNumber) {
		return true;
	} else{
		return false;
	}
}

int main()
{
	vector<Player> lineupVector;
	vector<Player>::iterator iter;
	ifstream ifs;
	int numOfSimulations = 0;

	ifs.open("lineup.txt", ifstream::in);

	//Retrieving line up and batting averages
	while (!ifs.eof()) {
		string playerName;
		float battingAvg;

		ifs >> playerName;
		ifs >> battingAvg;

		Player player(playerName, battingAvg);
		lineupVector.push_back(player);
	}

	if (lineupVector.size() == 0) {
		return 0;
	}

	cout << "~~Inputed Roster~~" << endl; 
	for (iter = lineupVector.begin(); iter != lineupVector.end(); iter++) {
		cout << iter->m_name;
		for (int i = 0; i < (20 - iter->m_name.size() - 5); i++) {
			cout << "-";
		}
		cout << iter->m_battingAvg << endl;
	}

	while (numOfSimulations <= 0) {
		cout << endl << "Enter number of simulations: ";
		cin >> numOfSimulations;
	}

	int safeCount;
	int outCount;
	int playerIndex;
	int totalRunsPerGame;
	int totalRunsPerSimulation = 0;
	// For loop for simulating number of games
	for (int sim = 0; sim < numOfSimulations; sim++) {
		safeCount = 0;
		outCount = 0;
		playerIndex = 0;
		totalRunsPerGame = 0;
		//For loop for number of Innings in a game
		for (int i = 0; i < numberOfInnings; i++) {
			//Simulating each inning
			while (outCount < 3) {
				if (i < 8 && safeCount >= 10) {
					//MERCY RULE
					//cout << "MERCY! " << endl;
					break;
				}
				if (didHitBall(lineupVector.at(playerIndex).m_battingAvg)) {
					safeCount++;
				}
				else {
					outCount++;
				}
				playerIndex++;
				if (playerIndex >= (int)lineupVector.size()) {
					//Top of lineup
					playerIndex = 0;
				}
			}

			int totalRunsPerInning = (safeCount - 3 > 0) ? safeCount - 3 : 0;
			totalRunsPerGame += totalRunsPerInning;

			//cout << "Inning " << i + 1 << "Runs " << totalRunsPerInning << endl;

			safeCount = 0;
			outCount = 0;
		}
		totalRunsPerSimulation += totalRunsPerGame;
	}

	cout << "Average final score : " << (float) totalRunsPerSimulation / (float) numOfSimulations << " over " << numOfSimulations << " number of simulations" << endl;
	
	system("pause");
    return 0;
}

