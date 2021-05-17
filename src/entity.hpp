#pragma once
#include "signature.hpp"
#include "registry.hpp"

namespace agl
{
	/// <summary>
	/// An interface representing entity.
	/// </summary>
	class IEntity
	{
	public:
		/// <summary>
		/// Default constructor.
		/// Sets the object to an invalid state.
		/// </summary>
		IEntity();

		/// <summary>
		/// Virtual destructor.
		/// </summary>
		virtual ~IEntity();

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		IEntity(IEntity &&other);

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The other object</param>
		IEntity(const IEntity &other);

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>Reference to *this</returns>
		IEntity& operator=(IEntity &&other);

		/// <summary>
		/// Copy assignment operator.
		/// </summary>
		/// <param name="other">The other object</param>
		/// <returns>Reference to *this</returns>
		IEntity& operator=(const IEntity &other);

		/// <summary>
		/// Returns the entity's unique identifier.
		/// </summary>
		/// <returns>The entity's unique identifier</returns>
		const CEntityUID& getEntityUID() const;

		/// <summary>
		/// Implicit cast operator to CEntityUID.
		/// </summary>
		/// <returns>The entity's unique identifier</returns>
		operator CEntityUID() const;

		/// <summary>
		/// Returns the signature.
		/// </summary>
		/// <returns>The signature</returns>
		const CSignature& getSignature() const;

		/// <summary>
		/// Returns a tuple of references to queried entity's components.
		/// </summary>
		/// <returns>The components</returns>
		template <typename... Args> std::tuple<Args&...> getComponent() const;

		/// <summary>
		/// Checks whether the entity has queried components.
		/// </summary>
		/// <returns>
		/// True - entity has got all of the queried components attached.
		/// False - entity has got some or all of the queried components absent.
		/// </returns>
		template <typename... Args> bool hasComponent() const;

		/// <summary>
		/// Detaches the queried components from an entity.
		/// If the queried component was not attached to an entity, 
		/// then no action will take place regarding that component array.
		/// </summary>
		template <typename... Args> void detachComponent();
		
		/// <summary>
		/// Initialize the component with 'args' and then attach to an entity aliased as 'entityUID'.
		/// </summary>
		/// <param name="...args">The initialization arguments</param>
		template <typename T, typename... Args> void attachComponent(Args&&... args);

		/// <summary>
		/// Default initialize the component and attach it to the entity.
		/// </summary>
		template <typename... Args> void attachComponent();

	private:
		friend class IRegistryEntity;

		/// <summary>
		/// Construct from CEntityUID.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		IEntity(const CEntityUID &entityUID);

		CSignature signature_;
		CEntityUID uid_;
	};

#include "entity.inl"
}