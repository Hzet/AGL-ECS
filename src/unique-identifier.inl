template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID()
	: uid_(Register())
{
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(EInvalid)
	: uid_(INVALID)
{
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(std::uint64_t uid)
	: uid_(uid)
{
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::~TUID()
{
	Unregister(*this);
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(TUID &&other)
	: uid_(other.uid_)
{
	other.uid_ = INVALID;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::TUID(const TUID &other)
	: uid_(other.uid_)
{
	Increment(*this);
}

template <typename T, std::uint64_t Size>
TUID<T, Size>& TUID<T, Size>::operator=(TUID &&other)
{
	std::swap(uid_, other.uid_);

	return *this;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>& TUID<T, Size>::operator=(const TUID &other)
{
	uid_ = other.uid_;
	Increment(*this);

	return *this;
}

template <typename T, std::uint64_t Size>
TUID<T, Size>::operator std::uint64_t() const
{
	return uid_;
}

template <typename T, std::uint64_t Size>
std::uint64_t TUID<T, Size>::Register()
{
	auto &identifiers = RegisteredIdentifiers();
	auto &freeIndexes = FreeIndexes();
	auto &peak = Peak();

	if (freeIndexes.empty())
	{
		identifiers[peak]++;
		peak++;
		return { peak };
	}
	else
	{
		std::uint64_t index = freeIndexes.front();
		freeIndexes.pop_front();

		identifiers[index]++;

		return { index + 1ul };
	}
}

template <typename T, std::uint64_t Size>
void TUID<T, Size>::Unregister(TUID<T, Size> &uid)
{
	if (uid == INVALID)
		return;

	auto &identifiers = RegisteredIdentifiers();
	auto &freeIndexes = FreeIndexes();
	auto &peak = Peak();

	if (uid == peak)
		peak--;
	else if (uid < peak)
		freeIndexes.push_back(uid);

	identifiers[uid - 1ul]--;
}

template <typename T, std::uint64_t Size>
void TUID<T, Size>::Increment(TUID<T, Size> &uid)
{
	if (uid == INVALID)
		return;

	RegisteredIdentifiers()[uid - 1ul]++;
}

template <typename T, std::uint64_t Size>
std::array<std::uint64_t, Size>& TUID<T, Size>::RegisteredIdentifiers()
{
	static std::array<std::uint64_t, Size> Identifiers_;

	return Identifiers_;
}

template <typename T, std::uint64_t Size>
std::list<std::uint64_t>& TUID<T, Size>::FreeIndexes()
{
	static std::list<std::uint64_t> Indexes_;

	return Indexes_;
}

template <typename T, std::uint64_t Size>
std::uint64_t& TUID<T, Size>::Peak()
{
	static std::uint64_t Peak_ = 0ul;

	return Peak_;
}