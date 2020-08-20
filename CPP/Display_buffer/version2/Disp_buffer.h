// Copyright 2017 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.




#ifndef _EINSTEIN_DISPLAY_BUFFER_
#define _EINSTEIN_DISPLAY_BUFFER_



namespace einstein
{
namespace zynq
{
namespace disp_buffer
{
	
class Disp_buffer
{
public:
	Disp_buffer(std::uint32_t col_count, std::uint32_t row_count);
	~Disp_buffer();

	void write_str(std::string s, std::uint32_t offset_x, std::uint32_t offset_y);
	void write_char(char data, std::uint32_t x, std::uint32_t y);
	// void set_cursor_pos(std::uint32_t x, std::uint32_t y);
	void reset_cursor_pos();
	void clear_buffer();
	void dump_buffer();		//dump the buffer with ruler
	void dump_buffer_debug();

	
	std::uint32_t get_cursor_x();
	std::uint32_t get_cursor_y();
	
private:
	std::uint32_t x;
	std::uint32_t y;
	
	char *scr_buffer;
	// char *scr_buffer_ruled;

	std::uint32_t col_max;
	std::uint32_t row_max;
	std::uint32_t total_buffer_size; // col_max * row_max
	std::uint32_t last_position[2]; // last cursor position

};



}
}
}

#endif //_EINSTEIN_DISPLAY_BUFFER