#pragma once
#include "component-array-base.hpp"
#include "entity-uid.hpp"
#include "config.hpp"

namespace agl
{
	/// <summary>
	/// An array object that stores the components and it's relation with entities.
	/// </summary>
	template <typename T>
	class TComponentArray
		: public IComponentArray
	{
	public:
		/// <summary>
		/// Initialize the component with 'args' and then attach to an entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <param name="...args">The initialization arguments</param>
		template <typename... Args> void attach(const CEntityUID &entityUID, Args&&... args);
		
		/// <summary>
		/// Detach component from entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		void detach(const CEntityUID &entityUID);

		/// <summary>
		/// Returns the component related to entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The component</returns>
		T& get(const CEntityUID &entityUID);

		/// <summary>
		/// Returns the component related to entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The component</returns>
		const T& get(const CEntityUID &entityUID) const;

	private:
		/// <summary>
		/// Converts entity's unique identifier to array index.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The index of the entity</returns>
		std::uint64_t getIndex(const CEntityUID &entityUID) const;

		/// <summary>
		/// Overridden virtual method to match the entity with default initialized component.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		virtual void addEntity(const CEntityUID &entityUID) override;

		/// <summary>
		/// Overridden virtual method to destroy an entity's component without the need to know the component's type.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		virtual void entityDestroyed(const CEntityUID &entityUID) override;

		std::array<T, AGL_MAX_ENTITIES> components_;
		std::array<bool, AGL_MAX_ENTITIES> activeEntities_;
	};

#include "component-array.inl"
}