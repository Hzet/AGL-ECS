#pragma once
#include <vector>

#include "entity-uid.hpp"
#include "signature.hpp"

namespace agl
{
	class CRegistry;

	/// <summary>
	/// A base class for CRegistry providing utility to manage the entities.
	/// </summary>
	class IRegistryEntity
	{
		friend class CRegistry;

		IRegistryEntity();
		virtual ~IRegistryEntity() = default;

		/// <summary>
		/// Creates the entity.
		/// </summary>
		/// <param name="registry">A pointer to the registry creating the entity</param>
		/// <returns>The entity</returns>
		IEntity createEntity();

		/// <summary>
		/// Destroys an entity.
		/// </summary>
		/// <param name="entity">The entity</param>
		void destroyEntity(IEntity &entity);

		/// <summary>
		/// Converts entity's unique identifier to array index.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The index of the entity</returns>
		std::uint64_t getIndex(const CEntityUID &entityUID) const;

		std::vector<IEntity> entities_;
	};
}