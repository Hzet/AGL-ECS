template<typename... Args>
CSignature CSignature::Create()
{
	CSignature signature;
	signature.attachType<Args...>();

	return signature;
}

template <typename... Args> 
bool CSignature::hasType() const
{
	return hasType_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
bool CSignature::hasType_impl(std::index_sequence<Sequence...>) const
{
	return (... && (signature_[type_hash<std::tuple_element_t<Sequence, TTuple>>::value] == true));
}

template <typename... Args>
void CSignature::attachType()
{
	attachType_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
void CSignature::attachType_impl(std::index_sequence<Sequence...>)
{
	((attachType_impl<std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename T>
void CSignature::attachType_impl()
{
	typeid_t hash = type_hash<T>::value;

	if (peak_ < hash)
		peak_ = hash;

	signature_.set(hash, true);
}

template <typename... Args> 
void CSignature::detachType()
{
	detachType_impl<std::tuple<Args...>>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename TTuple, std::uint64_t... Sequence>
void CSignature::detachType_impl(std::index_sequence<Sequence...>)
{
	((detachType_impl<std::tuple_element_t<Sequence, TTuple>>()), ...);
}

template <typename T>
void CSignature::detachType_impl()
{
	typeid_t hash = type_hash<T>::value;

	if (peak_ == hash && peak_ != 0u)
		for (typeid_t i = peak_ - 1u; i > 0u; i--)
			if (signature_[i] == true)
				peak_ = i;

	signature_.set(hash, false);
}

