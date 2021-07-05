#include "GamePlayScene.h"
#include "SceneManager.h"
#include "Game.h"
#include "RenderSystem.h"
#include "Asteroid.h"
#include "Message.h"
#include "ExplodableComponent.h";
#include "Explosion.h";
#include "GameOverScene.h";
#include "Pike.h"
#include "Warband.h"
#include "Legion.h"

/******************************************************************************************************************/
// Structors
/******************************************************************************************************************/

GamePlayScene::GamePlayScene()
	: _restartCounter(0),
	  _ufoTimer(MAX_UFO_WAIT),
	  _minAsteroids(NUM_ASTEROIDS)
{

}

/******************************************************************************************************************/

GamePlayScene::~GamePlayScene()
{
}

/******************************************************************************************************************/
// Functions
/******************************************************************************************************************/

void GamePlayScene::Initialise()
{
	float _scale = 0.5f;
	float distance = _scale / 10; 
	float x = 0;
	float y = 0;
	float z = 0;
	int warriorNum;
	int playerNum = 1;
	float newX = -1.0f;
	float newY = -1 - distance;
	float offset = 0.05f;

	
	//Create the blocks for player 1
	x = newX;
	y = newY;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		for (int j = 0; j < NUM_WARRIORS; j++)
		{
			for (int k = 0; k < NUM_WARRIORS; k++)
			{
				warriorNum = rand() % 3 + 1;

				switch (warriorNum)
				{
				case 1:
				{
					Pike* pike = new Pike(_sceneManager->GetGame()->GetMesh("pike"));
					pike->SetPlayerNum(playerNum);
					pike->SetScale(_scale);
					x += offset;
					pike->SetPos(Vector4(x, y, z, 1));
					pike->SetVelocity(pike->SPEED, 0);
					pike->Reset();
					_gameObjects.push_back(pike);
					break;
				}
				case 2:
				{
					Legion* legion = new Legion(_sceneManager->GetGame()->GetMesh("legion"));
					legion->SetScale(_scale);
					legion->SetPlayerNum(playerNum);
					x += offset;
					legion->SetPos(Vector4(x, y, z, 1));
					legion->SetVelocity(legion->SPEED, 0);
					legion->Reset();
					_gameObjects.push_back(legion);
					break;
				}
				case 3:
				{
					Warband* warband = new Warband(_sceneManager->GetGame()->GetMesh("warband"));
					warband->SetPlayerNum(playerNum);
					warband->SetScale(_scale);
					x += offset;
					warband->SetPos(Vector4(x, y, z, 1));
					warband->SetVelocity(warband->SPEED, 0);
					warband->Reset();
					_gameObjects.push_back(warband);
					break;
				}
				}
			}
			y -= 0.05f;
			x = newX;
		}
		newY += 0.5;
		y = newY;
		x = newX;
	}

	//Create the blocks for player 2
	newX = 0.75f;
	x = newX;
	y = newY;
	playerNum = 2;

	for (int i = 0; i < NUM_BLOCKS; i++)
	{
		for (int j = 0; j < NUM_WARRIORS; j++)
		{
			for (int k = 0; k < NUM_WARRIORS; k++)
			{
				warriorNum = rand() % 3 + 1;

				switch (warriorNum)
				{
				case 1:
				{
					Pike* pike = new Pike(_sceneManager->GetGame()->GetMesh("pike"));
					pike->SetPlayerNum(playerNum);
					pike->SetScale(_scale);
					x += offset;
					pike->SetPos(Vector4(x, y, z, 1));
					pike->SetVelocity(-pike->SPEED, 0);
					pike->Reset();
					_gameObjects.push_back(pike);
					break;
				}
				case 2:
				{
					Legion* legion = new Legion(_sceneManager->GetGame()->GetMesh("legion"));
					legion->SetScale(_scale);
					legion->SetPlayerNum(playerNum);
					x += offset;
					legion->SetPos(Vector4(x, y, z, 1));
					legion->SetVelocity(-legion->SPEED, 0);
					legion->Reset();
					_gameObjects.push_back(legion);
					break;
				}
				case 3:
				{
					Warband* warband = new Warband(_sceneManager->GetGame()->GetMesh("warband"));
					warband->SetPlayerNum(playerNum);
					warband->SetScale(_scale);
					x += offset;
					warband->SetPos(Vector4(x, y, z, 1));
					warband->SetVelocity(-warband->SPEED, 0);
					warband->Reset();
					_gameObjects.push_back(warband);
					break;
				}
				}
			}
			y -= 0.05f;
			x = newX;
		}
		newY += 0.5;
		y = newY;
		x = newX;
	}





	/*
	////////////////
	// Setup Objects
	_ship = new Ship(_sceneManager->GetGame()->GetMesh("ship"));
	_gameObjects.push_back(_ship);

	_ufo = new UFO(_sceneManager->GetGame()->GetMesh("ufo"));
	_gameObjects.push_back(_ufo);
	_ufo->SetAlive(false);

	// Create asteroids
	for (int i = 0; i < NUM_ASTEROIDS; i++)
	{
		Asteroid* asteroid = new Asteroid(_sceneManager->GetGame()->GetMesh("asteroid"));
		asteroid->Reset();
		_gameObjects.push_back(asteroid);
	}
	*/

	// Setup Score Display
	_scoreDisplay = new ScoreDisplay();
	_gameObjects.push_back(_scoreDisplay);


	// Start all objects to set them up
	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		_gameObjects[i]->Start();
	}

}

/******************************************************************************************************************/

void GamePlayScene::OnKeyboard(int key, bool down)
{

	if (down) return; // Ignore key down events

	// Switch key presses
	switch (key)
	{
	case 80: // P = pause
		// Put code here to add a Pause screen
		break;
	case 82: // R
		Reset();
		break;
	case 85: // U
		_ufoTimer = 0;
		break;
	case 27: // Escape
		_sceneManager->PopScene();
		break;
	}
}

/******************************************************************************************************************/

/// Update current scene
void GamePlayScene::Update(double deltaTime)
{
	Scene::Update(deltaTime);

	_physicsSystem.Process(_gameObjects, deltaTime);
	_collisionSystem.Process(_gameObjects, deltaTime);

	// Perform legacy update on game objects (in theory, should be phased out altogether)
	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		if (_gameObjects[i]->IsAlive())
		{
			_gameObjects[i]->Update(deltaTime);
		}
	}

	/*
	// Add more asteroids if we have less than 5
	while (Asteroid::count < _minAsteroids)
	{
		Asteroid* a = new Asteroid(_sceneManager->GetGame()->GetMesh("asteroid"));
		a->Reset();
		_gameObjects.push_back(a);
		Asteroid* b = new Asteroid(_sceneManager->GetGame()->GetMesh("asteroid"));
		b->Reset();
		_gameObjects.push_back(b);		
		_minAsteroids++;
	}

	// Handle UFO
	if (_ufoTimer < 0 && _ufo->IsAlive() == false)
	{
		double rnd = rand() * 1.0 / RAND_MAX;
		_ufoTimer = rnd * (MAX_UFO_WAIT - MIN_UFO_WAIT) + MIN_UFO_WAIT;

		_ufo->SetAlive(true);
		_ufo->Reset();
	}
	else if (_ufo->IsAlive() == false)
	{
		_ufoTimer -= deltaTime;
	}

	// Change game state if necessary
	if (!_ship->IsAlive())
	{
		// Ship is dead
		if (ExplodableComponent* ec = (ExplodableComponent*)(_ship->GetComponent("explodable")))
		{
			if (!ec->GetExplosion()->IsAlive() && ec->HasExploded())
			{
				// Dead
				_sceneManager->PopScene();
				_sceneManager->PushScene(new GameOverScene(_scoreDisplay->GetScore()));
			}
		}
	}
	*/
}

/******************************************************************************************************************/

/// Render current scene
void GamePlayScene::Render(RenderSystem* renderer)
{
	glm::mat4 MVM;

	renderer->Process(_gameObjects, 0);
}

/******************************************************************************************************************/

void GamePlayScene::Reset()
{
	int numAsteroidsFound = 0;
	_minAsteroids = NUM_ASTEROIDS;

	for (int i = 0; i < (int)_gameObjects.size(); i++)
	{
		// Delete excess asteroids
		if (_gameObjects[i]->GetType() == "asteroid")
		{
			numAsteroidsFound++;
			if (numAsteroidsFound > _minAsteroids)
			{
				delete _gameObjects[i];
				_gameObjects.erase(_gameObjects.begin() + i);
				i--;
				continue;
			}
		}

		// Reset
		_gameObjects[i]->Reset();
	}

	_ufo->SetAlive(false);
	_ufoTimer = MAX_UFO_WAIT;

}

/******************************************************************************************************************/
