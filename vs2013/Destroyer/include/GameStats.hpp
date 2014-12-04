#pragma once

#include <UtH/UtHEngine.hpp>

struct GameStats
{
	static GameStats Instance;
	static std::string SaveFilePath;

	struct Player
	{
		//Functions what we update to keep track of game
		float maxHp = 1;
		float hp = maxHp;
		float speed;
	} player;

	struct Game
	{
		//Functions what we update to keep track of game
		float highscore = 0;
		
		//Enemy kill counts
		size_t tankKills = 0;
		size_t soldKills = 0;
		size_t heliKills = 0;
		size_t aeroKills = 0;
	} game;

	struct Music
	{	
		uth::Sound* music_maingame;
		uth::Sound* music_warning;
		uth::Sound* music_gameOver;
		uth::Sound* music_afterMath;
	} music;

	GameStats() = default;
	bool Load();
	bool Save();

	static bool ResetSave();
};

#ifndef Statistics 
#define Statistics GameStats::Instance
#endif
