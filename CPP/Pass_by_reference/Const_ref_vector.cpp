
// Pass by move instead of copy with a vector

// When using a unique pointe we cannot pass by copy so:
// NOTICE the use of const to protect the data
// for (auto p : vec ) // *ERROR we cannot refernce this pointer bc it is doing a copy
	// we have to do it by refernce - const to protect it
	for (const auto &p : vec )
	{
		std::cout << *p << std::endl;  // notice we have to use a pointer dereference here
	}
