#include "FightComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "Pike.h"
#include "Legion.h"
#include "Warband.h"
#include "DeadObjectMessage.h"
#include "DamageMessage.h"

FightComponent::FightComponent(GameObject* gob)
	: GameObjectComponent("fight", gob)
{
	pike = new Pike(Game::TheGame->GetMesh("pike"));

	warband = new Warband(Game::TheGame->GetMesh("warband"));
}

FightComponent::~FightComponent()
{
}

void FightComponent::Start()
{

}

void FightComponent::Update(double deltaTime)
{

}

void FightComponent::OnMessage(Message* msg)
{

}


void FightComponent::End()
{

}

bool FightComponent::Win(int roll, int roll2)
{
	if (roll > roll2)
	{
		return true;
	}
	else if(roll < (roll2/2))
	{
		dead = true;
	}
	return false;
}
