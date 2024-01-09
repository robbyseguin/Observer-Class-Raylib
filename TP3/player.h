#pragma once

#include "entity.h"
#include "inputs.h"
#include "titlemanager.h"
#include "background.h"
#include <string>

// The player's spaceship. Moves with velocity and rotation as given by
// inputs. Can shoot Missiles and die when hit by Missiles from other Players.
class Player: public Entity 
{
	// References
	EntityList & _entities;

	using ObserverList = std::vector<obs::IObserver*>;
	using ObserverIt = ObserverList::iterator;
	std::vector<obs::IObserver*> observers_;

    // TODO: Le player ne devrait PAS connaître les objets qui
    // l'observent... À changer pour un pattern d'*Observer*
    

	// General Variables
	float _vx, _vy;
	float _turnSpeed, _linearAcceleration;
	float _maxSpeed;
	int _playerNum;
	float _angle;
	float _missileCooldown;
	float _laserCooldown;
	bool _alive;
	float _timeAlive;
	float _invincibleTime;
	bool _hasFired;

	// Helper Functions
	void spawnExplosion() const;
	void invoke(Event event);
public:

	Player(float x, float y, int player_num, int screen_w, int screen_h,
		   EntityList & entities, float invincible_time=3.0f);
	void shootMissile();
	void shootLaser();
	void update(float delta) override;
	void render(Resources* resources, float delta) override;
	void handleInputs(float delta, Inputs& inputs);
	bool isAlive() override;
    int getId() override;
    bool collides() override;
	bool doesCollide(int id) override;
    void collideEntity(Entity& entity) override;
	int getPlayerNum() const;
	void addObserver(obs::IObserver* obs);
	void remove(obs::IObserver* remove);
};
