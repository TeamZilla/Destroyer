#include <TankBullet.hpp>
#include <ExplosionEmitter.hpp>
using namespace uth;

TankBullet::TankBullet(Player* player, pmath::Vec2 position) :
m_player(player),
m_target(player->transform.GetPosition())
{
	transform.SetPosition(position);
	Init();
}
TankBullet::~TankBullet()
{

}
void TankBullet::Init()
{
	auto tankBulletTex = uthRS.LoadTexture("Enemies/Projectiles/copter_missile.png");
	tankBulletTex->SetSmooth(true);
	AddComponent(new Sprite(tankBulletTex));

	//TEST
	auto pos = transform.GetPosition();
	m_direction = (m_target - pos).normalize();
	if (m_direction.x < 0)
	{
		transform.SetScale(pmath::Vec2(0.5, 0.5));
	}
	else
	{
		transform.SetScale(pmath::Vec2(-0.5, -0.5));
	}
	transform.SetRotation(180*atan(m_direction.y / m_direction.x)/pmath::pi);

	m_dmg = 3;

}
void TankBullet::update(float m_dt)
{
	m_speed = 900 * m_dt;
	transform.SetPosition(transform.GetPosition() + m_speed*m_direction);
	hitCheck();
}

void TankBullet::hitCheck()
{
	if ((pmath::Vec2(0, 360) - transform.GetPosition()).length() <= 140)
	{
		m_player->Hit(m_player->CheckIfGoingRight() == (m_direction.x < 0 ? true : false) ? m_dmg : m_dmg / 3);
		ExplosionEmitter::Emit(transform.GetPosition());
		Parent()->RemoveChild(this);
	}
}