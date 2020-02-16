#pragma once

#include "FastDelegate.h"
#include <list>
#include <map>
#include <iostream>
#include <sstream>
#include "windows.h"

//using fastdelegate::MakeDelegate;

class IEventData;

typedef unsigned long EventType;
typedef std::shared_ptr<IEventData> IEventDataPtr;
typedef fastdelegate::FastDelegate1<IEventDataPtr> EventListenerDelegate;




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



class BaseEventData : public IEventData {
	const float m_timeStamp;
public:
	// Consturctor
	explicit BaseEventData(const float timeStamp = 0.0f)
		:m_timeStamp(timeStamp) {}
	// 
	virtual ~BaseEventData(void) {}

	// Returns the type of event
	virtual const EventType& VGetEventType(void) const = 0;

	float VGetTimeStamp(void) const { return m_timeStamp; }
	// Serializing for network out
	virtual void VSerialize(std::ostream& out) const { }
};



class IEventManager
{
public:
	enum eConstants {kINFINITE = 0xffffffff};

	explicit IEventManager(const char* pName, bool setAsGlobal);
	virtual ~IEventManager(void);

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;
	virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;
	virtual bool VTickUpdate(unsigned long maxMillis = kINFINITE) = 0;


	static IEventManager* Get(void);
};
