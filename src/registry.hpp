#pragma once
#include <set>
#include <mutex>

#include "view.hpp"
#include "registry-entity.hpp"
#include "registry-component.hpp"

namespace agl
{
	class CRegistry;
}

extern agl::CRegistry registry;

namespace agl
{

	class CRegistry
		: private IRegistryComponent,
		private IRegistryEntity
	{
	public:
		/// <summary>
		/// Returns a view of entities that matches the signature of 'Args'.
		/// </summary>
		/// <returns>The view</returns>
		template <typename... Args> TView<Args...> view();

		/// <summary>
		/// Creates an entity.
		/// </summary>
		/// <returns>The entity</returns>
		IEntity create();

		/// <summary>
		/// Destroys an entity.
		/// </summary>
		/// <param name="entity">The entity</param>
		void destroy(IEntity &entity);

	private:
		friend class IEntity;
		template <typename... Args> friend class TView;

		std::vector<CEntityUID> getEntities(const CSignature &signature);

		/// <summary>
		/// Returns a tuple of references to queried entity's components.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The components</returns>
		template <typename... Args> std::tuple<Args&...> get(const CEntityUID &entityUID);

		/// <summary>
		/// Detaches the queried components from an entity aliased as 'entityUID'.
		/// If the queried component was not attached to an entity, 
		/// then no action will take place regarding that component array.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		template <typename... Args> void detach(const CEntityUID &entityUID);

		/// <summary>
		/// Initialize the component with 'args' and then attach to an entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <param name="...args">The initialization arguments</param>
		template <typename T, typename... Args> void attach(const CEntityUID &entityUID, Args&&... args);

		/// <summary>
		/// Default initialize the component and attach it to 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		template <typename... Args> void attach(const CEntityUID &entityUID);
	};

#include "registry.inl"
}