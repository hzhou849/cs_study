The move constructor is used instead of the copy constructor, if the object has type "rvalue-reference" (Type &&).
std::move() is a cast that produces an rvalue-reference to an object, to enable moving from it