/* experimental playing cards std::cout
#include <iostream>
#include <clocale>

int main ()
{

	std::cout<<"\u1F0A1"; //ACE of spades card 
	std::cout<<"\u1F0A3"; //two of spades card 

	return 0;
}
Edit & Run



// Ἂ1Ἂ3
// Last edited on Mar 28, 2016 at 6:05pm
//   Mar 28, 2016 at 6:21pm
// Moschops (7244)
// What does this code give you:

// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
#include <iostream>
#include <clocale>

int main ()
{
	std::cout<<"🂡" << std::endl; //ACE of spades card 
	std::cout<<"\U0001F0A1" << std::endl; // \U for 32 bit unicode
	