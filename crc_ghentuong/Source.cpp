#include <string>
#include <stdio.h>
#include <iostream>
#include <bitset>
#include "crc_ghentuong.h"

using namespace std;

int main() {
	crc_ghentuong crc(0xD5);
	string x = crc.data_to_message("GhenTuong");
	cout << x << endl;
	cout << endl;
	cout << crc.check(x) << endl;
	cout << crc.message_to_data(x) << endl;
	cout << endl;
	system("pause");
}