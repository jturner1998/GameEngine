#include "UFO.h"
#include "CollisionMatrix.h"
#include "CollisionMessage.h"
#include "LivesComponent.h"
#include "Components.h"
#include "DeadObjectMessage.h"
#include "DamageMessage.h"
#include "Game.h"
#include "Missile.h"

const float UFO::MAX_SPEED = 0.25f;
const float UFO::FIRE_DELAY = 3.00f;

/******************************************************************************************************************/

UFO::UFO(Mesh* mesh)
	: GameObject("UFO")
{
	// Create components for UFO (they will add themselves)
	new PhysicsComponent(this);
	new ExplodableComponent(this);

	// TODO: Add LivesComponent here
	new LivesComponent(this);

	CollisionComponent* cc = new CollisionComponent(this);
	cc->SetCollisionRadius(mesh->CalculateMaxSize() * 0.9f);
	cc->SetCollisionID(CollisionID::UFO_ID);
	cc->SetCollisionMatrixFlag(CollisionID::Ship_ID);
	cc->SetCollisionMatrixFlag(CollisionID::Bullet_ID);

	RenderComponent* rc = new RenderComponent(this);
	rc->SetMesh(mesh);
	rc->ShouldDraw(false);

	_alive = false;
}

/******************************************************************************************************************/

UFO::~UFO()
{
}

/******************************************************************************************************************/

void UFO::Update(double deltaTime)
{
	GameObject::Update(deltaTime);

	_fireTimer -= deltaTime;
	if (_fireTimer < 0)
	{
		_fireTimer = FIRE_DELAY;

		// Fire a missile
		Missile* missile = new Missile(Game::TheGame->GetMesh("missile"));
		missile->SetValidTargetType("ship");
		missile->Spawn(_position);
		Game::TheGame->AddGameObject(missile);
	}
}

/******************************************************************************************************************/

void UFO::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "collision")
	{
		CollisionMessage* col = (CollisionMessage*)msg;
		if (col->GetCollidee() == this ||
			col->GetCollider() == this)
		{
			// TODO: Send out a damage message instead of death message; increase score when the lives 
			// reach 0 instead (inside the LivesComponent)
			DamageMessage msg(this, 1);	// damage of 1
			OnMessage(&msg);

			//DeadObjectMessage msg(this);
			//OnMessage(&msg);

			// Send increase score message
			//if (col->GetOtherCollisionObject(this)->GetType() == "bullet")
			//{
			//	Message msg("scoreUp");
			//	Game::TheGame->BroadcastMessage(&msg);
			//}
		}
	}
	else if (msg->GetMessageType() == "dead")
	{
  	 	DeadObjectMessage* dom = (DeadObjectMessage*)msg;
		if (dom->GetDeadObject() == this)
		{
			RenderComponent* rc = (RenderComponent*)GetComponent("render");
			rc->ShouldDraw(false);
			_alive = false;

			Message msg("scoreUp");
			Game::TheGame->BroadcastMessage(&msg);
		}
	}

	GameObject::OnMessage(msg);
}

/******************************************************************************************************************/

void UFO::Reset()
{
	_alive = true;
	_fireTimer = FIRE_DELAY;

	RenderComponent* rc = (RenderComponent*)GetComponent("render");
	rc->ShouldDraw(true);

	PhysicsComponent* pc = (PhysicsComponent*)GetComponent("physics");

	double rnd = rand() * 1.0f / RAND_MAX;

	if (rnd < 0.25)
	{
		_position = Vector4(0.99f, 0.75f, 0.0f, 1.0f);
		pc->SetVelocity(Vector4(-MAX_SPEED, 0.0f, 0.0f, 0.0f));
	}
	else if (rnd < 0.5)
	{
		_position = Vector4(0.99f, -0.75f, 0.0f, 1.0f);
		pc->SetVelocity(Vector4(-MAX_SPEED, 0.0f, 0.0f, 0.0f));
	}
	else if (rnd < 0.75)
	{
		_position = Vector4(-0.99f, 0.75f, 0.0f, 1.0f);
		pc->SetVelocity(Vector4(MAX_SPEED, 0.0f, 0.0f, 0.0f));
	}
	else
	{
		_position = Vector4(-0.99f, -0.75f, 0.0f, 1.0f);
		pc->SetVelocity(Vector4(MAX_SPEED, 0.0f, 0.0f, 0.0f));
	}

	LivesComponent* lc = (LivesComponent*)GetComponent("lives");
	if (lc)
	{
		// TODO: Reset the lives component here
		lc->SetLives(5);
	}
}

/******************************************************************************************************************/
