#include "registry-component.hpp"
#include "entity.hpp"

namespace agl
{
	void IRegistryComponent::entityDestroyed(const IEntity &entity)
	{
		const CSignature &signature = entity.getSignature();

		for (typeid_t i = 0u; i < signature.getCount(); i++)
			if (signature[i])
				components_[i]->entityDestroyed(entity);
	}
}

