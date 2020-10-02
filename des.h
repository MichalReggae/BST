#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


class DESClass {
public:

	ifstream inputstream;
	vector<string> round_keys;
	DESClass() {
		inputstream.open("rcvectest.txt");
		
	}
	~DESClass() {
		inputstream.close();
	}
	

	string hex_to_bin(string hex);

	string bin_to_hex(string s);

	string Xor(string a, string b);

	string dec_to_bin(int dec);

	int bin_to_dec(string bin);

	//string buffer_key(ifstream& inputstreamkey);
	string buffer_key();

	string shift_left(string word, int times);

	string show(string x) {
		return x;
	}

	//void generate_key(ifstream& inputstreamkey, vector<string>& round_keys);
	void generate_key();

	//string DES(string textEdit, vector<string> round_keys);
	string DES(string textEdit);

	//string DES_decryption(string crypted, vector<string>& round_keys);
	string DES_decryption(string textEdit);
};