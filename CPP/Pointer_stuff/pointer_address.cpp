
/* c++ to get the address of something 
 * use static_cast<void*>(std::addressof(object));
 */ 

ptr= static_cast<void*>(std::addressof(a[i][j]));

std::cout << "a["<<i << "]" << "[" << j<<"]: " << a[i][j]<< " "<< ptr<< " "; // debug statement
// std::cout << static_cast<void*>(std::addressof(a[i][j])); // get the address of
// std::cout << a[i][j];