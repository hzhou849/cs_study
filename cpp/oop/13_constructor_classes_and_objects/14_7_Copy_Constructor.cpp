/* 14.7 Copy constructor 
 * if using pointers always user define your copy constructor
 * NOTE if member of object is a pointer, only the pointer will be copied,
 * not what it is being pointed to. (shallow copy)
 *
 * SYNTAX:
 * const - is to prevent any changes to source object
 * "TYPE::TYPE(const Type &source_obj);" - passing the object by reference not copy otherwise you will 
 *  be redundantly copying a copy and cause recursive calls
 * Example
 * 
 * Obj_Name::Obj_Name(const Obj_Name &source)
 *  : name{source.name}, value1{source.value1}, value2{source.value2}{
 *  }
 * 
 */



