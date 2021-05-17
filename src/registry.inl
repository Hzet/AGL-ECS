template <typename T, typename... Args> 
void CRegistry::attach(const CEntityUID &entityUID, Args&&... args)
{
	this->attachComponent<T>(entityUID, std::forward<Args>(args)...);
}

template <typename... Args>
void CRegistry::attach(const CEntityUID &entityUID)
{
	this->attachComponent<Args...>(entityUID);
}

template <typename... Args> 
void CRegistry::detach(const CEntityUID &entityUID)
{
	this->detachComponent<Args...>(entityUID);
}

template <typename... Args> 
std::tuple<Args&...> CRegistry::get(const CEntityUID &entityUID)
{
	return getComponent<Args...>(entityUID);
}

template <typename... Args>
TView<Args...> CRegistry::view()
{
	TView<Args...> result(this->getComponentArray<Args...>());

	result.track(std::move(getEntities(CSignature::Create<Args...>())));

	return result;
}