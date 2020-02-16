#include "EventManagerImplement.h"



EventManager::EventManager(const char* pName, bool setAsGlobal)
	:IEventManager(pName, setAsGlobal)
{
	m_activeQueue = 0;
}

bool EventManager::VAddListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	EventListenerList& eventListenerList = m_eventListeners[type];
	// checking if the listener repeats
	for (auto it = eventListenerList.begin(); it != eventListenerList.end(); ++it) {
		if (eventDelegate == (*it))
		{
			return false;
		}
	}
	// if not, add the listener to the list
	eventListenerList.push_back(eventDelegate);
	return true;
}

bool EventManager::VRemoveListener(const EventListenerDelegate& eventDelegate, const EventType& type)
{
	bool success = false;

	auto findIt = m_eventListeners.find(type);
	if (findIt != m_eventListeners.end())
	{
		EventListenerList& listeners = findIt->second;
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (eventDelegate == (*it))
			{
				listeners.erase(it);
				success = true;
				break;
			}
		}
	}
	return success;
}

bool EventManager::VTriggerEvent(const IEventDataPtr& pEvent) const
{
	bool processed = false;

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		const EventListenerList& eventListenerList = findIt->second;
		for (EventListenerList::const_iterator it = eventListenerList.begin(); it != eventListenerList.end(); ++it)
		{
			EventListenerDelegate listener = (*it);
			listener(pEvent);
			processed = true;
		}
	}
	return processed;
}

bool EventManager::VQueueEvent(const IEventDataPtr& pEvent)
{

	auto findIt = m_eventListeners.find(pEvent->VGetEventType());
	if (findIt != m_eventListeners.end())
	{
		m_queues[m_activeQueue].push_back(pEvent);
		return true;
	}
	else
	{
		return false;

	}
}

bool EventManager::VAbortEvent(const EventType& inType, bool allOfType)
{

	bool success = false;
	EventListenerMap::iterator findIt = m_eventListeners.find(inType);
	if (findIt != m_eventListeners.end())
	{
		EventQueue& eventQueue = m_queues[m_activeQueue];
		auto it = eventQueue.begin();
		while (it != eventQueue.end())
		{
			auto thisIt = it;
			++it;
			if ((*thisIt)->VGetEventType() == inType)
			{
				eventQueue.erase(thisIt);
				success = true;
				if (!allOfType)
					break;
			}
		}
	}
	return success;
}

bool EventManager::VTickUpdate(unsigned long maxMillis)
{
	unsigned long currMs = GetTickCount64();
	unsigned long maxMs = ((maxMillis == IEventManager::kINFINITE) ? (IEventManager::kINFINITE) : (currMs + maxMillis));

	int queueToProcess = m_activeQueue;
	m_activeQueue = (m_activeQueue + 1) % EVENTMANAGER_NUM_QUEUES;
	m_queues[m_activeQueue].clear();

	while (!m_queues[queueToProcess].empty())
	{
		IEventDataPtr pEvent = m_queues[queueToProcess].front();
		m_queues[queueToProcess].pop_front();

		const EventType& eventType = pEvent->VGetEventType();

		auto findIt = m_eventListeners.find(eventType);
		if (findIt != m_eventListeners.end())
		{
			const EventListenerList& eventListeners = findIt->second;

			for (auto it = eventListeners.begin(); it != eventListeners.end(); ++it)
			{
				EventListenerDelegate listener = (*it);
				listener(pEvent);
			}
		}

		currMs = GetTickCount64();
		if (maxMillis != IEventManager::kINFINITE && currMs >= maxMs)
		{
			break;
		}
	}

	bool queueFlushed = (m_queues[queueToProcess].empty());
	if (!queueFlushed)
	{
		while (!m_queues[queueToProcess].empty())
		{
			IEventDataPtr pEvent = m_queues[queueToProcess].back();
			m_queues[queueToProcess].pop_back();
			m_queues[m_activeQueue].push_front(pEvent);
		}
	}

	return queueFlushed;
}