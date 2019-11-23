#pragma once
#include "IEventData.h"


class BaseEventData : public IEventData{
	const float m_timeStamp;
public:
	// Consturctor
	explicit BaseEventData(const float timeStamp = 0.0f) 
		:m_timeStamp(timeStamp){}
	// 
	virtual ~BaseEventData(void){}

	// Returns the type of event
	virtual const EventType& VGetEventType(void) const = 0;

	float VGetTimeStamp(void) const { return m_timeStamp; }
	// Serializing for network out
	virtual void VSerialize (std::ostream &out) const { }
};