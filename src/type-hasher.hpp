#pragma once

namespace agl
{
	using typeid_t = std::uint64_t;

	/// <summary>
	/// Implementation of type_hash.
	/// </summary>
	class type_hash_impl
	{
		template <typename T> friend struct type_hash;

		static inline int TypeIncrementor = 0;
	};

	/// <summary>
	/// Creates a unique hash identifier for type 'T'.
	/// The hash values are guaranteed to be continuous and start from 0.
	/// </summary>
	template <typename T>
	struct type_hash
	{
		using type = typename T;
		static inline const typeid_t value = type_hash_impl::TypeIncrementor++;
	};
}