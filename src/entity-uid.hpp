#pragma once
#include "config.hpp"
#include "unique-identifier.hpp"

namespace agl
{
	class IEntity;

	class CEntityUID
		: public TUID<IEntity, AGL_MAX_ENTITIES>
	{
	public:
		using TUID<IEntity, AGL_MAX_ENTITIES>::TUID;
	};
}

namespace std
{
	template <>
	struct hash<agl::CEntityUID>
	{
		size_t operator()(const agl::CEntityUID &uid) const noexcept
		{
			return hash<uint64_t>{}(static_cast<const uint64_t>(uid));
		}
	};
}