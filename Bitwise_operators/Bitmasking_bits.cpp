const uint32_t PIN_NUMBER =3;                   //  1<<3 = 0x1000
			std::uint32_t var1 = ~(1<<(PIN_NUMBER & 0x1F)); // 0111
			var1 &= 0xff;
			std::uint32_t dir_reg = 0xfd;
			const  std::uint32_t DIR_INPUT = 0;
			const std::uint32_t DIR_OUTPUT = 1; 
			std::cerr <<std::showbase<<std::hex<< "var: " <<var1 << std::endl; // f7 = 1111 0111

		
			std::cerr << "dir_reg: " << dir_reg << std::endl; //fd = 1111 1101
			dir_reg &= ~(1 << (PIN_NUMBER & 0x1f));           //f7   1111 0111 
			std::cerr << "DIR_IN: " << dir_reg << std::endl; // f9 = 1111 0101

			//set bit do this
			dir_reg |= ~(1 << (PIN_NUMBER & 0x1f));         
