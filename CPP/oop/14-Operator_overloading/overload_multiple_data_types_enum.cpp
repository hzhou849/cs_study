	void enum_test(int test);
	enum class AXI_MASK : std::uint32_t
	{
		VAR1 = 0x0004
	};


	friend std::ostream& operator << (std::ostream& os, const AXI_MASK& value1)
	{
		os << "enum overloaded: " << static_cast<std::uint32_t> (value1);
		return os;
	}

	template<class data_in1>
	friend std::uint32_t operator+ ( int lhs,  data_in1 rhs)
	{
		return (static_cast<uint32_t>(lhs) + static_cast<std::uint32_t>(rhs));

	}

or
	// Multiple data types
	template<class data_in1, class data_in2>
	friend std::uint32_t operator+ ( data_in1 lhs,  data_in2 rhs)
	{
		return (static_cast<uint32_t>(lhs) + static_cast<std::uint32_t>(rhs));

	}
