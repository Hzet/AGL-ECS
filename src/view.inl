template <typename... Args>
TView<Args...>::iterator::iterator(TView<Args...> &view, std::vector<CEntityUID>::iterator it)
	: view_(view),
	iterator_(it)
{
}

template <typename... Args>
bool TView<Args...>::iterator::operator!=(const iterator &other) const
{
	return iterator_ != other.iterator_;
}

template <typename... Args>
bool TView<Args...>::iterator::operator==(const iterator &other) const
{
	return iterator_ == other.iterator_;
}

template <typename... Args>
typename TView<Args...>::iterator::reference TView<Args...>::iterator::operator*() const
{
	return view_.get(*iterator_);
}

template <typename... Args>
typename TView<Args...>::iterator TView<Args...>::iterator::operator++(int)
{
	iterator result{ *this };

	++(*this);

	return result;
}

template <typename... Args>
typename TView<Args...>::iterator& TView<Args...>::iterator::operator++()
{
	++iterator_;
	return *this;
}

template <typename... Args>
typename TView<Args...>::iterator TView<Args...>::begin()
{
	return TView<Args...>::iterator{ *this, entities_.begin() };
}

template <typename... Args>
typename TView<Args...>::iterator TView<Args...>::end()
{
	return TView<Args...>::iterator{ *this, entities_.end() };
}

template <typename... Args>
TView<Args...>::TView(std::tuple<TComponentArray<Args>&...> arrays)
	: arrays_(std::move(arrays))
{
}

template <typename... Args>
void TView<Args...>::track(std::vector<CEntityUID> &&entities)
{
	entities_ = std::move(entities);
}


template <typename... Args>
std::tuple<Args&...> TView<Args...>::get(const CEntityUID &entityUID)
{
	return get_impl(entityUID, std::make_index_sequence<sizeof...(Args)>{ });
}

template <typename... Args>
template <std::uint64_t... Sequence>
std::tuple<Args&...> TView<Args...>::get_impl(const CEntityUID &entityUID, std::index_sequence<Sequence...>)
{
	return { (std::get<Sequence>(arrays_).get(entityUID))... };
}