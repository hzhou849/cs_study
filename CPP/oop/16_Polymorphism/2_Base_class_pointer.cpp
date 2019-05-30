/*18.4 Base Class pointer
 *
 * The base class pointers will now bind dynamically to corresponding dervived classes 
 * but the funtions must be declared as virtual for this to work

 * Just by adding the virtual keyword to your base and derived functions,
 * you can now make it dynamically bound

 */

// Example:
    // By using base class pointers, you can reference whatever derived class bounding
    // automatically. 
    // Device *d1 = new Device();
    // Device *d2 = new Ethernet_Dev();
    // Device *d3 = new Peripheral_Dev();
    // Device *d4 = new General_Dev();

    // Device *array [] = {d1, d2, d3, d4};

    // for (int i=0; i<4; ++i) {
    //     array[i]->set_bit(1);
    // }
    // delete the pointers




