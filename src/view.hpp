#pragma once
#include "entity-uid.hpp"
#include "signature.hpp"
#include "component-array.hpp"

namespace agl
{
	/// <summary>
	/// A view class representing a container that accumulates the entities matching signature with 'Args'.
	/// </summary>
	template <typename... Args>
	class TView
	{
	public:
		/// <summary>
		/// A view iterator.
		/// </summary>
		class iterator
		{
		public:
			using iterator_category = std::input_iterator_tag;
			using value_type = typename std::tuple<Args&...>;
			using difference_type = typename std::uint64_t;
			using pointer = typename std::tuple<Args&...>;
			using reference = typename std::tuple<Args&...>;

			explicit iterator(TView<Args...> &view, std::vector<CEntityUID>::iterator it);

			iterator& operator++();
			iterator operator++(int);

			reference operator*() const;

			bool operator==(const iterator &other) const;
			bool operator!=(const iterator &other) const;

		private:
			TView<Args...> &view_;

			std::vector<CEntityUID>::iterator iterator_;
		};
		
		/// <summary>
		/// Return an iterator pointing to the first element of the view.
		/// </summary>
		/// <returns>The begin iterator</returns>
		iterator begin();

		/// <summary>
		/// Return an iterator pointing to the element after the last element of the view.
		/// </summary>
		/// <returns>The end iterator</returns>
		iterator end();

	private:
		friend class CRegistry;

		/// <summary>
		/// Construct from component array references.
		/// </summary>
		/// <param name="arrays">The component arrays</param>
		TView(std::tuple<TComponentArray<Args>&...> arrays);

		/// <summary>
		/// Adds the entities belonging to the view.
		/// </summary>
		/// <param name="entities"></param>
		void track(std::vector<CEntityUID> &&entities);

		/// <summary>
		/// Returns a tuple of references to queried entity's components.
		/// </summary>
		/// <param name="entityUID">The entity's unique identifier</param>
		/// <returns>The components</returns>
		std::tuple<Args&...> get(const CEntityUID &entityUID);

		/// <summary>
		/// Implementation of get method.
		/// </summary>
		/// <param name="entityUID"></param>
		/// <param name=""></param>
		/// <returns></returns>
		template <std::uint64_t... Sequence> std::tuple<Args&...> get_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>);

		std::vector<CEntityUID> entities_;
		std::tuple<TComponentArray<Args>&...> arrays_;
	};

#include "view.inl"
}