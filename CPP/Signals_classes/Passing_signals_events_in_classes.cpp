
/* HOw to pass sigevent struct with classes/objects. */
//method 1 - part of class and access to class members

// header file - make it static 
static	const struct sigevent* hdlr(void *blah, int id);

// cpp file
const struct sigevent * Fault_tester::hdlr(void *not_used, int id)
{
	m_fault_cir_hal
	static int count = 0;
	if (++count > 1000)
	{
		count =0;
		return &int_event;
	}

	return NULL;
}


std::int32_t Fault_tester::timing_test()
{

	
	
	// struct sigevent int_event; // event to wake up the thread
	int id;
	int irq = SYSPAGE_ENTRY(qtime)->intr;		// Look here for registered interrupts. vector 2 for 32bit systems
	std::cerr << "Starting INterupt program" << irq<< std::endl;

	
	// Request I/O privileges
	// if (ThreadCtl(_NTO_TCTL_IO, 0) == -1)
	// {
	// 	perror( "ThreadCTL()");
	// 	return EXIT_FAILURE;
	// }


	// setup an event for the handler or the kernel to use to wake up this 
	// thread. Use whatever event you want

	SIGEV_INTR_INIT(&int_event);  // register event or Int Handler

	id = InterruptAttach(irq, hdlr, NULL,0, _NTO_INTR_FLAGS_TRK_MSK );
	if (id == -1)
	{
		perror("InterruptAttach()");
		return EXIT_FAILURE;
	}


	while (1)
	{
		// Block here and wait for event
		InterruptWait(0, NULL);

		printf("INTERRUPT Triggered!..\n");
	}

	return EXIT_SUCCESS;
	
}
//===============================================================================================================
//Method 2- not part fo the class

// declare this function here in the cpp file, no need to add member in header.h file.
const struct sigevent * hdlr(void *blah, int id)
{
	static int count = 0;
	if (++count > 1000)
	{
		count =0;
		return &int_event;
	}

	return NULL;
}



//create this member like normal 
std::int32_t Fault_tester::timing_test()
{

	
	
	// struct sigevent int_event; // event to wake up the thread
	int id;
	int irq = SYSPAGE_ENTRY(qtime)->intr;		// Look here for registered interrupts. vector 2 for 32bit systems
	std::cerr << "Starting INterupt program" << irq<< std::endl;

	
	// Request I/O privileges
	// if (ThreadCtl(_NTO_TCTL_IO, 0) == -1)
	// {
	// 	perror( "ThreadCTL()");
	// 	return EXIT_FAILURE;
	// }


	// setup an event for the handler or the kernel to use to wake up this 
	// thread. Use whatever event you want

	SIGEV_INTR_INIT(&int_event);  // register event or Int Handler

	id = InterruptAttach(irq, hdlr, NULL,0, _NTO_INTR_FLAGS_TRK_MSK );
	if (id == -1)
	{
		perror("InterruptAttach()");
		return EXIT_FAILURE;
	}


	while (1)
	{
		// Block here and wait for event
		InterruptWait(0, NULL);

		printf("INTERRUPT Triggered!..\n");
	}

	return EXIT_SUCCESS;
	
}
