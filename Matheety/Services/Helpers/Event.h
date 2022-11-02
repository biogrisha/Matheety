#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <memory>


//#define EVENT_CLASS_DEBUG

template<typename... Args>
class EventHandlerRAII;

template<typename... Args>
class Event
{
public:

	template<typename func, typename objType>
	struct ObjAndFunc
	{
#ifdef EVENT_CLASS_DEBUG
		~ObjAndFunc()
		{
			std::cout << "ObjAndFunc deleted " << ind << std::endl;
			i--;
		}

		ObjAndFunc()
		{
			ind = i++;
			std::cout << "ObjAndFunc created " << ind << std::endl;
		}
		int ind;
		static int i;
#endif // EVENT_CLASS_DEBUG
		func fPtr;
		objType* obj;
	};



	template<typename func, typename objType>
	EventHandlerRAII<Args...> AddHandler(func fPtr, objType* objPtr)
	{
		ObjAndFunc<func, objType>* objAndFunc = new ObjAndFunc<func, objType>;
		objAndFunc->fPtr = fPtr;
		objAndFunc->obj = objPtr;


		eventStruct evStr;
		evStr.handler = RetLambda<func, objType>();
		evStr.deleter = RetLambdaDestructor<func, objType>();
		evStr.getObjPtr = RetLambdaGetObjPtr<func, objType>();
		evStr.object = objAndFunc;
		evStr.id.reset(new int(m_handlers.size()));

		int* tempId = evStr.id.get();
		m_handlers.push_back(std::move(evStr));

		return EventHandlerRAII< Args...>(this, tempId);
	}


	void Fire(Args...args)
	{
		for (auto& hndl : m_handlers)
		{
			hndl.handler(std::forward<Args>(args)..., hndl.object);

		}
	}

	void operator()(Args...args)
	{
		for (auto& hndl : m_handlers)
		{
			hndl.handler(std::forward<Args>(args)..., hndl.object);

		}
	}

	void Clear(int id)
	{
		if (id == m_handlers.size() - 1) //if id is the last element then just pop
		{
			m_handlers.pop_back();
		}
		else
		{
			eventStruct& lastEl = m_handlers.back();//else get last el
			*(lastEl.id) = id; //set its id to that of el to delete
			std::iter_swap(m_handlers.begin() + id, m_handlers.end() - 1);//swap
			m_handlers.pop_back();//pop 
		}
	}


private:

	template<typename func, typename objType>
	auto RetLambda()
	{
		return [](Args...t, void* objAndFunc) {


			auto objFuncCast = static_cast<ObjAndFunc<func, objType>*>(objAndFunc);
			(objFuncCast->obj->*(objFuncCast->fPtr))(std::forward<Args>(t)...);
		};
	}

	template<typename func, typename objType>
	auto RetLambdaDestructor()
	{
		return [](void* objAndFunc) {


			auto objFuncCast = static_cast<ObjAndFunc<func, objType>*>(objAndFunc);
			delete objFuncCast;
		};
	}

	template<typename func, typename objType>
	auto RetLambdaGetObjPtr()
	{
		return [](void* objAndFunc, void** obj) {


			auto objFuncCast = static_cast<ObjAndFunc<func, objType>*>(objAndFunc);
			*obj = objFuncCast->obj;
		};
	}

	struct eventStruct
	{
		~eventStruct()
		{
			if (object != NULL && deleter != NULL)
				deleter(object);
		}
		eventStruct(eventStruct&& obj)
		{
			handler = obj.handler;
			deleter = obj.deleter;
			getObjPtr = obj.getObjPtr;
			object = obj.object;
			id = std::move(obj.id);
			obj.handler = NULL;
			obj.deleter = NULL;
			obj.getObjPtr = NULL;
			obj.object = NULL;
			obj.id.reset();
		}
		eventStruct& operator=(eventStruct&& other)
		{
			if (this != &other)
			{
				handler = other.handler;
				deleter = other.deleter;
				getObjPtr = other.getObjPtr;
				object = other.object;
				id = std::move(other.id);
				other.handler = NULL;
				other.deleter = NULL;
				other.getObjPtr = NULL;
				other.object = NULL;
				other.id.reset();
			}

			return *this;
		}

		eventStruct() = default;

		void(*handler)(Args..., void*);
		void(*deleter)(void*);
		void(*getObjPtr)(void*, void**);
		void* object;
		std::unique_ptr<int> id;
	};
	std::vector<eventStruct> m_handlers;


};

#ifdef EVENT_CLASS_DEBUG

template<typename ...Args>
template<typename func, typename objType>
int Event<Args...>::ObjAndFunc<func, objType>::i = 0;
#endif // EVENT_CLASS_DEBUG


template<typename... Args>
class EventHandlerRAII
{
public:
	EventHandlerRAII(Event< Args...>* eventPtr, int* id)
	{
		m_id = id;
		m_eventPtr = eventPtr;
	}
	EventHandlerRAII() = default;

	~EventHandlerRAII()
	{
		if (m_eventPtr != NULL && m_id != NULL)
			m_eventPtr->Clear(*m_id);
	}
	void reset(EventHandlerRAII&& other)
	{
		if (this != &other)
		{
			if (m_eventPtr != NULL)
			{
				m_eventPtr->Clear(*m_id);

			}
			m_eventPtr = other.m_eventPtr;
			m_id = other.m_id;
			other.m_id = NULL;
			other.m_eventPtr = NULL;

		}
	}

	void reset()
	{
		if (m_eventPtr != NULL && m_id != NULL)
		{
			m_eventPtr->Clear(*m_id);

		}

		m_id = NULL;
		m_eventPtr = NULL;


	}

	EventHandlerRAII(EventHandlerRAII&& other)
	{
		if (this != &other)
		{
			m_id = other.m_id;
			m_eventPtr = other.m_eventPtr;
			other.m_id = NULL;
			other.m_eventPtr = NULL;
		}
	}

private:
	friend Event<Args...>;
	int* m_id = NULL;
	Event<Args...>* m_eventPtr = NULL;

};