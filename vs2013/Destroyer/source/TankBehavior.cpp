//#include <TankBehavior.hpp>

//using namespace uth;
//
//TankBehavior::TankBehavior(float speed, uth::GameObject* player) :
//m_speed(speed),
//m_player(player)
//{
//	m_rigidBody = parent->GetComponent<uth::Rigidbody>();
//}
//TankBehavior::~TankBehavior()
//{
//
//}
//void TankBehavior::Update(float dt) 
//{
//	//auto& rbody = *parent->GetComponent<uth::Rigidbody>();
//	const auto& from = parent->transform.GetPosition();
//	const auto& to = m_player->transform.GetPosition();
//
//	auto& direction = (to - from).normalize();
//
//	m_rigidBody->SetVelocity(direction * m_speed);
//
//}
//void TankBehavior::Hit()
//{
//	m_rigidBody->ApplyImpulse(pmath::Vec2(Randomizer::GetFloat(-20, 20),     //X direction
//							 -Randomizer::GetFloat(50, 70)),				 //Y direction
//							 pmath::Vec2(Randomizer::GetFloat(-25, 25), 0)); //offset
//}