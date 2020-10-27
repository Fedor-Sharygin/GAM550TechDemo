#pragma once

#ifndef _EVMAN_H_
#define _EVMAN_H_

#include "Manager.h"


class Event;
enum class EVENT_TYPE;

class Component;

class EventManager : public Manager
{
public:
	EventManager();
	virtual ~EventManager();

	virtual void Update(float dt) override;
	virtual void FrameStart() override {};
	virtual void FrameEnd() override {};

	virtual void Initialize() override;
	virtual void End() override;

	void Subscribe(Component* nSub, EVENT_TYPE evType);
	void BroadCastEvent(Event* ev);

	template<typename TEvent>
	TEvent* PassEvent()
	{
		/// check if the provided type is a child of Event
		if (false == std::is_base_of<Event, TEvent>::value)
		{
			return nullptr;
		}

		/// otherwise => create the event, push and return it
		/// to store details
		TEvent* nEvent = new TEvent();
		storedEvents.push_back(nEvent);
		return nEvent;
	};
public:
private:
private:
	/// Store all of the events
	std::vector<Event*> storedEvents;

	/// Store the subscriptions
	std::unordered_map<EVENT_TYPE, std::vector<Component*>> subscriptions;
};



#endif

