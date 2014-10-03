#include <Tank.hpp>

using namespace uth;

Tank::Tank(pmath::Vec2 pos)
{
	auto tankTexture = uthRS.LoadTexture("Enemies/tank.png");
	tankTexture->SetSmooth(true);
	AddComponent(new Sprite(tankTexture));
	transform.SetPosition(500,500);


}
Tank::~Tank()
{

}
void Tank::Update(float dt)
{
	GameObject::Update(dt);

}
void Tank::Draw()
{
	GameObject::Draw(uthEngine.GetWindow());
}