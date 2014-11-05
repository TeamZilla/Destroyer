#include <EnemyFactory.hpp>
#include <TankBehavior.hpp>

using namespace uth;

uth::Layer*			EnemyFactory::m_layer;
uth::PhysicsWorld*	EnemyFactory::m_physicsWorld;
Player*				EnemyFactory::m_player;

std::shared_ptr<GameObject> EnemyFactory::CreateTank()
{
	const static float speed(10.0f);
	const static std::string textureId("Enemies/tank.png");
	const static pmath::Vec2 CollisionSize(50, 50);

	auto& obj = std::shared_ptr<GameObject>(new GameObject());

	obj->AddTags({ "Tank", "Enemy" });
	obj->AddComponent(new Sprite(textureId));
	obj->transform.SetPosition(700, 500);
	obj->transform.SetScale(0.5f);
	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
	obj->GetComponent<Rigidbody>()->SetFriction(0);
	obj->GetComponent<Rigidbody>()->SetPhysicsGroup(-3);
	obj->AddComponent(new TankBehavior(speed, m_player));

	return m_layer->AddChild(obj);

}