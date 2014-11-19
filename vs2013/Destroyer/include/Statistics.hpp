#pragma once

#include <UtH/UtHEngine.hpp>

class Statistics
{
	Statistics() = delete;
	~Statistics() = delete;
public:
	//Functions to load and save stats to file
	static void  Init();
	static void  DeInit();
	static bool  SaveStats();
	static bool  LoadStats();
	static bool  ResetSaveFile();
	//Functions what we update to keep track of game
	static float player_hp;
	static float player_speed;
	static float game_score;
	static float game_highscore;
	static float game_seconds;
	//Enemy kill counts
	static int game_TankKills;
	static int game_SoldKills;
	static int game_HeliKills;
	static int game_AeroKills;


};