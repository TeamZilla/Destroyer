
#include <GameStats.hpp>

GameStats   GameStats::Instance;
std::string GameStats::SaveFilePath = "testi.txt";

bool GameStats::Load()
{
	uth::FileManager fm;
	fm.OpenFile(SaveFilePath, uth::FileManager::Location::ASSET, false);
	fm.ReadBytes(&game, 1, sizeof(GameStats::Game));
	return true;
}

bool GameStats::Save()
{
	uth::FileManager fm;
	fm.OpenFile(SaveFilePath, uth::FileManager::Location::ASSET, true);
	fm.WriteBinary(BINARY_DATA((void*)&game, sizeof(GameStats::Game)));
	return true;
}

bool GameStats::ResetSave()
{
	return GameStats().Save();
}
