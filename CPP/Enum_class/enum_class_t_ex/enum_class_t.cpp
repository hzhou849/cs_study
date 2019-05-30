/* 
 * Enum class with type definition
 * 
 */

#include <iostream>
#include "bitConvert.h"

enum class Cfg2 : std::uint16_t 
{
	OWD 	 = 0x8000,
	OWD_OFF  = 0x4000,
	DIS_OUT  = 0x2000,
	NOW		 = 0x1000,
	COS_VR1  = 0x0800,
	COS_VR0  = 0x0400,
	DOUT_SEL = 0x0100,
	DOUT	 = 0x0080,
	SD		 = 0x0040

};

// /* OSTREAM override for the enum class */
// // enable if only enum is passed
// template <typename T>
// std::ostream& operator << (typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& enumArg )
// {
// 	return stream << static_cast<typename std::underlying_type<T>::type> (enumArg);
// }


uint16_t display (Cfg2 regPos)
{
	std::cout <<std::showbase << std::hex<<"Register Position: " << static_cast<unsigned int>(regPos) << std::endl;
}

int main()
{
	display(Cfg2::OWD);
	bitConvert bc;

	// static_cast must be done before passing arg Cfg2 type into printBinary()
	bc.printBinary(static_cast<unsigned int>(Cfg2::COS_VR0));
}
