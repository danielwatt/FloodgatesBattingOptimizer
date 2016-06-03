#pragma once
#include <string>
using namespace std;
class Player
{
public:
	float m_battingAvg;
	int totalRBI;
	int totalThirdOut;
	string m_name;
	Player(string name, float battingAvg);
	~Player();
};

