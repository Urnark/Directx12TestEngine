#pragma once

#include <unordered_map>
#include <map>
#include <typeindex>
#include <functional>

#include "../../Utils/Logger.h"

namespace dx12ge
{
	using namespace dx12ge;

	class Event
	{
	public:
		Event() {};
		virtual ~Event() {};
	};


	class EventSystem
	{
		using FuncCallback = std::function<void(Event*)>;

	private:
		static std::unordered_map<std::type_index, std::map<unsigned int, FuncCallback>> _map;

	public:

		/* Call all the subscribers that subscribes to the Event */
		template<class E>
		static void publish(E & e)
		{
			//PrintNL_PFN("Publish: ", typeid(E).name());
			for (auto it : _map[typeid(E)])
			{
				it.second(&e);
			}
		}

		/* Subscribe to the event system */
		template<class T, class E>
		static void subscribe(T* subscriber, void(T::*callback)(E*))
		{
			//PrintNL_PFN("Subscribe: ", typeid(E).name(), ", ID [", reinterpret_cast<unsigned int>(subscriber), "]");
			std::map<unsigned int, FuncCallback>& subscribers = _map[typeid(E)];

			subscribers[reinterpret_cast<unsigned int>(subscriber)] = std::bind((void(T::*)(Event*))callback, subscriber, std::placeholders::_1);
		};

		/* Remove an instance of a class from the event system */
		template<class T, class E>
		static void unsubscribe(T* subscriber, void(T::*callback)(E*))
		{
			//PrintNL_PFN("Unsubscribe: ", typeid(E).name(), ", ID [", reinterpret_cast<unsigned int>(subscriber), "]");
			std::map<unsigned int, FuncCallback>& subscribers = _map[typeid(E)];

			subscribers.erase(reinterpret_cast<unsigned int>(subscriber));
			
			if (subscribers.empty())
			{
				_map.erase(typeid(E));
			}
		};

		/* Remove all the subscribers from the event system */
		static void unsubscribeAll()
		{
			for (auto it : _map)
			{
				it.second.clear();
			}
			_map.clear();
		}
	};
}