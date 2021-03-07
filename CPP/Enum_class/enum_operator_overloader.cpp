	// Overload Bit Manipulation operators to handle enums types

	// Multiplication * operator
	template<class data_type1, class data_type2>
	friend std::uint32_t operator* (const data_type1 value1, const data_type2 value2)
	{
		// Protect the data types passed into the template.
		// Testing seems that this will only be called when data_type is not recognized ie. enum

		return ( static_cast<std::uint32_t>(value1) * static_cast<std::uint32_t>(value2) );
	}

	// Addition + operator
	template<class data_type1, class data_type2>
	friend std::uint32_t operator+ (const data_type1 value1, const data_type2 value2)
	{
		return ( static_cast<std::uint32_t>(value1) + static_cast<std::uint32_t>(value2) );
	}

	// Mask AND & operator overload
	template<class data_type1, class data_type2>
	friend std::uint32_t operator& (const data_type1 value1, const data_type2 value2)
	{
		return ( static_cast<std::uint32_t>(value1) & static_cast<std::uint32_t>(value2) );
	}

	// Mask OR | Operator Overload
	template<class data_type1, class data_type2>
	friend std::uint32_t operator| (const data_type1 value1, const data_type2 value2)
	{
		return ( static_cast<std::uint32_t>(value1) | static_cast<std::uint32_t>(value2) );
	}
