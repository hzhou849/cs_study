///
/// An iterator for ObjectLists
///

#ifndef __OBJECT_LIST_ITERATOR_H__
#define __OBJECT_LIST_ITERATOR_H__

#include "Object.h"
#include "ObjectList.h"

namespace df {

class ObjectList;

class ObjectListIterator {

 private:
  ObjectListIterator();	        ///< Iterator must be given list when created.
  int m_index;			///< Index into list.
  const ObjectList *m_p_list;	///< List iterating over.

 public:
  /// Create iterator, over indicated list.
  ObjectListIterator(const ObjectList *p_list);

  /// Set iterator to first item in list.
  void first();

  /// Set iterator to next item in list.
  void next();

  /// Return true if at end of list.
  bool isDone() const;

  /// Return pointer to current item in list, NULL if done/empty.
  Object *currentObject() const;     
  
  /// Assignment operator.
  ObjectListIterator &operator=(const ObjectListIterator &rhs);
  
  /// Set to new List.
  void setList(const ObjectList *p_list);
  
};

} // end of namespace df
#endif // __OBJECT_LIST_ITERATOR_H__
