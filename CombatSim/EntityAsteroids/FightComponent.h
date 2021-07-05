#pragma once
#include "GameObjectComponent.h"

class Warband;
class Pike;
class Legion;

class FightComponent
	: public GameObjectComponent
{
	Warband* warband;
	Pike* pike;
	Legion* legion;

public:
	bool dead = false;

public:
	FightComponent(GameObject* gob);
	virtual ~FightComponent();

	// Setup function -- called when parent object is initialised (using its own Start method)
	virtual void Start();

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg);

	// Shutdown function -- called when parent object is destroyed
	virtual void End();

	virtual bool Win(int roll, int roll2);
};

