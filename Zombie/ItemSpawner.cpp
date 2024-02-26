#include "pch.h"
#include "ItemSpawner.h"

ItemSpawner::ItemSpawner(const std::string& name) : Spawner(name)
{
}

GameObject* ItemSpawner::Create()
{
	Item::Types itemType = itemTypes[Utils::RandomRange(0, itemTypes.size())];
	return Item::Create(itemType, 20);
}

void ItemSpawner::Reset()
{
	Spawner::Reset();
	interval = 3.f;
	radius = 500.f; //생성반경

	itemTypes.clear();
	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Ammo);
	itemTypes.push_back(Item::Types::Health);
}
