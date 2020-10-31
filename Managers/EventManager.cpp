#include "pch.h"
#include "EventManager.h"

#include "Events//Events.h"

#include "..//Objects//Components//Components.h"


EventManager::EventManager()
	:
	Manager(MANAGER_TYPE::TYPE_EVENT_MANAGER)
{
	Initialize();
}

EventManager::~EventManager()
{
	End();
}


void EventManager::Update(float dt)
{
	auto curEv = storedEvents.begin();
	while (storedEvents.end() != curEv)
	{
		/// update the event time
		(*curEv)->timeLeft -= dt;

		/// if the time is less than 0
		/// => broadcast it and delete it
		if ((*curEv)->timeLeft < 0.0f)
		{
			this->BroadCastEvent(*curEv);
			curEv = storedEvents.erase(curEv);
		}
		else
		{
			++curEv;
		}
	}
}


void EventManager::Initialize()
{
	storedEvents = std::vector<Event*>();
	subscriptions = std::unordered_map<EVENT_TYPE, std::vector<Component*>>();
}

void EventManager::End()
{
	for (auto& leftOverEvent : storedEvents)
	{
		delete leftOverEvent;
	}
	storedEvents.clear();

	/// DO NOT (!!!) delete subscribers
	/// they are deleted by their gameobjects
	for (auto& [_, subGroup] : subscriptions)
	{
		subGroup.clear();
	}
	subscriptions.clear();
}


void EventManager::Subscribe(Component* nSub, EVENT_TYPE evType)
{
	/// if the passed event type is default
	/// no subscription is required
	/// since no default events exist
	if (EVENT_TYPE::TYPE_DEFAULT != evType)
	{
		subscriptions[evType].push_back(nSub);
	}
}

void EventManager::BroadCastEvent(Event* ev)
{
	for (auto& sub : subscriptions[ev->evType])
	{
		sub->HandleEvent(ev);
	}
}

