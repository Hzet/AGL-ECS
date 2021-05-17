#pragma once
#include <bitset>

#include "config.hpp"
#include "type-hasher.hpp"

namespace agl
{
	/// <summary>
	/// A class to uniquely identify a set of different types.
	/// The signature consists of a bitset where the indices represents the agl::type_hash 
	/// and the value represents presence of the type.
	/// </summary>
	class CSignature
	{
	public:
		/// <summary>
		/// Static creator of signatures.
		/// </summary>
		/// <returns>The signature</returns>
		template <typename... Args> static CSignature Create();
 
		/// <summary>
		/// Checks whether the signature includes queried types.
		/// </summary>
		/// <returns>
		/// True - all types are included in the signature.
		/// False - some or all of the types are absent in the signature.
		/// </returns>
		template <typename... Args> bool hasType() const;

		/// <summary>
		/// Attaches the types to the signature.
		/// </summary>
		template <typename... Args> void attachType();

		/// <summary>
		/// Detaches the types from the signature.
		/// </summary>
		template <typename... Args> void detachType();

		/// <summary>
		/// Iterate over the signature's types.
		/// </summary>
		/// <param name="index">The index</param>
		/// <returns>
		/// True - signature has 
		/// </returns>
		bool operator[](typeid_t index) const;

		/// <summary>
		/// Returns the peak, which is the highest used index.
		/// </summary>
		/// <returns>The count</returns>
		std::uint64_t getCount() const;

	private:
		friend struct std::hash<agl::CSignature>;
		friend bool operator==(const CSignature &l, const CSignature &r);
		friend bool operator!=(const CSignature &l, const CSignature &r);
		friend bool operator<(const CSignature &l, const CSignature &r);
		
		/// <summary>
		/// Implementation of hasType method.
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		template <typename TTuple, std::uint64_t... Sequence> bool hasType_impl(std::index_sequence<Sequence...>) const;
		
		/// <summary>
		/// Implementation of attachType method.
		/// </summary>
		/// <param name=""></param>
		template <typename TTuple, std::uint64_t... Sequence> void attachType_impl(std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of attachType method.
		/// </summary>
		/// <param name=""></param>
		template <typename T> void attachType_impl();

		/// <summary>
		/// Implementation of detachType method.
		/// </summary>
		/// <param name=""></param>
		template <typename TTuple, std::uint64_t... Sequence> void detachType_impl(std::index_sequence<Sequence...>);

		/// <summary>
		/// Implementation of detachType method.
		/// </summary>
		/// <param name=""></param>
		template <typename T> void detachType_impl();
								  
		typeid_t peak_;
		std::bitset<AGL_MAX_COMPONENTS> signature_;
	};

	bool operator==(const CSignature &l, const CSignature &r);
	bool operator!=(const CSignature &l, const CSignature &r);
	bool operator<(const CSignature &l, const CSignature &r);

#include "signature.inl"
}

namespace std
{
	template <>
	struct hash<agl::CSignature>
	{
		size_t operator()(const agl::CSignature& signature) const noexcept
		{
			return hash<std::bitset<AGL_MAX_COMPONENTS>>{ }(signature.signature_);
		}
	};
}