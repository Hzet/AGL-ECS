#include "registry.hpp"
#include "entity.hpp"

namespace agl
{
	IEntity CRegistry::create()
	{
		return createEntity();
	}

	void CRegistry::destroy(IEntity &entity)
	{
		entityDestroyed(entity);
	}

	std::vector<agl::CEntityUID> CRegistry::getEntities(const CSignature &signature)
	{
		std::vector<CEntityUID> result;

		for (const auto &e : entities_)
			if (e.getSignature() == signature)
				result.push_back(e.getEntityUID());

		return result;
	}

}

