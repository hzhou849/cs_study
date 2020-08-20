// Copyright 2017 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

/* Display Buffer GUI █
 */


#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

#include "Disp_buffer.h"

namespace einstein
{
namespace zynq
{
namespace disp_buffer
{


	         
Disp_buffer::Disp_buffer(std::uint32_t col_count, std::uint32_t row_count)
:x{0}, y{0}, scr_buffer{nullptr}
{
	this->row_max = row_count;
	this->col_max = col_count;

	total_buffer_size = (col_max * row_max);

	// 2 methods you can do double array for contiguous memory single array for cells
	// Allocating one single contiguous array
	scr_buffer = new char [total_buffer_size * sizeof(char)];

	// Add '\n' to end of each row
	for (int i=0; i < total_buffer_size; i++)
	{
		if ( (i>= 0) && (i %col_max == 0) ) //greater or equal to zero! important
		{
			std::cerr<<"cell: " << i << std::endl;
			scr_buffer[i] = '\n'; // 0 -(n-1) index
		}
	}

	if (scr_buffer != nullptr)
	{
		std::cerr << "Screen Buffer Created\n" 
			<< "Rows: " << row_max << "\n"
			<< "Col: " << col_max << "\n"
			<< "Total size: "<< total_buffer_size << "\n"
			<< std::endl;
	}

}


Disp_buffer::~Disp_buffer()
{
	delete[] scr_buffer;
}


void Disp_buffer::dump_buffer()
{
	for (int i=0; i < total_buffer_size; i++)
	{
		// if (scr_buffer[i] == '\0')
		// {
		// 	std::cout << " " << "";
		// }
		// else if (scr_buffer[i] == '\n')
		// {
		// 	std::cout << "\'\\n'" << "\n";
		// }

		// top border
		if ( i>0 && i<col_max)
		{
			std::cout <<"=";
		}
		else if (i == col_max)
		{
			std::cout <<"=\n";
		}

		//show right edge   // does not work on linux empty space will compact
		else if (i > 0 && i%col_max == 0 )
		{
			std::cout <<"\n";
		}
		// bottom border
		else if (i>=((row_max -1) *col_max))
		{
			std::cout << "=";
		}
		//left edge
		// else if ( i > col_max &&  i%col_max == (1))
		// {
		// 	std::cout << "|";

		// }


		else
		{
			std::cout << scr_buffer[i] <<"\0";
		}
		
		
	}
	std::cout << std::endl; // flush buffer
	// clear_buffer();
}


// Dumps buffer with ruler
void Disp_buffer::dump_buffer_debug()
{
	std::uint32_t y_axis_ruler = 0;

	// Print the rulers X-Axis columns counter 
	std:: cout << "";
	for(int i=0; i<col_max; i++)
	{
		// For ruler number < 10 due to single char spacing?
		if (i < 10) 
		{
			std::cout << std::setw(2) << " " << i <<"";
		}
		else
		{
			std::cout << std::setw(1) << " " << i <<"";
		}

		if (i !=0 && i % col_max == 0)
		{
			std::cout << std::endl;
		}
	}

	std::cout << std::endl; // extra line btw each x-axis ruler for ease of readability


	// Print the Y-Axis rows coutner & dump the screen buffer
	for (int i=0; i<total_buffer_size; i++)
	{
		if (i % col_max	 == 1)
		{
			std::cout << std::setw(3) << std::left << y_axis_ruler;
			y_axis_ruler++;
		}

		if (scr_buffer[i] == '\0')
		{
			std::cout << std::setw(3) << std::left<<" " << "";
		}
		else if (scr_buffer[i] == '\n')
		{
			std::cout <<std::setw(3) << std::left <<"\'\\n'" << "\n";
			
		}
		else
		{
			std::cout << std::setw(3) << std::left << scr_buffer[i] << "";
		}
	}
	std::cout << std::endl; //flush buffer
}

/* Formula: (rowY *colMax + xCell#) = cellPosition */
void Disp_buffer::write_char(char data, std::uint32_t x, std::uint32_t y)
{

	std::uint32_t cell_pos = 0;
	cell_pos = (y * this->col_max + x);

	this->scr_buffer[cell_pos] = data;
}


void Disp_buffer::clear_buffer()
{
	// NOTE: Don't want to delete the cells adn the end of line with '\n' char
	for (int i=0; i < total_buffer_size; i++)
	{
		if (i % col_max !=0)
		{
			scr_buffer[i] = '\0';		// "erased blank char"
		}
	}
}


void Disp_buffer::reset_cursor_pos()
{
	// Order of this execution matters, adjust numbers as needed
	std::cout << "\033[50A"; 	// move cursor up 50 rows?
	std::cout << "\033[s";   	// Save the cursor position
	std::cout << "\033[2J";  	// Clear the screen
	std::cout << "\033[u";		// Restore the cursor position
	// std::cout <<"\[\033[0;36m\]"; // Cyan colour? may not be supported.
	// std::cout <<"\[\033[1;37m\]"; // bold grey?
	// std::cout <<"\033c";			//reset
	
}

void Disp_buffer::write_str(std::string s, std::uint32_t offset_x, std::uint32_t offset_y)
{
	volatile std::uint32_t str_size = s.length();
	
	// temp buffer for chars
	char char_array[str_size+1];
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//copy the contents of the string to char array
	strcpy(char_array, s.c_str());

	for (int i=0; i < str_size; i++)
	{
		// std::cout << i<<": "<<char_array[i]<< std::endl;; 
		write_char(char_array[i], offset_x + i, offset_y);
	}
	
	
}









}
}
}