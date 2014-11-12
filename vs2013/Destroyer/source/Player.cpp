#include <Player.hpp>

using namespace uth;

bool Player::isGoingRight = true;

Player::Player(uth::PhysicsWorld* physworld)
{
	m_speed = 0;
	m_maxSpeed = 400;
	m_minSpeed = -400;
	m_acceleration = 750;
	m_jumpSpeed = 0;
	m_jumpHeight = 8;
	m_jumpTimer = 0;
	m_tailTimer = 0;
	isGoingRight = true;
	m_isJumping = false;
	m_isCrouching = false;
	m_isTurning = false;

	//Create, set position and scale player Sprite
	auto playerTexture = uthRS.LoadTexture("modzilla/moz_animation.png");
	playerTexture->SetSmooth(true);
	AddComponent(new AnimatedSprite(playerTexture,24,8,3));
	transform.SetOrigin(uth::Origin::BottomCenter);
	transform.SetScale(1.5f);
	transform.SetPosition(pmath::Vec2f(0,
		uthEngine.GetWindow().GetSize().y -
		transform.GetSize().y/4));

	//Set walking animation and other animations
	m_walkAnim  =  pmath::Vec4(16, 8, 16, 10);
	m_stompAnim =  pmath::Vec4(0, 3, 0, 4);
	m_jumpAnim  =  pmath::Vec4(8, 6, 8, 7);
	m_tailAnim  =  pmath::Vec4(3, 3, 3, 6);
	playerAnimation = GetComponent<AnimatedSprite>("AnimatedSprite");
	SetAnimation(m_walkAnim);
	
	//Create body hitbox for player (player wont need own rigidbody)
	m_bodyBox = new GameObject();
	m_bodyBox->AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 0),
		pmath::Vec2(transform.GetSize().x/2.2f, transform.GetSize().y / 1.5f)));
	m_bodyBox->transform.SetPosition(0, 30);
	m_bodyBox->AddComponent(new Rigidbody(*physworld));
	m_bodyBox->GetComponent<Rigidbody>()->SetKinematic(true);
	m_bodyBox->GetComponent<Rigidbody>()->SetPhysicsGroup(-2);
	m_bodyBox->AddTag("PlayerBodyCollider");
	AddChild(m_bodyBox);

	//Create head hitbox for player
	m_headBox = new GameObject();
	m_headBox->AddComponent(new Sprite(pmath::Vec4(0, 1, 0, 0),
		pmath::Vec2(transform.GetSize().x/2.4f, transform.GetSize().y/4)));
	m_headBox->transform.SetPosition(transform.GetSize().x / 3.6f, -80);
	m_headBox->AddComponent(new Rigidbody(*physworld));
	m_headBox->GetComponent<Rigidbody>()->SetKinematic(true);
	m_headBox->GetComponent<Rigidbody>()->SetPhysicsGroup(-2);
	m_headBox->AddTag("PlayerHeadCollider");

	AddChild(m_headBox);


}

void Player::init()
{
}
void Player::update(float dt)
{
	m_dt = dt;
	Acceleration();
	if (m_isJumping)
	{
		Jumping();
	}
	else if (m_isCrouching)
	{
		Crouching();
	}
	else if (m_isTurning)
	{
		Turning();
	}
}
void Player::ChangeDirection()
{
	if (!m_isJumping && !m_isCrouching && !m_isTurning)
	{
		m_isTurning = true;
		m_tailTimer = 0.33f;
		SetAnimation(m_tailAnim);
	}
}

void Player::Turning()
{
	m_tailTimer -= m_dt;

	if (m_tailTimer < 0)
	{
		//Flip player sprite to create illusion that player turns
		transform.SetScale(transform.GetScale().x*-1, transform.GetScale().y);
		//Speed reduced to minspeed
		m_speed = m_minSpeed;
		//Change bool value to check is player going right or not
		isGoingRight = !isGoingRight;
		SetAnimation(m_walkAnim);
		m_isTurning = false;
	}
}

//Player jump
void Player::Jump()
{   //This is called once, changes variables to be ready to jump
	if (!m_isJumping && !m_isCrouching && !m_isTurning)
	{
		m_tempPos = transform.GetPosition();
		m_isJumping = true;
		m_jumpSpeed = m_jumpHeight;
		m_jumpTimer = 0.2;
		SetAnimation(m_jumpAnim);
	}
}
void Player::Jumping()
{   //After 
	m_jumpTimer -= m_dt;
	if (m_jumpTimer <= 0)
	{
		m_jumpSpeed -= m_dt * 30;
		transform.Move(0, -m_jumpSpeed);
		if (transform.GetPosition().y >= m_tempPos.y)
		{
			transform.SetPosition(m_tempPos);
			SetAnimation(m_walkAnim);
			m_isJumping = false;
		}
	}
}
void Player::Crouch()
{
	if (!m_isJumping && !m_isCrouching && !m_isTurning)
	{
		m_tempPos = transform.GetPosition();
		m_isCrouching = true;
		m_jumpSpeed = 4;
		m_crouchTimer = 0;
		SetAnimation(m_stompAnim,false);
	}
}
void Player::Crouching()
{
	m_jumpSpeed -= m_dt * 20;
	m_crouchTimer += m_dt;
	transform.Move(0, -m_jumpSpeed);
	if (transform.GetPosition().y >= m_tempPos.y)
	{
		transform.SetPosition(m_tempPos);
	}
	if (m_crouchTimer >= 1)
	{
		SetAnimation(m_walkAnim);
		m_isCrouching = false;
	}

}
void Player::Acceleration()
{
	if (m_maxSpeed > m_speed)
	{
		m_speed += m_dt*m_acceleration;
	}
	else
	{
		m_speed = m_maxSpeed;
	}
}
// Get player speed
float Player::getSpeed()
{
	return m_speed;
}
// Get player direction
bool  Player::CheckIfGoingRight()
{
	return isGoingRight;
}
void Player::SetAnimation(pmath::Vec4 anim, bool loop)
{
	playerAnimation->ChangeAnimation(anim.x, anim.y, anim.z, anim.w, loop);
}
// Deconstructor
Player::~Player()
{
}