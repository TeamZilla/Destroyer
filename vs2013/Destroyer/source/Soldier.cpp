#include <Soldier.hpp>
#include <time.h>
using namespace uth;

Soldier::Soldier(pmath::Vec2 pos, PhysicsWorld* physworld)
{
	m_soldierTime = 2;
	m_soldierScale = 0.5f;
	m_soldierSpeed = 200;
	m_playerSpeed = 0;
	m_isSideChecked = false;
	m_isSoldierHit = false;
	m_isSoldierDestroyed = false;
	m_maxRange = 400;
	m_minRange = 200;
	m_physWorld = physworld;

	m_window = &uthEngine.GetWindow();
	auto tankTexture = uthRS.LoadTexture("Enemies/soldier_running.png");
	tankTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(tankTexture,6,6,1,10));
	transform.SetPosition(pos.x, pos.y);
	transform.SetScale(0.4f);
	AddComponent(new Rigidbody(*m_physWorld));
	m_rigidBody = GetComponent<Rigidbody>("Rigidbody");
	m_rigidBody->SetPosition(pmath::Vec2(pos.x, pos.y));
	m_rigidBody->SetPhysicsGroup(-3);
	//m_rigidBody->SetUnitSize(pmath::Vec2(m_rigidBody->GetSize().x / 2, m_rigidBody->GetSize().y / 2));
	//m_rigidBody->SetSize(pmath::Vec2(m_rigidBody->GetSize().x, m_rigidBody->GetSize().y/4));
	//TODO: scale functions

	WhichSideOfPlayer();
}
Soldier::~Soldier()
{

}
void Soldier::update(float dt)
{
	if (!m_isSoldierHit)
	{
		Movement(dt);
	}
	else
	{
		Fly(dt);
	}
	m_dt = dt;
}

void Soldier::Movement(float dt)
{
	if (!m_isSideChecked)
	{
		m_range = Randomizer::GetInt(m_minRange, m_maxRange);
		m_isSideChecked = true;
	}

	if (m_playerPos.x + m_range <= m_rigidBody->GetPosition().x || m_playerPos.x - m_range >= m_rigidBody->GetPosition().x)
	{
		auto pos = pmath::Vec2(m_rigidBody->GetPosition());
		m_rigidBody->SetPosition(pmath::Vec2(pos.x + (dt*m_soldierSpeed) + 1, pos.y));
		//m_rigidBody->ApplyImpulse(pmath::Vec2(m_tankSpeed, 10));
	}

	//transform.SetScale(Randomizer::GetFloat(m_tankScale - 0.02f, m_tankScale + 0.01f));
}
void Soldier::Fly(float dt)
{
	m_soldierTime -= dt;
	if (m_soldierTime <= 0 &&
		m_rigidBody->GetVelocity().y < 0.2f &&
		m_rigidBody->GetAngularVelocity() < 0.2f)
	{
		m_isSoldierDestroyed = true;
	}
}
bool Soldier::isDestroyed()
{
	return m_isSoldierDestroyed;
}
void Soldier::Hit()
{
	m_rigidBody->ApplyImpulse(pmath::Vec2(Randomizer::GetFloat(-10, 10),      //X direction
							  -Randomizer::GetFloat(5, 15)),			      //Y direction
							  pmath::Vec2(Randomizer::GetFloat(-15, 15), 0)); //offset
	//m_rigidBody->SetPhysicsGroup(3); //Set collision group to positive so it can collide to tanks
	m_isSoldierHit = true;
}
void Soldier::WhichSideOfPlayer()
{
	m_playerPos = pmath::Vec2(m_window->GetSize().x / 2 <= m_rigidBody->GetPosition().x, 0);

	if (m_playerPos.x <= m_rigidBody->GetPosition().x)
	{
		m_isSoldierOnRight = true;
		m_soldierSpeed *= -1;
	}
	else
	{
		m_isSoldierOnRight = false;
		transform.SetScale(transform.GetScale().x * -1, transform.GetScale().y);
	}

}

//void Tank::Draw()
//{
//	GameObject::Draw(uthEngine.GetWindow());
//}