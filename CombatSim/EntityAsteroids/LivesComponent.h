#pragma once
#include "GameObjectComponent.h"



class LivesComponent
	: public GameObjectComponent
{
	// Data
protected:
	int _livesRemaining;

	// Structors
public:
	LivesComponent(GameObject* gob);
	virtual ~LivesComponent();

	// Gets/Sets
public:
	void SetLives(int lives);

	// Functions
public:

	// Setup function -- called when parent object is initialised (using its own Start method)
	virtual void Start();

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg);

	// Shutdown function -- called when parent object is destroyed
	virtual void End();
};