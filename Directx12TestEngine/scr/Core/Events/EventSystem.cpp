#include "EventSystem.h"

std::unordered_map<std::type_index, std::map<unsigned int, std::function<void(dx12ge::Event*)>>> dx12ge::EventSystem::_map;