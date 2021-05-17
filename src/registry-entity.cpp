#include "registry-entity.hpp"
#include "registry.hpp"
#include "entity.hpp"

namespace agl
{

	IRegistryEntity::IRegistryEntity()
		: entities_(AGL_MAX_ENTITIES)
	{
	}

	IEntity IRegistryEntity::createEntity()
	{
		//AGL_CORE_ASSERT(occupied_ < AGL_MAX_ENTITIES, "Maximum capacity reached!");

		IEntity result{ CEntityUID{ } };

		entities_[getIndex(result)] = result;

		return result;
	}

	void IRegistryEntity::destroyEntity(IEntity &entity)
	{
		entities_[getIndex(entity)] = { };

		entity = IEntity{ };
	}

	std::uint64_t IRegistryEntity::getIndex(const CEntityUID &entityUID) const
	{
		return entityUID - 1ul;
	}

}