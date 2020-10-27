#pragma once

#ifndef _CONTEV_H_
#define _CONTEV_H_

#include "Event.h"


class Contact;

class ContactEvent : public Event
{
public:
	ContactEvent();
	virtual ~ContactEvent();
public:
	/// Store the contact
	Contact* passedContact;
private:
private:
};


#endif

