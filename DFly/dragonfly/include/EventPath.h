///
/// An "pathfinding" event
///

#ifndef __EVENT_PATH_H__
#define __EVENT_PATH_H__

// Engine includes.
#include "Event.h"
#include "Path.h"

namespace df {

const std::string PATH_EVENT = "df::path";

enum SearchResult {
  NOT_FOUND,
  INCOMPLETE,
  FOUND,
};

class EventPath : public Event {

 private:
  SearchResult m_result;	///< Result of search.
  Path m_path;			///< Path found, if successful.

 public:
  EventPath();

  // Construct event with path.
  EventPath(Path path);

  // Set result.
  void setResult(SearchResult new_result);

  // Return result.
  SearchResult getResult() const;

  // Set path.
  void setPath(Path new_path);

  // Return path.
  Path getPath() const;
};

} // end of namespace df
#endif // __EVENT_PATH_H__
