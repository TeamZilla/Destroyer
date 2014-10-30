#include <BackgroundManager.hpp>
#include <Player.hpp>

using namespace uth;

BackgroundManager::BackgroundManager(float bY, float fY, float mY)
{

}
bool BackgroundManager::Init(uth::Layer& bg, uth::Layer& fg)
{
	m_cameraPan = 0;
	m_cameraPanMax = 300;
	m_cameraPanSpd = 5;
	m_isCameraTurning = false;
	backG = &bg;
	backF = &fg;

	// Background
	GameObject* temp;
	//Mountains
	backG->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "mountain1" }));
	temp->AddComponent(new Background(0.02,
		uthEngine.GetWindow().GetSize().y - 570, 0.5, true,
		"backgrounds/mountains01.png"));
	backG->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "mountain2" }));
	temp->AddComponent(new Background(0.02,
		uthEngine.GetWindow().GetSize().y - 570, 0.5, false,
		"backgrounds/mountains02.png"));

	//Backcity
	backG->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "building1" }));
	temp->AddComponent(new Background(50,
		uthEngine.GetWindow().GetSize().y - 470, 2,true, 
		"backgrounds/buildings02.png"));
	backG->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "building2" }));
	temp->AddComponent(new Background(50,
		uthEngine.GetWindow().GetSize().y - 470, 2, false,
		"backgrounds/buildings02.png"));

	//Frontcity
	backF->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "lantern1" }));
	temp->AddComponent(new Background(100,
		uthEngine.GetWindow().GetSize().y - 220, 4, true,
		"backgrounds/lanterns.png"));
	backF->AddChild(temp = new GameObject(std::vector<std::string>{ "bg", "lantern2" }));
	temp->AddComponent(new Background(100,
		uthEngine.GetWindow().GetSize().y - 220, 4, false,
		"backgrounds/lanterns.png"));

	
	return true;
}
void BackgroundManager::Update(float dt)
{
	CameraMovement(dt);

	
}
void BackgroundManager::CameraMovement(float dt)
{
	m_camera = &uthEngine.GetWindow().GetCamera();
	m_camera->SetPosition(m_cameraPan, m_cameraStartPos.y);
	if (!m_isCameraTurning)
	{
		m_isCameraTurning = true;
		m_cameraPan = 0;
	}
	//Change direction depending where player is looking
	if (Player::isGoingRight)
	{
		m_cameraPan += dt*m_cameraPanSpd * ((m_cameraStartPos.x + m_cameraPanMax) - m_camera->GetPosition().x);
	}
	else
	{
		m_cameraPan += dt*m_cameraPanSpd * ((m_cameraStartPos.x - m_cameraPanMax) - m_camera->GetPosition().x);
	}
}
void BackgroundManager::SetCameraStartPos(pmath::Vec2 pos)
{
	m_cameraStartPos = pos;
	uthEngine.GetWindow().GetCamera().SetPosition(pos);
}
void BackgroundManager::Shake(float amount, float delay)
{

	auto childrenF = backF->Children("bg");
	auto childrenG = backG->Children("bg");

	//Set amount and delay to backgrounds
	for (auto& e : childrenF)
	{
		auto fg = static_cast<GameObject*>(e.get());
		fg->GetComponent<Background>()->Shake(amount);
	}
	for (auto& e : childrenG)
	{
		auto bg = static_cast<GameObject*>(e.get());
		bg->GetComponent<Background>()->Shake(amount);
	}
}
BackgroundManager::~BackgroundManager()
{
	DeInit();
}

void BackgroundManager::DeInit()
{

}