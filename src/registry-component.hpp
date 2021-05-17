#pragma once
#include <array>
#include <memory>

#include "component-array.hpp"

namespace agl
{
	/// <summary>
	/// A base class for CRegistry providing utility to manage the components.
	/// </summary>
	class IRegistryComponent
	{
		friend class CRegistry;

		/// <summary>
		/// Returns a tuple of references to queried entity's components.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The components</returns>
		template <typename... Args> std::tuple<Args&...> getComponent(const CEntityUID &entityUID);

		/// <summary>
		/// Initialize the component with 'args' and then attach to an entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <param name="...args"></param>
		template <typename T, typename... Args> void attachComponent(const CEntityUID &entityUID, Args&&... args);

		/// <summary>
		/// Default initialize the components of type 'Args' and attach them to the entity.
		/// </summary>
		/// <param name="entityUID">The entity's unique identitifer</param>
		template <typename... Args> void attachComponent(const CEntityUID &entityUID);

		/// <summary>
		/// Detaches the queried components from an entity aliased as 'entityUID'.
		/// If the queried component was not attached to an entity, 
		/// then no action will take place regarding that component array.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		template <typename... Args> void detachComponent(const CEntityUID &entityUID);

		/// <summary>
		/// Returns a tuple of references to component arrays.
		/// </summary>
		/// <returns>The component arrays</returns>
		template <typename... Args> std::tuple<TComponentArray<Args>&...> getComponentArray();

		/// <summary>
		/// Detaches the components that belong to the 'entity'.
		/// </summary>
		/// <param name="entity">The entity</param>
		void entityDestroyed(const IEntity &entity);

		std::array<std::unique_ptr<IComponentArray>, AGL_MAX_COMPONENTS> components_;

	private:
		/// <summary>
		/// Implementation of getComponent method.
		/// </summary>
		/// <param name="entityUID"></param>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename... Args, std::uint64_t... Sequence> std::tuple<Args&...> getComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of attachComponent method
		/// </summary>
		/// <param name="entityUID"></param>
		/// <param name=""></param>
		template <typename... Args, std::uint64_t... Sequence> void attachComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of detachComponent method.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <param name=""></param>
		template <typename... Args, std::uint64_t... Sequence> void detachComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of getComponentArray method.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename... Args, std::uint64_t... Sequence> std::tuple<TComponentArray<Args>&...> getComponentArray_impl(std::index_sequence<Sequence...>);

		/// <summary>
		/// Returns an component array.
		/// </summary>
		/// <returns>The component array</returns>
		template <typename T> IComponentArray* getBaseComponentArray();

		/// <summary>
		/// Creates a new component array if it does not yet exist and return it.
		/// </summary>
		/// <returns>The component array</returns>
		template <typename T> IComponentArray* createComponentArray();
	};

#include "registry-component.inl"
}