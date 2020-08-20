
/* my tested and working method of using signals in the same class */

// header file
static void Int_hander(int signum);


//cpp
void Fault_tester::INT_handler(int signum)
{
	char c;
	signal(signum, SIG_IGN);
	printf("OUCH, did you hit Ctrl-C?\n Do you really want to quit?[y/n]\n");
	c= getchar();

	if (c == 'y' || c == 'Y')
	{
		
		return EXIT_SUCCESS;
	}
	else
	{
		signal(SIGINT, Fault_tester::INT_handler);
	}

	getchar(); // get new line char
	
}

void Fault_tester::int_kickoff()
{
	signal(SIGINT, Fault_tester::INT_handler);
}

std::int32_t Fault_tester::timing_test()
{
	std::cout << "Starting timing test" << std::endl;

	

	std::thread thread1(&Fault_tester::main_task,this);
	std::thread thread2(&Fault_tester::load_data,this);
	std::thread thread3_display_buffer(&Fault_tester::display_task, this);
	std::thread thread4_int_kickoff(&Fault_tester::int_kickoff, this);
	


	thread4_int_kickoff.join();

	thread3_display_buffer.join();
		thread2.join();
		thread1.join();
	std::cout << "Thread killed" << std::endl;
	return EXIT_SUCCESS;
}
