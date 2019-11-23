#pragma once
#include "BaseEventData.h"

typedef unsigned long EventType;

class EvtData_On_Mouse_Click :public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<EvtData_On_Mouse_Click> OnMouseClickPtr;
	explicit EvtData_On_Mouse_Click() {}

	virtual const EventType& VGetEventType(void) const {
		return sk_EventType;
	}

	virtual IEventDataPtr VCopy(void) const {
		return IEventDataPtr(OnMouseClickPtr);
	}

	virtual const char* GetName(void) const {
		return "EvtData_On_Mouse_Click";
	}
};

