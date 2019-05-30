/*Constructor initialization lists 
 * the traditional method is inefficent, bc its not actually initialized
 * as they are created the traditional way.
 * 
 * using {} initializer you are initializing the value immediately 
 * compiler will initialize variables before the constructor body is executed.
 * note: initialization happens in order of how the variables were declared in class not constructor
*/

std::string name;
int value;

// Previous Traditional way
className::ObjectName() {
    name = "none"   //assignment not really initialization as the values were created up top
    value = 0;
}


// c++ 11 initialization list method
// values will be initalized immediately
className::ObjectName(std::string n_val, int v_value) 
    : name{n_val}, value{v_value} {
}
