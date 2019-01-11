//
// Saucer.h
//

#include "Object.h"
 
class Saucer : public df::Object {
 private:
  void moveToStart();
  void out();
 
 public:
  Saucer();
  int eventHandler(const df::Event *p_e);
};
