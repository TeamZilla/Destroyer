#ifndef SCENES_H
#define SCENES_H
#define UTHDefaultScene -1

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	GAME,TITLE,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include <GameScene.hpp>//main game 
#include <TitleScene.hpp>//titleScreen

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case GAME:		return new /*Game*/GameScene();
	case TITLE:		return new /*Game*/TitleScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC