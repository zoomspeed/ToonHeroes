#include "FirstStageScene.h"
#include "InGameInterface.h"
#include "Core.h"

Scene* FirstStageScene::createScene()
{
	Scene* pScene = Scene::create();
	FirstStageScene* mainLayer = FirstStageScene::create();
	InGameInterface* InterfaceLayer = InGameInterface::create();
	pScene->addChild(mainLayer);
	pScene->addChild(InterfaceLayer);
	
	return pScene;
}

bool FirstStageScene::init()
{
	if( !Layer::init() ) return false;

	m_fMoveSpeed = 300.0f;
	Core::sharedManager()->m_fOriginX = 0.f; // 스크롤 기준 좌표

	// 뒷 배경
	m_pBackGround = new Object_BackGround;
	m_pBackGround->init();
	m_pBackGround->setPosition(Point(0, 0));
	this->addChild(m_pBackGround);

	// 타워
	Core::sharedManager()->TM.setScene(this);

	// 동료 객체
	Core::sharedManager()->AM.setScene(this);

	this->schedule(schedule_selector(FirstStageScene::tick));

	return true;
}

void FirstStageScene::tick(float _dt)
{
	 Point layerPos = this->getPosition();

	if (GetAsyncKeyState(VK_RIGHT) && Core::sharedManager()->m_fOriginX >= -1024.f)
	{
		layerPos.x -= m_fMoveSpeed * _dt;
		Core::sharedManager()->m_fOriginX -= m_fMoveSpeed * _dt;
	}

	if (GetAsyncKeyState(VK_LEFT) && Core::sharedManager()->m_fOriginX < 0.f)
	{
		layerPos.x += m_fMoveSpeed * _dt;
		Core::sharedManager()->m_fOriginX += m_fMoveSpeed * _dt;
	}

	if (GetAsyncKeyState('A') && Core::sharedManager()->isKeyDown == false) // 테스트 A누르면 칼든 동료 소환
	{
		Core::sharedManager()->isKeyDown = true;
		Core::sharedManager()->AM.createSwordAlliance();
	}
	else if (!GetAsyncKeyState('A'))
	{
		Core::sharedManager()->isKeyDown = false;
	}

	Core::sharedManager()->AM.action(_dt);

	this->setPosition(layerPos);
}