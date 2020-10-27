#pragma once

#ifndef _EVENT_H_
#define _EVENT_H_


enum class EVENT_TYPE
{
	TYPE_CONTACT,
	TYPE_DEFAULT
};

class Event
{
public:
	Event(EVENT_TYPE nType);
	virtual ~Event() {};
public:
	/// Store the event type for handlers
	EVENT_TYPE evType;

	/// Store when the event must be passed
	float timeLeft;
private:
private:
};


#endif

