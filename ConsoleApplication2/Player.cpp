#include "stdafx.h"
#include "Player.h"


Player::Player(string name, float battingAvg)
{
	m_battingAvg = battingAvg;
	m_name = name;
}


Player::~Player()
{
}
