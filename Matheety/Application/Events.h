#pragma once
#include <map>
#include <iostream>
#include <vector>
#include <typeinfo>


class EventBase
{
public:
	virtual~EventBase() = default;
};

template<typename... Args>
class Event :public EventBase
{
public:
	Event(void(*func)(Args..., void*), void* obj)
	{
		m_object = obj;
		m_handler = func;
	}

	void Fire(Args...args)
	{
		if (m_object != nullptr && m_handler != nullptr)
			m_handler(std::forward<Args>(args)..., m_object);
	}

	void Update(void(*func)(Args..., void*), void* obj)
	{
		m_object = obj;
		m_handler = func;
	}

	void Clear()
	{
		m_object = nullptr;
		m_handler = nullptr;
	}

	const void* GetObjectPtr()
	{
		return m_object;
	}


private:
	void(*m_handler)(Args..., void*);
	void* m_object = nullptr;


};



class EventDispatcher
{
public:

	template <typename ...Args>
	Event<Args...>* AddEvent(void(*func)(Args..., void*), std::string name, void* obj)
	{
		Event<Args...>* ev = nullptr;
		auto pair = m_events.find(name);
		if (pair != m_events.end())
		{

			ev = dynamic_cast<Event<Args...>*>(pair->second.get());
			if (!ev)
			{
				//Wrong template parameters
				std::string typeName(typeid(*(pair->second.get())).name());
				typeName += " is actual type";
				throw std::invalid_argument(typeName);
			}
			ev->Update(func, obj);
		}
		else
		{
			ev = new Event<Args...>(func, obj);
			m_events.insert(std::make_pair(name, std::unique_ptr<Event<Args...>>(ev)));
		}

		return ev;
	}

	template <typename ...Args>
	Event<Args...>* GetEvent(std::string name)
	{
		Event<Args...>* ret = nullptr;
		auto pair = m_events.find(name);
		if (pair != m_events.end())
		{
			ret = dynamic_cast<Event<Args...>*>(pair->second.get());
			if (!ret)
			{
				//Wrong template parameters
				std::string typeName(typeid(*(pair->second.get())).name());
				typeName += " is actual type";
				throw std::invalid_argument(typeName);
			}
		}


		return ret;
	}

private:
	std::map<std::string, std::unique_ptr<EventBase>> m_events;

};

/*
auto ev = EventGlobal::GetEventDipatcher()->AddEvent<int>([](int b, void* a) {static_cast<A*>(a)->f(b); }
, "test", this); //Create event

ev->Fire(4);
ev->Clear();
ev->Fire(4);
ev->Update([](int b, void* a) {static_cast<A*>(a)->f(b+1); }, this);
ev->Fire(4);
auto ev1 = EventGlobal::GetEventDipatcher()->AddEvent<int>([](int b, void* a) {static_cast<A*>(a)->f(b+3); }
, "test", this); //If you recreate an event with the same name and signature, the previous pointer to this event is still valid and the components are updated
//If signature distincts than behavior is undefuned

ev1->Fire(4);
ev1->Clear();
ev1->Fire(4);
ev1->Update([](int b, void* a) {static_cast<A*>(a)->f(b + 1); }, this);
ev1->Fire(4);
ev->Fire(4);
ev->Clear();
ev->Fire(4);
ev->Update([](int b, void* a) {static_cast<A*>(a)->f(b + 1); }, this);
ev->Fire(4);
ev1->Fire(4);
*/



