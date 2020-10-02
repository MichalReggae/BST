
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "des.h"

//#using <system.dll>

using namespace std;
using namespace System::Diagnostics;

string DESClass::hex_to_bin(string hex) {
	unordered_map<char, string> map_hex_to_bin;
	map_hex_to_bin['0'] = "0000";
	map_hex_to_bin['1'] = "0001";
	map_hex_to_bin['2'] = "0010";
	map_hex_to_bin['3'] = "0011";
	map_hex_to_bin['4'] = "0100";
	map_hex_to_bin['5'] = "0101";
	map_hex_to_bin['6'] = "0110";
	map_hex_to_bin['7'] = "0111";
	map_hex_to_bin['8'] = "1000";
	map_hex_to_bin['9'] = "1001";
	map_hex_to_bin['A'] = "1010";
	map_hex_to_bin['B'] = "1011";
	map_hex_to_bin['C'] = "1100";
	map_hex_to_bin['D'] = "1101";
	map_hex_to_bin['E'] = "1110";
	map_hex_to_bin['F'] = "1111";
	string bin = "";
	for (int i = 0; i < hex.size(); i++) {
		bin += map_hex_to_bin[hex[i]];
	}
	return bin;
}

string DESClass::bin_to_hex(string s) {
	unordered_map<string, string> map_bin_to_hex;
	map_bin_to_hex["0000"] = "0";
	map_bin_to_hex["0001"] = "1";
	map_bin_to_hex["0010"] = "2";
	map_bin_to_hex["0011"] = "3";
	map_bin_to_hex["0100"] = "4";
	map_bin_to_hex["0101"] = "5";
	map_bin_to_hex["0110"] = "6";
	map_bin_to_hex["0111"] = "7";
	map_bin_to_hex["1000"] = "8";
	map_bin_to_hex["1001"] = "9";
	map_bin_to_hex["1010"] = "A";
	map_bin_to_hex["1011"] = "B";
	map_bin_to_hex["1100"] = "C";
	map_bin_to_hex["1101"] = "D";
	map_bin_to_hex["1110"] = "E";
	map_bin_to_hex["1111"] = "F";

	string hex = "";

	for (int i = 0; i < s.length(); i += 4) {
		string tmp = "";
		for (int j = 0; j < 4; j++) {
			tmp += s[i + j];
		}
		hex += map_bin_to_hex[tmp];
	}
	return hex;
}

string DESClass::Xor(string a, string b) {
	string result = "";
	int size = b.size();
	for (int i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			result += "1";
		}
		else {
			result += "0";
		}
	}
	return result;
}

string DESClass::dec_to_bin(int dec) {

	string binary;
	unsigned int mask = 0x00000080;
	for (int i = 0; i < 8; i++) {
		if (dec & mask) {
			binary += '1';
		}
		else {
			binary += '0';
		}
		mask >>= 1;
	}

	return binary;
}

int DESClass::bin_to_dec(string bin) {
	int temp = 0;
	for (int i = 0; i < bin.size(); i++) {
		if ((bin[bin.size() - 1 - i]) == '1') {
			temp += pow(2, i);
		}
	}
	return temp;
}



string DESClass::buffer_key() {
	string key;
	int temp;
	int n = 0;
	string tempstr;
	if (inputstream.is_open()) {
		while (n < 8) {
			inputstream >> temp;

			key += dec_to_bin(temp);
			n++;
		}
	}
	return key;
}

string DESClass::shift_left(string word, int times) {
	string temp;
	for (int i = 0; i < times; i++) {
		for (int j = 1; j < 28; j++) {
			temp += word[j];
		}
		temp += word[0];
		word = temp;
		temp = "";
	}
	return word;
}

void DESClass::generate_key() {
	string key = buffer_key();
	round_keys.clear();

	int key56_permutation[56] =
	{ 57,49,41,33,25,17,9,
		1,58,50,42,34,26,18,
		10,2,59,51,43,35,27,
		19,11,3,60,52,44,36,
		63,55,47,39,31,23,15,
		7,62,54,46,38,30,22,
		14,6,61,53,45,37,29,
		21,13,5,28,20,12,4
	};

	int compression_permutation[48] =
	{ 14,17,11,24,1,5,
		3,28,15,6,21,10,
		23,19,12,4,26,8,
		16,7,27,20,13,2,
		41,52,31,37,47,55,
		30,40,51,45,33,48,
		44,49,39,56,34,53,
		46,42,50,36,29,32
	};
	int shift_key_tab[16] =
	{ 1, 1, 2, 2,
		2, 2, 2, 2,
		1, 2, 2, 2,
		2, 2, 2, 1
	};
	string new_key;
	for (int i = 0; i < 56; i++) {
		new_key += key[key56_permutation[i] - 1];
	}
	string new_key_left = new_key.substr(0, 28);
	string new_key_right = new_key.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		new_key_left = shift_left(new_key_left, shift_key_tab[i]);
		new_key_right = shift_left(new_key_right, shift_key_tab[i]);

		string new_key_combined = new_key_left + new_key_right;
		string round_key;
		for (int i = 0; i < 48; i++) {
			round_key += new_key_combined[compression_permutation[i] - 1];
		}
		round_keys.push_back(round_key);

	}

}


string DESClass::DES(string textEdit) {
	textEdit = hex_to_bin(textEdit);
	Debug::Write("test");
	int initial_permutation[64] =
	{ 58,50,42,34,26,18,10,2,
		60,52,44,36,28,20,12,4,
		62,54,46,38,30,22,14,6,
		64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,
		59,51,43,35,27,19,11,3,
		61,53,45,37,29,21,13,5,
		63,55,47,39,31,23,15,7
	};
	int expansion_d_box[48] =
	{ 32,1,2,3,4,5,4,5,
		6,7,8,9,8,9,10,11,
		12,13,12,13,14,15,16,17,
		16,17,18,19,20,21,20,21,
		22,23,24,25,24,25,26,27,
		28,29,28,29,30,31,32,1
	};

	int s_boxes[8][4][16] =
	{ {
		14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
	},
	{
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
	},


	{
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
	},
	{
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
	},
	{
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
	},
	{
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
	},
	{
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
	},
	{
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
	} };

	int permutation_tab[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};

	int final_permutation[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};

	string pre_crypted_word;
	for (int i = 0; i < 64; i++) {
		pre_crypted_word += textEdit[initial_permutation[i] - 1];

	}

	string pre_cypted_word_left = pre_crypted_word.substr(0, 32);
	string pre_cypted_word_right = pre_crypted_word.substr(32, 32);

	for (int i = 0; i < 16; i++) {
		string pre_cypted_word_right_exp;
		for (int i = 0; i < 48; i++) {
			pre_cypted_word_right_exp += pre_cypted_word_right[expansion_d_box[i] - 1];
		}
		string after_xor = Xor(round_keys[i], pre_cypted_word_right_exp);
		string res;
		for (int i = 0; i < 8; i++) {
			string row1 = after_xor.substr(i * 6, 1) + after_xor.substr(i * 6 + 5, 1);
			int row = bin_to_dec(row1);
			string col1 = after_xor.substr(i * 6 + 1, 1) + after_xor.substr(i * 6 + 2, 1) + after_xor.substr(i * 6 + 3, 1) + after_xor.substr(i * 6 + 4, 1);;
			int col = bin_to_dec(col1);
			int val = s_boxes[i][row][col];
			res += dec_to_bin(val);
		}
		string word_after_pertab;
		for (int i = 0; i < 32; i++) {
			word_after_pertab += res[permutation_tab[i] - 1];
		}

		after_xor = Xor(word_after_pertab, pre_cypted_word_left);

		pre_cypted_word_left = after_xor;

		if (i < 15) {
			string temp = pre_cypted_word_right;
			pre_cypted_word_right = after_xor;
			pre_cypted_word_left = temp;
		}
	}
	string combined_text = pre_cypted_word_left + pre_cypted_word_right;
	string ciphertext;
	for (int i = 0; i < 64; i++) {
		ciphertext += combined_text[final_permutation[i] - 1];
	}
	ciphertext = bin_to_hex(ciphertext);
	return ciphertext;
}

string DESClass::DES_decryption(string crypted) {
	reverse(round_keys.begin(), round_keys.end());
	
	return DES(crypted);
}

/*
int main()
{
	ifstream inputstream("rcvectest.txt");
	vector <string> round_keys;
	generate_key(inputstream, round_keys);

	string textEdit = "ABCDEF1234132DEF";
	string cipher = DES(textEdit, round_keys);
	cout << "Cipher: " << cipher << endl;

	string decrypted = DES_decryption(cipher, round_keys);

	cout << "Decrypted word: " << decrypted << endl;

	generate_key(inputstream, round_keys);
	textEdit = "ABCDEF1234132DEF";
	cipher = DES(textEdit, round_keys);
	cout << "Cipher: " << cipher << endl;

	decrypted = DES_decryption(cipher, round_keys);

	cout << "Decrypted word: " << decrypted << endl;

	inputstream.close();
	return 0;
}*/
