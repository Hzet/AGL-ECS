#include "signature.hpp"

namespace agl
{
	bool operator==(const CSignature &l, const CSignature &r)
	{
		return l.signature_ == r.signature_;
	}

	bool operator!=(const CSignature &l, const CSignature &r)
	{
		return !(l == r);
	}

	bool operator<(const CSignature &l, const CSignature &r)
	{
		if (l.peak_ > r.peak_)
			return false;
		
		if (l.peak_ < r.peak_)
			return true;

		for (std::uint64_t i = 0ul; i < l.peak_; i++)
			if (!l[i] && r[i])
				return true;

		return false;
	}

	bool CSignature::operator[](typeid_t index) const
	{
		return signature_[index];
	}

	std::uint64_t CSignature::getCount() const
	{
		return (peak_ == 0ul ? 0ul : peak_ + 1ul);
	}
}