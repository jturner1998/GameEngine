#pragma once
#include "GameObject.h"
#include <stdlib.h>


#pragma once
#include "GameObject.h"
#include <stdlib.h>

class Mesh;

class Warband :
	public GameObject
{
protected:
	float xVel = 0;
	float yVel = 0;
	Vector4 warbandPos;

public:
	static const float SPEED;
	static const int BASE;

public:
	Warband(Mesh* mesh);
	virtual ~Warband();

public:
	virtual void SetVelocity(float x, float y) { xVel = x; yVel = y; }

	virtual void SetPos(Vector4 pos) { warbandPos = pos; }

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg);

	// Reset the asteroid to a random velocity somewhere along the edge
	virtual void Reset();

	virtual void Spawn(const Vector4& pos);

	virtual void SetPlayer(int playerNum) { GameObject::SetPlayerNum(playerNum); }

	virtual int GetModifiers();

	virtual float Distance(float a, float b);
};

