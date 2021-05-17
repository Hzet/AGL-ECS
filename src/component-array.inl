template <typename T>
template <typename... Args>
void TComponentArray<T>::attach(const CEntityUID &entityUID, Args&&... args)
{
	activeEntities_[getIndex(entityUID)] = true; 
	components_[getIndex(entityUID)] = T{ std::forward<Args>(args)... };
}

template <typename T>
void TComponentArray<T>::detach(const CEntityUID &entityUID)
{
	activeEntities_[getIndex(entityUID)] = false;
}

template <typename T>
T& TComponentArray<T>::get(const CEntityUID &entityUID)
{
	return components_[getIndex(entityUID)];
}

template <typename T>
const T& TComponentArray<T>::get(const CEntityUID &entityUID) const
{
	return components_[getIndex(entityUID)];
}

template <typename T>
std::uint64_t TComponentArray<T>::getIndex(const CEntityUID &entityUID) const
{
	return entityUID - 1ul;
}

template <typename T>
void TComponentArray<T>::addEntity(const CEntityUID &entityUID)
{
	attach(entityUID);
}

template <typename T>
void TComponentArray<T>::entityDestroyed(const CEntityUID &entityUID)
{
	detach(entityUID);
}