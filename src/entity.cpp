#include "entity.hpp"

namespace agl
{
	IEntity::IEntity()
		: uid_(CEntityUID::INVALID)
	{
	}

	IEntity::IEntity(IEntity &&other)
		: uid_(std::move(other.uid_)),
		signature_(std::move(other.signature_))
	{
	}

	IEntity::IEntity(const IEntity &other)
		: uid_(other.uid_),
		signature_(other.signature_)
	{
	}

	IEntity::~IEntity()
	{
	}

	IEntity& IEntity::operator=(IEntity &&other)
	{
		uid_ = std::move(other.uid_);
		signature_ = std::move(other.signature_);

		return *this;
	}

	IEntity& IEntity::operator=(const IEntity &other)
	{
		uid_ = other.uid_;
		signature_ = other.signature_;

		return *this;
	}

	const CEntityUID& IEntity::getEntityUID() const
	{
		return uid_;
	}

	IEntity::operator CEntityUID() const
	{
		return uid_;
	}

	const CSignature& IEntity::getSignature() const
	{
		return signature_;
	}

	IEntity::IEntity(const CEntityUID &entityUID)
		:  uid_(entityUID)
	{
	}
}