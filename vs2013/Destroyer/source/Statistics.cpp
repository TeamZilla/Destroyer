#include <Statistics.hpp>

using namespace uth;

float Statistics::player_hp			= 0;
float Statistics::player_speed		= 0;
float Statistics::game_score		= 0;
float Statistics::game_highscore	= 0;
float Statistics::game_seconds		= 0;
int   Statistics::game_TankKills	= 0;
int   Statistics::game_SoldKills	= 0;
int   Statistics::game_HeliKills	= 0;
int   Statistics::game_AeroKills	= 0;
std::string Statistics::save_data	= "";

void Statistics::Init()
{
	if (LoadStats)
	{
		//TODO:: set score and kills score to own variables
	}
	else
	{
		
	}
}
void Statistics::DeInit()
{

}
bool Statistics::SaveStats()
{
	FileManager fs;
	fs.OpenFile("testi.txt", FileManager::Location::ASSET, true);
	fs.WriteString("Testi.");
	fs.CloseFile();
	return true;
}
bool Statistics::LoadStats()
{
	FileManager fs;
	fs.OpenFile("testi.txt", FileManager::Location::ASSET, true);
	save_data = fs.ReadText();
	fs.CloseFile();
	return true;
}
bool Statistics::ResetSaveFile()
{
	game_score = 0;
	game_highscore = 0;
	game_TankKills = 0;
	game_SoldKills = 0;
	game_HeliKills = 0;
	game_AeroKills = 0;
	if (SaveStats())
		return true;
	return false;
}