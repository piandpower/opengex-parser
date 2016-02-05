#include "OpenGEXPCH.h"
#include "OpenGEXAny.h"

namespace OGEXParser
{
	Any::AnyEmpty Any::Null;

	Any::Any() :
		content(nullptr)
	{
	}

	Any::Any(const Any::AnyEmpty& value) :
		content(nullptr)
	{
	}

	Any::Any(const Any& other) :
		content(other.content ? other.content->clone() : nullptr)
	{
	}

	Any::~Any()
	{
		delete content;
	}

	Any& Any::swap(Any& rhs)
	{
		std::swap(content, rhs.content);
		return *this;
	}

	Any& Any::operator = (const Any::AnyEmpty& rhs)
	{
		delete content;
		content = nullptr;
		return *this;
	}

	Any& Any::operator = (const Any& rhs)
	{
		Any(rhs).swap(*this);
		return *this;
	}

	bool Any::empty() const
	{
		return !content;
	}

	const std::type_info& Any::getType() const
	{
		return content ? content->getType() : typeid(void);
	}

	void* Any::castUnsafe() const
	{
		return content ? static_cast<Any::Holder<void*> *>(this->content)->held : nullptr;
	}

} // namespace MyGUI