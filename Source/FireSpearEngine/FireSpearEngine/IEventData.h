#pragma once
#include <iostream>
#include <sstream>
#include "windows.h"

typedef unsigned long EventType;


class IEventData {
public:
	typedef std::shared_ptr<IEventData> IEventDataPtr;
	virtual const EventType& VGetEventType(void) const = 0;
	virtual float VGetTimeStamp(void) const = 0;
	virtual void VSerialize(std::ostream& out) const = 0;
	virtual IEventDataPtr VCopy(void) const = 0;
	virtual const char* GetName(void) const = 0;
	virtual std::string ToString() const { return GetName(); }
};