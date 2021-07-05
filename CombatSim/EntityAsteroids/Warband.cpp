#include "Warband.h"
#include "CollisionMatrix.h"
#include "CollisionMessage.h"
#include "Components.h"
#include "DeadObjectMessage.h"
#include "Game.h"

const float Warband::SPEED = 0.2f;
const int Warband::BASE = 3;

Warband::Warband(Mesh* mesh)
	: GameObject("warband")
{
	PhysicsComponent* pc = new PhysicsComponent(this);

	CollisionComponent* cc = new CollisionComponent(this);
	cc->SetCollisionRadius(mesh->CalculateMaxSize() * 0.9f);
	cc->SetCollisionID(CollisionID::Warband_ID);
	cc->SetCollisionMatrixFlag(CollisionID::Pike_ID);
	cc->SetCollisionMatrixFlag(CollisionID::Warband_ID);
	cc->SetCollisionMatrixFlag(CollisionID::Warband_ID);

	RenderComponent* rc = new RenderComponent(this);
	rc->SetColour(Colour::Red());
	rc->SetMesh(mesh);
	rc->ShouldDraw(true);
}

Warband::~Warband()
{

}

void Warband::Update(double deltaTime)
{
	GameObject::Update(deltaTime);
}

void Warband::OnMessage(Message* msg)
{
	if (msg->GetMessageType() == "dead")
	{
		DeadObjectMessage* dead = (DeadObjectMessage*)msg;

		if (dead->GetDeadObject() == this)
		{
			RenderComponent* rc = (RenderComponent*)GetComponent("render");
			rc->ShouldDraw(false);
			_alive = false;
		}
	}
	else if (msg->GetMessageType() == "collision")
	{
		CollisionMessage* col = (CollisionMessage*)msg;

		if (col->GetCollidee() == this ||
			col->GetCollider() == this)
		{
			if (col->GetOtherCollisionObject(this)->GetPlayerNum() != this->GetPlayerNum())
			{
				GameObject::SetRoll((rand() % 6 + 1) + BASE);

				FightComponent* fight = new FightComponent(this);

				if (!fight->Win(GameObject::GetRoll(), col->GetOtherCollisionObject(this)->GetRoll()) && !fight->dead)
				{
					if (GameObject::GetPlayerNum() == 1 && col->GetOtherCollisionObject(this)->GetType() != "warband")
					{
						Vector4 newPosition = GameObject::GetPosition();
						GameObject::SetPosition(Vector4(newPosition.x() - 0.1f, newPosition.y(), newPosition.z(), newPosition.w()));
					}
					else if (GameObject::GetPlayerNum() == 2 && col->GetOtherCollisionObject(this)->GetType() != "warband")
					{
						Vector4 newPosition = GameObject::GetPosition();
						GameObject::SetPosition(Vector4(newPosition.x() + 0.1f, newPosition.y(), newPosition.z(), newPosition.w()));
					}
					else
					{
						DeadObjectMessage dom(this);
						OnMessage(&dom);
						/*
						DeadObjectMessage* dead = (DeadObjectMessage*)msg;

						if (dead->GetDeadObject() == this)
						{
							RenderComponent* rc = (RenderComponent*)GetComponent("render");
							rc->ShouldDraw(false);
							_alive = false;
						}
						*/
					}
				}
				else if (fight->dead)
				{
					DeadObjectMessage dom(this);
					OnMessage(&dom);
					/*
					DeadObjectMessage* dead = (DeadObjectMessage*)msg;

					if (dead->GetDeadObject() == this)
					{
						RenderComponent* rc = (RenderComponent*)GetComponent("render");
						rc->ShouldDraw(false);
						_alive = false;
					}
					*/
				}
			}
		}
	}
}

void Warband::Reset()
{
	_alive = true;

	RenderComponent* rc = (RenderComponent*)GetComponent("render");
	rc->ShouldDraw(true);

	PhysicsComponent* pc = (PhysicsComponent*)GetComponent("physics");
	pc->SetVelocity(Vector4(xVel, yVel, 0.0f, 0.0f));

	_position = warbandPos;
}

void Warband::Spawn(const Vector4& pos)
{
	warbandPos = pos;

	_position.x(pos.x());
	_position.y(pos.y());

	_alive = true;

	Vector4 vel(xVel, yVel, 0.0f, 0.0f);
	PhysicsComponent* p = (PhysicsComponent*)GetComponent("physics");
	p->SetVelocity(vel);

	RenderComponent* rc = (RenderComponent*)GetComponent("render");
	rc->ShouldDraw(true);
}

int Warband::GetModifiers()
{
	auto GO = Game::TheGame->GetGameObjects();
	int damageIncrease = 0;
	int damageDecrease = 0;
	bool friendLeft = false;
	bool friendRight = false;

	for (auto& go : GO)
	{
		if (go->GetPlayerNum() == this->GetPlayerNum())
		{
			if (Distance(go->GetPosition().x(), this->GetPosition().x()) < 0.15f)
			{
				damageIncrease++;

				if (damageIncrease >= 3)
				{
					damageIncrease = 3;
				}
			}

			if (Distance(go->GetPosition().y(), this->GetPosition().y()) < 0.15f);
			{
				if (!friendLeft)
				{
					friendLeft = true;
				}
				else if (!friendRight)
				{
					friendRight = true;
				}
			}
		}
	}

	if (!friendLeft)
	{
		damageDecrease--;
	}

	if (!friendRight)
	{
		damageDecrease--;
	}

	return damageDecrease + damageIncrease;
}

float Warband::Distance(float a, float b)
{
	return(sqrt(b - a) * (b - a));
}