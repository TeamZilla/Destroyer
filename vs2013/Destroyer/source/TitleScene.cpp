#include <TitleScene.hpp>

using namespace uth;

uth::Layer& TitleScene::getLayer(LayerId id)
{
	return *m_layers[id];
}
TitleScene::TitleScene()
{}
TitleScene::~TitleScene()
{}
void TitleScene::Update(float dt)
{}
bool TitleScene::Init()
{
	return true;
}
bool TitleScene::DeInit()
{
	return true;
}

