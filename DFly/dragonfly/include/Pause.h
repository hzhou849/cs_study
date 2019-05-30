///
/// Pause
/// 

#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "EventKeyboard.h"
#include "Object.h"

#define DF_PAUSE_KEY df::Keyboard::PAUSE

namespace df {

class Pause: public Object {
 private:
  int m_pause_key;		///< Pause key.

 public:
  Pause(int init_pause_key = DF_PAUSE_KEY);
  int eventHandler(const Event *p_e);
};
 
} // end of namespace df
#endif // __PAUSE_H__
