#include "LivesComponent.h"
#include "GameObject.h"
#include "Game.h"
#include "DeadObjectMessage.h"
#include "DamageMessage.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

LivesComponent::LivesComponent(GameObject* gob)
	: GameObjectComponent("lives", gob), _livesRemaining(5)
{

}

/******************************************************************************************************************/

LivesComponent::~LivesComponent()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

// Setup function -- called when parent object is initialised (using its own Start method)
void LivesComponent::Start()
{
	// Register for damage event
	_parent->RegisterListener("damage", this);
}

/******************************************************************************************************************/

// Main update function (called every frame)
void LivesComponent::Update(double deltaTime)
{
}

/******************************************************************************************************************/

// Message handler (called when message occurs)
void LivesComponent::OnMessage(Message* msg)
{
  	if (msg->GetMessageType() == "damage")
	{
		DamageMessage* dMsg = (DamageMessage*)msg;
		_livesRemaining-=dMsg->GetDamage();
		if (_livesRemaining <= 0)
		{
			// Send out death message
  			DeadObjectMessage dom(_parent);
			_parent->OnMessage(&dom);
		}
	}
}

/******************************************************************************************************************/

void LivesComponent::SetLives(int lives)
{
	_livesRemaining = lives;
}

/******************************************************************************************************************/

// Shutdown function -- called when parent object is destroyed
void LivesComponent::End()
{
	_parent->UnregisterListener("damage", this);
}

/******************************************************************************************************************/
