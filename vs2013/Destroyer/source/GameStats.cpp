
#include <GameStats.hpp>

GameStats   GameStats::Instance;
std::string GameStats::SaveFilePath = "testi.txt";

bool GameStats::Load()
{
	uth::FileManager file;

	if (file.OpenFile(SaveFilePath, uth::FileManager::Location::INTERNAL, false))
	{
		file.ReadBytes(&score, 1, sizeof(Score));
		return true; // TODO: Return IO error state, when uth engine supports it.
	}
	else
	{
		ResetSave();
	}

	return false;
}

bool GameStats::Save()
{
	uth::FileManager file;

	if (file.OpenFile(SaveFilePath, uth::FileManager::Location::INTERNAL, true))
	{
		file.WriteBytes(&score, 1, sizeof(Score));
		return true; // TODO: Return IO error state, when uth engine supports it.
	}

	return false;
}

bool GameStats::ResetSave()
{
	return GameStats().Save();
}