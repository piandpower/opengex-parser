#pragma once

#include "OpenGEXCommon.h"

#include <algorithm>
#include <typeinfo>

namespace OGEXParser
{
	class DLL_OPENGEXPARSER_EXPORT Any
	{
	public:
		struct AnyEmpty { };
		static AnyEmpty Null;

		Any();
		Any(const Any::AnyEmpty& value);
		Any(const Any& other);

		template<typename ValueType>
		Any(const ValueType& value) :
			content(new Holder<ValueType>(value))
		{
		}

		~Any();

		Any& swap(Any& rhs);

		template<typename ValueType>
		Any& operator = (const ValueType& rhs)
		{
			Any(rhs).swap(*this);
			return *this;
		}

		Any& operator = (const Any::AnyEmpty& rhs);
		Any& operator = (const Any& rhs);

		bool empty() const;

		const std::type_info& getType() const;

		template<typename ValueType>
		ValueType* castType() const
		{
			if (this->getType() == typeid(ValueType))
				return &static_cast<Any::Holder<ValueType> *>(this->content)->held;
			return nullptr;
		}

		void* castUnsafe() const;

	private:
		class Placeholder
		{
		public:
			virtual ~Placeholder() { }

		public:
			virtual const std::type_info& getType() const = 0;
			virtual Placeholder* clone() const = 0;
		};

		template<typename ValueType>
		class Holder :
			public Placeholder
		{
		public:
			Holder(const ValueType& value) :
				held(value)
			{
			}

		public:
			virtual const std::type_info& getType() const
			{
				return typeid(ValueType);
			}

			virtual Placeholder* clone() const
			{
				return new Holder(held);
			}

		public:
			ValueType held;

		private:
			Holder& operator=(const Holder&) = delete;
		};

	private:
		Placeholder* content;
	};

}