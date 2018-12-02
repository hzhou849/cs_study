///
/// State.h
///

#ifndef STATE_H
#define STATE_H

#include "Object.h"

namespace df {

const std::string UNDEFINED_STATE = "__undefined state__";

class State {
 private:
  std::string m_state_type;      /// Name of state.

 public:
  State();
  virtual ~State();

  /// Set name of state.
  void setType(std::string new_type);

  /// Get name of state.
  std::string getType() const;

  /// Invoked when state first entered.
  virtual void Enter(Object *p_obj);

  /// Invoked every game loop step.
  virtual void Execute(Object *p_obj)=0;

  /// Invoked when state exited.
  virtual void Exit(Object *p_obj);
};

} // end of namespace df
#endif
