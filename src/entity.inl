template <typename... Args>
std::tuple<Args&...> IEntity::getComponent() const
{
	return registry.get<Args...>(uid_);
}

template <typename... Args>
bool IEntity::hasComponent() const
{
	return signature_.hasType<Args...>();
}

template <typename... Args> 
void IEntity::detachComponent()
{
	signature_.detachType<Args...>();
	registry.detach<Args...>(*this);
}

template <typename T, typename... Args> 
void IEntity::attachComponent(Args&&... args)
{
	signature_.attachType<T>();
	registry.attach<T>(*this, std::forward<Args>(args)...);
}

template <typename... Args>
void agl::IEntity::attachComponent()
{
	signature_.attachType<Args...>();
	registry.attach<Args...>(*this);
}
