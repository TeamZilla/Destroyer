//#include <EnemyFactory.hpp>
//#include <TankBehavior.hpp>
//
//using namespace uth;
//
//std::shared_ptr<GameObject> EnemyFactory::CreateTank()
//{
//	const static float speed(5.0f);
//	const static std::string textureId("Enemies/tank.png");
//	const static pmath::Vec2 CollisionSize(50, 50);
//
//	auto& obj = std::shared_ptr<GameObject>(new GameObject());
//
//	obj->AddTag({ "Tank", "Enemy" });
//	obj->AddComponent(new TankBehavior(speed, m_player));
//	obj->AddComponent(new Sprite(textureId));
//	obj->transform.SetPosition(700, 500);
//	obj->AddComponent(new Rigidbody(*m_physicsWorld, uth::COLLIDER_BOX, CollisionSize));
//	obj->GetComponent<Rigidbody>()->SetPhysicsGroup(-3);
//
//	return m_layer->AddChild(obj);
//
//}