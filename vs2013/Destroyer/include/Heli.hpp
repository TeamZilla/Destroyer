#pragma once

#include <vector>
#include <Missile.hpp>
#include <Player.hpp>
#include <UtH/UtHEngine.hpp>

class Heli : public uth::GameObject
{
public:
	Heli();
	Heli(pmath::Vec2f givenPos, Player* player);
	Heli(float);
	~Heli();

	void update(float) override;
	//void Draw();
	void SetNextPos(pmath::Vec2f);
	void SetShootTarget(pmath::Vec2f);
	void SetMisCD_min(float);
	void SetMisCD_max(float);
	void SetLinearSpeed(float);
	void SetHoverSpeed(float);
	bool isDestroyed();
	//Taking damage and dying
	void takeDamage(int amount);

private:
	int m_health;

	void Hover();						// the function that makes random-like movement
	void Pilot();						// is the fuction that's called in each update loop.

	//uth::Sound* m_heliSound;

	// Hovering
	pmath::Vec2f m_hoverScale;
	float m_hoverSpeed;
	float m_hoverTime;					// howerDisplacement is a function of m_hoverTime
	pmath::Vec2f m_hoverDisplacement;	// the difference of curPos and exact position
	Player* m_player;
	
	
	//linear move	
	void LinearMove();					// calculates linear progression between each update
	void Navigate(pmath::Vec2f targ);	// called when there's a new place to go to.
	
	bool isMoving;
	float m_linearSpeed;				// m_linearSpeed in linear movement
	float m_pathLenght;					// lenght of path. Changed only in m_navigate()
	pmath::Vec2f m_moveDir;				// direction for linear move
	pmath::Vec2f m_curPos;				// the current hovering origin. NOT SAME AS this->transfor.GetPos()
	pmath::Vec2f m_nextPos;				// is the given target destination in m_navigate()
	pmath::Vec2f m_prevPos;				//the position at the moment new destination is given.
	float m_dt;
	float m_hoverRatio;
	float m_hoverMaxTime;

	//shooting
	bool isRight;
	bool isShooting;
	bool isCool;
	float m_missileCooldownTimer;
	float m_missileCD_min;
	float m_missileCD_max;

	//std::vector <Missile*> m_missiles;
	void m_shooter();
	void m_launch();
	void burst();
	void m_reload();
	int m_missileClip;
	float m_missileCount;
	float m_missileRegenTimer;
	float m_missileRegenTime;
	float m_shootDelay;
	float burstTimer;
	Missile *m_missile;
	pmath::Vec2f m_shootingTarget;
	float bonVoyageTimer;


};
