#pragma once
#include <string>

enum class Event
{
	SHIP_DESTROYED,
	MISSILE_SHOT
	// Plus tard : on pourrait ajouter d'autres types d'événements
	// à surveiller, ex: RESPAWNED, TELEPORTED, LASER_SHOT, ...
};

namespace obs
{
	class IObserver
	{
	protected:
		IObserver() = default;
	public:
		virtual ~IObserver() = default;
		virtual void notify(Event evt) = 0;
	};

}
