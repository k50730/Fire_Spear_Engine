#pragma once
#include "EventManager.h"

const unsigned int EVENTMANAGER_NUM_QUEUES = 2;

class EventManager : public IEventManager
{
	typedef std::list<EventListenerDelegate> EventListenerList;
	typedef std::map<EventType, EventListenerList> EventListenerMap;
	typedef std::list<IEventDataPtr> EventQueue;

	EventListenerMap m_eventListeners;
	EventQueue m_queues[EVENTMANAGER_NUM_QUEUES];
	int m_activeQueue = 0;

public:
	explicit EventManager(const char* pName, bool setAsGlobal);
	virtual ~EventManager(void) {}

	virtual bool VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type) = 0;
	virtual bool VTriggerEvent(const IEventDataPtr& pEvent) const = 0;
	virtual bool VQueueEvent(const IEventDataPtr& pEvent) = 0;
	virtual bool VAbortEvent(const EventType& type, bool allOfType = false) = 0;
	virtual bool VTickUpdate(unsigned long maxMillis = kINFINITE) = 0;

private:


};