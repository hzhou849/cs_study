/* Delegating constructors 
 * use delgating to avoid re-writing the same code in overloaded constructors
 * do this by writing the most overloaded constructor first and manually pass
 * argument values in for the missing parameters for lesser constructors
 * 
 * only works for initialization lists
 * also cannot delegate 
 */


std::string name;
int value1; 
int value2;

// NOTE: both caller and delegated bodies will run
className::Object (std::string n_value, int v1, int v2) 
    : name{n_val}, value1 {v1}, value2{v2}{
    std::cout << "3 args constructor" << std::endl; // this line should run when other constructors are called.
    
}
className::Object() 
    : name {"None", 0,0} {  // delegate to the most overloaded (first) constructor
    std::cout<<"no args constructor" << std::endl; //this line should not execute until after jump to delegated constructor
}
className::Object(std::string n_value)
    : name{n_value, 0, 0} {
}