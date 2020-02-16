#pragma once
#include "windows.h"
#include "EventManager.h"




typedef unsigned long EventType;


#pragma region Mouse Event

class OnMouseClick :public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnMouseClick> OnMouseClickPtr;
	explicit OnMouseClick() {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnMouseClickPtr); }

	virtual const char* GetName(void) const { return "MouseClick"; }
};

class OnMouseMove : public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnMouseMove> OnMouseMovePtr;

	explicit OnMouseMove(float x, float y)
		: m_MouseX(x), m_MouseY(y) {}

	inline float GetMouseX() const { return m_MouseX; }

	inline float GetMouseY() const { return m_MouseY; }

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnMouseMovePtr); }

	virtual const char* GetName(void) const { return "MouseMove"; }

	std::string ToString(void) const override
	{
		std::stringstream ss;
		ss << "Mouse Move: " << m_MouseX << "," << m_MouseY;
		return ss.str();
	}
private:
	float m_MouseX, m_MouseY;
};

class OnMousePressed : public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnMousePressed> OnMousePressedPtr;

	explicit OnMousePressed(int button)
		: m_Button(button) {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnMousePressedPtr); }

	virtual const char* GetName(void) const { return "MouseButtonPressed"; }
private:
	int m_Button;
};

class OnMouseReleased : public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnMouseReleased> OnMouseReleasedPtr;

	explicit OnMouseReleased(int button)
		: m_Button(button) {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnMouseReleasedPtr); }

	virtual const char* GetName(void) const { return "MouseButtonReleased"; }
private:
	int m_Button;
};

#pragma endregion


#pragma region Key Event
// Base Key Event
class KeyEvent : public BaseEventData
{
public:
	inline int GetKeyCode() const { return m_KeyCode; }
protected:
	KeyEvent(int keycode)
		: m_KeyCode(keycode) {}

	int m_KeyCode;
};

class OnKeyPressed : public KeyEvent
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnKeyPressed> OnKeyPressedPtr;

	OnKeyPressed(int keycode)
		: KeyEvent(keycode) {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnKeyPressedPtr); }

	virtual const char* GetName(void) const { return "KeyPressed"; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "Key Pressed: " << m_KeyCode;
		return ss.str();
	}

};

class OnKeyReleased : public KeyEvent
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnKeyReleased> OnKeyReleasedPtr;

	OnKeyReleased(int keycode)
		: KeyEvent(keycode) {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnKeyReleasedPtr); }

	virtual const char* GetName(void) const { return "KeyReleased"; }

	std::string ToString(void) const override
	{
		std::stringstream ss;
		ss << "Key Released: " << m_KeyCode;
		return ss.str();
	}
};

#pragma endregion


#pragma region Window Event

class OnWindowResize : public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnWindowResize> OnWindowResizePtr;

	OnWindowResize(unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height) {}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnWindowResizePtr); }

	virtual const char* GetName(void) const { return "OnWindowResize"; }
private:
	unsigned int m_Width, m_Height;
};

class OnWindowClose : public BaseEventData
{
public:
	static const EventType sk_EventType;
	std::shared_ptr<OnWindowClose> OnWindowClosePtr;

	OnWindowClose() {}

	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(OnWindowClosePtr); }

	virtual const char* GetName(void) const { return "OnWindowClose"; }
};

#pragma endregion

#pragma region Actor Event

class OnObjectSpawn : public BaseEventData
{
	int m_ObjectId;
public:
	static const EventType sk_EventType;

	OnObjectSpawn(void) 
	{
		m_ObjectId = NULL;
	}

	explicit OnObjectSpawn(int objectId) 
		: m_ObjectId(objectId)
	{

	}
	std::shared_ptr<OnObjectSpawn> OnObjectSpawnPtr;





	virtual const EventType& VGetEventType(void) const { return sk_EventType; }

	virtual IEventDataPtr VCopy(void) const { return IEventDataPtr(new OnObjectSpawn(m_ObjectId)); }

	virtual const char* GetName(void) const { return "OnObjectSpawn"; }

	const int GetObjectId(void) const { return m_ObjectId; }

private:


};



#pragma endregion