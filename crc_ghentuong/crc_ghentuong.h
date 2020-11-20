/*
*	Tran Hoai Bao (GhenTuong)
*	hoaibaoce@gmail.com
*/
#include <string>
using namespace std;

class crc_ghentuong {
	public:
		crc_ghentuong(unsigned long input_crc);
		string data_to_message(string data);
		string message_to_data(string message);
		bool check(string message);
	private:
		const char HEX[17] = "0123456789ABCDEF";
		unsigned long crc;
		unsigned int crc_size; // bits for storing odd.
		unsigned int crc_byte; // bytes/characters for storing odd.
		unsigned int most_left_set_bit(unsigned long input);
		string string_to_hex(string input);
		string hex_to_string(string input);
};
/*
* How to use this:
* Copy crc_ghentuong.h and crc_ghentuong.cpp to where you find convenient in your project.
* - To include the library in your code.
* #include "crc_ghentuong.h"
* Change "crc_ghentuong.h" to the path where you put the two files.
* 
* crc_ghentuong crc(0xD5);
* init crc with 0xD5 = 11010101 = 213. This is a crc 8 bits.
* The divisor is actually 111010101 = 0x1D5.
* Since the highest bit are always 1, so putting 11010101 to input is enough.
* This is the most common way to write crc polynomial.
* Only those crcs from 1 to 63 bit are supported.
* 
* - To get the encoded message from data:
* string mesage = crc.data_to_message(data);
* 
* - To check it the message is correct (not being corrupted).
* if (crc.check(message)) {
*     // correct.
* }
* else {
*     // corrupted.
* }
* 
* - To get data from message:
* string data = crc.message_to_data(message);
* 
*/

