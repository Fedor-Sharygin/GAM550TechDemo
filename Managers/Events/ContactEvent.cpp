#include "pch.h"
#include "ContactEvent.h"

#include "..//CollisionManager.h"



ContactEvent::ContactEvent()
	:
	Event(EVENT_TYPE::TYPE_CONTACT)
{
	passedContact = nullptr;
}

ContactEvent::~ContactEvent()
{
	/// we can delete it, because this
	/// is the only class that has direct
	/// access to it
	/// after the handling => delete the event
	delete passedContact;
}

