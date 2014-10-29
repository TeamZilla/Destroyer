#include <Tank.hpp>
#include <time.h>
using namespace uth;

Tank::Tank(pmath::Vec2 pos, PhysicsWorld* physworld)
{
	m_tankTime = 2;
	m_tankScale = 0.5f;
	m_tankSpeed = 200;
	m_playerSpeed = 0;
	m_isSideChecked = false;
	m_isTankHit = false;
	m_isTankDestroyed = false;
	m_maxRange = 400;
	m_minRange = 200;
	m_physWorld = physworld;

	m_window = &uthEngine.GetWindow();
	auto tankTexture = uthRS.LoadTexture("Enemies/tank.png");
	tankTexture->SetSmooth(true);
	AddComponent(new Sprite(tankTexture));
	transform.SetPosition(pos.x, pos.y);
	transform.SetScale(m_tankScale);
	AddComponent(new Rigidbody(*m_physWorld));
	m_rigidBody = GetComponent<Rigidbody>("Rigidbody");
	m_rigidBody->SetPosition(pmath::Vec2(pos.x, pos.y));
	m_rigidBody->SetPhysicsGroup(-3);
	AddTag("Tank"); // Set name tag for object
	//m_rigidBody->SetUnitSize(pmath::Vec2(m_rigidBody->GetSize().x / 2, m_rigidBody->GetSize().y / 2));
	//m_rigidBody->SetSize(pmath::Vec2(m_rigidBody->GetSize().x, m_rigidBody->GetSize().y/4));
	//TODO: scale functions

	WhichSideOfPlayer();
}
Tank::~Tank()
{

}
void Tank::update(float dt)
{
	if (!m_isTankHit)
	{
		Movement(dt);
	}
	else
	{
		Fly(dt);
	}
	m_dt = dt;
}

void Tank::Movement(float dt)
{
	if (!m_isSideChecked)
	{
		m_range = Randomizer::GetInt(m_minRange, m_maxRange);
		m_isSideChecked = true;
	}

	if (m_playerPos.x + m_range <= m_rigidBody->GetPosition().x || m_playerPos.x - m_range >= m_rigidBody->GetPosition().x)
	{
		auto pos = pmath::Vec2(m_rigidBody->GetPosition());
		m_rigidBody->SetPosition(pmath::Vec2(pos.x + (dt*m_tankSpeed) + 1, pos.y));
	}
}
void Tank::Fly(float dt)
{
	m_tankTime -= dt;
	if(m_tankTime <= 0 &&
		m_rigidBody->GetVelocity().y < 0.2f &&
		m_rigidBody->GetAngularVelocity() < 0.2f)
	{
		m_isTankDestroyed = true;
	}
}
bool Tank::isDestroyed()
{
	return m_isTankDestroyed;
}
void Tank::Hit()
{
	m_rigidBody->ApplyImpulse(pmath::Vec2(Randomizer::GetFloat(-20, 20),      //X direction
							 -Randomizer::GetFloat(35, 50)),			      //Y direction
							  pmath::Vec2(Randomizer::GetFloat(-25, 25), 0)); //offset
	//m_rigidBody->SetPhysicsGroup(3); //Set collision group to positive so it can collide to tanks
	m_isTankHit = true;
}
void Tank::WhichSideOfPlayer()
{
	m_playerPos = pmath::Vec2(m_window->GetSize().x / 2 <= m_rigidBody->GetPosition().x, 0);

	if (m_playerPos.x <= m_rigidBody->GetPosition().x)
	{
		m_isTankOnRight = true;
		m_tankSpeed *= -1;
	}
	else
	{
		m_isTankOnRight = false;
		transform.SetScale(transform.GetScale().x * -1, transform.GetScale().y);
	}

}
