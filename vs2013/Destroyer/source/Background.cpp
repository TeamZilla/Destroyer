#include <Background.hpp>

using namespace uth;

Background::Background(uth::Texture* tex)
{
	tex->SetSmooth(true);
	AddComponent(new Sprite(tex));
	transform.SetOrigin(uth::Origin::TopLeft);
}

Background::~Background()
{
}
//void Background::Draw()
//{
//	GameObject::Draw(uthEngine.GetWindow());
//}