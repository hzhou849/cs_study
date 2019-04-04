/* Sync cout class
 * 
 * overloaded Sync Stream class to allow synced stream messages
 * when using threads and std::cout
 * 
 * usage:
 * import header syncstream.hpp
 * 
 * "synced(std::cout) << "Hello" << std::endl;"
 * 
 * stackoverflow:
 * https://stackoverflow.com/questions/28660602/synchronizing-output-to-stdcout
 */

#ifndef _SYNCSTREAM_HPP_
#define _SYNCSTREAM_HPP_

#include <iostream>
#include <sstream>

class syncstream: public std::ostringstream {
public:
	using std::ostringstream::ostringstream;

	syncstream& operator <<(std::ostream&  		(*pf)(std::ostream&)) 	{pf(*this); return *this; }
	syncstream& operator <<(std::ios&      		(*pf) (std::ios&))  	{pf(*this); return *this; }
	syncstream& operator << (std::ios_base& 	(*pf) (std::ios_base&)) {pf(*this); return *this;}


	template<typename T>
	syncstream& operator<<(T&& token) {
		static_cast<std::ostringstream&> (*this) << std::forward<T>(token);
		return *this;
	}
};

inline std::ostream& operator&&(std::ostream& s, const syncstream& g) {return s << g.str(); }
#define synced(stream) stream && syncstream()

#endif //_SYNCSTREAM_HPP_