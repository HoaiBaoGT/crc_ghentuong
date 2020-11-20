/*
*	Tran Hoai Bao (GhenTuong)
*	hoaibaoce@gmail.com
*/
#include "crc_ghentuong.h"

crc_ghentuong::crc_ghentuong(unsigned long input_crc) {
    if (((input_crc >> 63) != 0) || (input_crc == 0)) {
        // You are doing it wrong.
        return;
    }
    unsigned int find_crc_size = most_left_set_bit(input_crc);
    crc = input_crc | (1 << find_crc_size);
    crc_size = find_crc_size;
    crc_byte = crc_size >> 3; // or / 8. It is just my way ._.
}

string crc_ghentuong::data_to_message(string data) {
    // Extern byte for storing crc.
    string message = data;
    if ((crc == 0) || (crc_size == 0) || (crc_byte == 0)) {
        message.clear();
        return message;
    }
    for (int i = 0; i < crc_byte; i++) {
        message.push_back((char)0);
    }
    int length = message.length();
    unsigned long odd = 0;
    unsigned long ext = 0;
    for (int i = 0; i < length; i++) {
        for (int b = 7; b >= 0; b--) {
            ext = (message[i] >> b) & 0x1;
            odd = (odd << 1) | ext;
            if ((odd >> crc_size) > 0) {
                odd = odd ^ crc;
            }
        }
    }
    string key;
    for (int i = (crc_byte - 1); i >= 0; i--) {
        ext = (odd >> (i * 8)) & 0xFF;
        key.push_back((char)ext);
    }
    return data + string_to_hex(key);
}

bool crc_ghentuong::check(string message) {
    if ((crc == 0) || (crc_size == 0) || (crc_byte == 0)) {
        return false;
    }
    int key_pt_1 = message.length() - (crc_byte * 2);
    int key_pt_2 = message.length() - 1;
    if (key_pt_1 < 0) {
        return false;
    }
    string key = message.substr(key_pt_1, key_pt_2);
    if (key.empty()) {
        return false;
    }
    string data = message_to_data(message);
    if (data.empty()) {
        return false;
    }
    message = data + hex_to_string(key);
    int length = message.length();
    unsigned long odd = 0;
    unsigned long ext = 0;
    for (int i = 0; i < length; i++) {
        for (int b = 7; b >= 0; b--) {
            ext = (message[i] >> b) & 0x1;
            odd = (odd << 1) | ext;
            if ((odd >> crc_size) > 0) {
                odd = odd ^ crc;
            }
        }
    }
    if (odd == 0) {
        return true;
    }
    return false;
}

string crc_ghentuong::message_to_data(string message) {
    string data;
    int data_pt_1 = 0;
    int data_pt_2 = message.length() - (crc_byte * 2);
    if (data_pt_2 <= 0) {
        data.clear();
    }
    else {
        data = message.substr(data_pt_1, data_pt_2);
    }
    return data;
}

unsigned int crc_ghentuong::most_left_set_bit(unsigned long input) {
    int n = 0;
    while ((input >> n) != 0) {
        n++;
    }
    return n;
}

string crc_ghentuong::string_to_hex(string input) {
    string output;
    int shit;
    int input_length = input.length();
    for (int i = 0; i < input_length; i++) {
        shit = (input[i] >> 4) & 0xF;
        output.push_back((char)HEX[shit]);
        shit = input[i] & 0xF;
        output.push_back((char)HEX[shit]);
    }
    return output;
}

string crc_ghentuong::hex_to_string(string input) {
    string output;
    string s;
    int v;
    int input_length = input.length();
    for (int i = 0; i < input_length; i+=2) {
        s.clear();
        s.push_back(input[i]);
        s.push_back(input[i + 1]);
        try {
            v = stoi(s, nullptr, 16);
            output.push_back((char)v);
        }
        catch (exception) {}
    }
    return output;
}