template <typename... Args>
void IRegistryComponent::detachComponent(const CEntityUID &entityUID)
{
	detachComponent_impl<Args...>(entityUID, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
void IRegistryComponent::detachComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	((getBaseComponentArray<std::tuple_element_t<Sequence, TTuple>>()->entityDestroyed(entityUID)), ...);
}

template <typename T, typename... Args>
void IRegistryComponent::attachComponent(const CEntityUID &entityUID, Args&&... args)
{
	if constexpr (sizeof...(Args) == 0)
		createComponentArray<T>()->addEntity(entityUID);	
	else
	{
		auto &arr = *dynamic_cast<TComponentArray<T>*>(createComponentArray<T>());
		arr.attach(entityUID, std::forward<Args>(args)...);
	}
}

template <typename... Args>
void IRegistryComponent::attachComponent(const CEntityUID &entityUID)
{
	attachComponent_impl<Args...>(entityUID, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
void IRegistryComponent::attachComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	((createComponentArray<std::tuple_element_t<Sequence, TTuple>>()->addEntity(entityUID)), ...);
}

template <typename... Args>
std::tuple<Args&...> IRegistryComponent::getComponent(const CEntityUID &entityUID)
{
	return getComponent_impl(entityUID, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
std::tuple<Args&...> IRegistryComponent::getComponent_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>)
{
	auto arrays = getComponentArray<Args...>();

	std::tuple<Args&...> result{
		(std::get<Sequence>(arrays).get(entityUID))...
	};

	return result;
}

template <typename... Args>
std::tuple<TComponentArray<Args>&...> IRegistryComponent::getComponentArray()
{
	return getComponentArray_impl<Args...>(std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args, std::uint64_t... Sequence>
std::tuple<TComponentArray<Args>&...> IRegistryComponent::getComponentArray_impl(std::index_sequence<Sequence...>)
{
	using TTuple = std::tuple<Args...>;

	std::tuple<TComponentArray<Args>&...> result{
		(*dynamic_cast<TComponentArray<std::tuple_element_t<Sequence, TTuple>>*>(getBaseComponentArray<std::tuple_element_t<Sequence, TTuple>>()))...
	};

	return result;
}

template <typename T>
IComponentArray* IRegistryComponent::getBaseComponentArray()
{
	return components_[type_hash<T>::value].get();
}

template <typename T>
IComponentArray* IRegistryComponent::createComponentArray()
{
	auto &result = components_[type_hash<T>::value];

	if(result == nullptr)
		result = std::make_unique<TComponentArray<T>>();

	return result.get();
}