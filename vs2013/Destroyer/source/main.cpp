#include <UtH/UtHEngine.hpp> //UtHEngine main.

#define NEWSCENEFUNC
#include <Scenes.hpp>


// Basic computer main loop.
// Android version is hidden at UtHEngine/android/jni/main.cpp


int main()
{

	uthSceneM.registerNewSceneFunc(NewSceneFunc, COUNT);

	uthEngine.Init();
#if _DEBUG
		  
		uthSceneM.GoToScene(TITLE);
#endif
	while (uthEngine.Running())
	{

		uthEngine.Update();
		uthEngine.Draw();
	}

	return 0;
}