#pragma once
#include <vector>
#include "type-hasher.hpp"

namespace agl
{
	class CEntityUID;

	/// <summary>
	/// A base polymorphic base class for TComponentArray class.
	/// </summary>
	class IComponentArray
	{
	public:
		/// <summary>
		/// Defaulted virtual destructor.
		/// </summary>
		virtual ~IComponentArray() = default;

		/// <summary>
		/// Virtual method to match the entity with default initialized component.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		virtual void addEntity(const CEntityUID &entityUID) = 0;

		/// <summary>
		/// Virtual method to destroy an entity's component without the need to know the component's type.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		virtual void entityDestroyed(const CEntityUID &entityUID) = 0;

	private:
		friend class std::vector<IComponentArray>;
		template <typename T> friend class TComponentArray;
	};
}