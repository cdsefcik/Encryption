#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<sstream>
#include<iomanip>

using namespace std;

/*
*Chapter 25, TEA. This is the Tiny Encryption Algorithm.
*This was run for the output. Worked correctly. The decipher part was not implemented or run.
*The algorithm is in chapter 25, page 930-932 of the Programming Principles and Practice Using C++. 
*/


void error(string str) {
		cerr << str << endl;
	}


void encipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0;
	unsigned long delta = 0x9E3779B9;
	unsigned long n = 32;

	while (n-- > 0) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
	}
	w[0] = y; w[1] = z;
}

void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {
	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xC6EF3720;
	unsigned long delta = 0x9E3779B9;
	unsigned long n = 32;
	//sum delta<<5, in general sum = delta * n
	while (n-- > 0) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}
	w[0] = y; w[1] = z;
}

int main() {
	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;
	string op;
	string key;
	string infile;
	string outfile;
	cout << "please enter input file name, output file name, and key:\n";
	cin >> infile >> outfile >> key;
	while (key.size() < kchar) key += '0';  //pad key
	ifstream inf(infile.c_str());
	ofstream outf(outfile.c_str());
	if (!inf || !outf) error("bad file name");

	//Encipher Program
	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	unsigned long outptr[2];
	char inbuf[nchar];
	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	int count = 0;

	while (inf.get(inbuf[count])) {
		outf << hex; //use hexadecimal output
		if (++count == nchar) {
			encipher(inptr, outptr, k);
			//pad with leading zeros:
			outf << setw(8) << setfill('0') << outptr[0] << ' ' << setw(8) << setfill('0') << outptr[1] << ' ';
			count = 0;
		}

	}

	if (count) { //pad
		while (count != nchar) inbuf[count++] = '0';
		encipher(inptr, outptr, k);
		outf << outptr[0] << ' ' << outptr[1] << ' ';

	}

	//Decipher Page 934


	return 0;
}
