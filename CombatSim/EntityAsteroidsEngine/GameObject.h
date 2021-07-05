#pragma once
#include <map>
#include <vector>
#include "Vector4.h"
#include "MathsHelper.h"


// Forward references
class GameObjectComponent;
class Message;


// Typedefs
typedef std::map<std::string, GameObjectComponent*> ComponentMap;
typedef std::map<std::string, GameObjectComponent*>::iterator ComponentMapIterator;
typedef std::map<std::string, std::vector<GameObjectComponent*> > MessageListenerMap;
typedef std::map<std::string, std::vector<GameObjectComponent*> >::iterator MessageListenerMapIterator;
typedef std::vector<GameObjectComponent*>::iterator ComponentListIterator;


// Now new and improved to use a component-based architecture
class GameObject
{
	// Constants
public:


	// Data
protected:
	std::string			_type;			// Type of the object
	float				_angle;			// Angle of object in degrees
	float				_scale;			// Scale of the object (1 = normal)
	Vector4				_position;		// Position of object's origin
	bool				_alive;			// Alive flag; when false, is not updated
	bool				_deleteFlag;	// Set when you want this game object to be deleted by the game
	int					_playerNum;
	int					_roll;

	// Components
	ComponentMap		_components;

	// Listener registration
	MessageListenerMap	_messageListeners;



	// Constructors
public:
	GameObject(std::string type);
	virtual ~GameObject();

	// Disable copy constructor + assignment operator
private:
	GameObject(const GameObject&);
	GameObject& operator=(const GameObject&);


	// Gets/sets
public:
	float GetAngle()													const	{ return _angle; }
	void SetAngle(float v)														{ _angle = v;  }

	int GetPlayerNum()													const	{ return _playerNum; }
	void SetPlayerNum(int n)													{ _playerNum = n; }

	int GetRoll()														const	{ return _roll; }
	void SetRoll(int r)															{ _roll = r; }


	float GetScale()													const	{ return _scale; }
	void SetScale(float v)														{ _scale = v; }

	Vector4 GetPosition()												const	{ return _position; }
	void SetPosition(Vector4 v)													{ _position = v; }

	bool IsAlive()														const	{ return _alive; }
	void SetAlive(bool v)														{ _alive = v; }

	bool ShouldBeDeleted()												const	{ return _deleteFlag; }
	void SetDeleteFlag(bool v)													{ _deleteFlag = v; }

	std::string GetType()												const	{ return _type; }

	// Component Functions
public:
	bool AddComponent(GameObjectComponent* goc)									;
	bool RemoveComponent(GameObjectComponent* goc)								;
	bool RemoveComponent(std::string componentType)								;
	GameObjectComponent* GetComponent(std::string type)							;

	void RegisterListener(std::string msg, GameObjectComponent* goc)			;
	void UnregisterListener(std::string msg, GameObjectComponent* goc)			;


	// General Functions
public:
	// Setup function -- called to initialise object and its components. Should only be called once
	virtual void Start();

	// Main update function (called every frame)
	virtual void Update(double deltaTime);

	// Message handler (called when message occurs)
	virtual void OnMessage(Message* msg);

	// Shutdown function -- called when object is destroyed (i.e., from destructor)
	virtual void End();

	// Resets the game object to the start state (similar to Start(), but may be called more than once)
	virtual void Reset();
};

