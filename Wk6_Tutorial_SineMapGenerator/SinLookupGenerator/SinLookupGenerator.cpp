// SinLookupGenerator.cpp : Generates a pre computed Sin Lookup Table
//

#include <iostream>
#include <fstream>
#include <iomanip>

//Size and Math Defines

#define M_PI 3.1415926535f
#define SIN_SIZE 512
#define SIN_FP 12

int main()
{
    //Write out Header
	std::fstream header;
	header.open("sinlut.h", std::ios_base::out);
	header << "/*\nSine Lookup Table with" << SIN_SIZE << "entiries, \n" << SIN_FP << "fixeds \n*/\n\n";
	header << "#define sin_lut_len" << SIN_SIZE*2 << "\n";
	header << "#define sin_lut_size" << SIN_SIZE << "\n\n";
	header << "extern const short sin_lut[" << SIN_SIZE << "]\n" << std::endl;
	header.close();

	//Write out C File
	std::fstream cfile;
	cfile.open("sinlut.c", std::ios_base::out);
	cfile << "sin_lut[" << SIN_SIZE << "]=\n{";

	//Short for casted sin val
	unsigned short shortSinVal;

	for (int i = 0; i < SIN_SIZE; i++) {
		
		//Get Sin Value
		float sinVal = sin(i * 2 * M_PI / SIN_SIZE);
		sinVal = sinVal * (1 << SIN_FP);

		//Convert sin Val to Short
		shortSinVal = (unsigned short)(sinVal);

		//If we have written 8 values this line then go on to
		//a new line
		if (i % 8 == 0) {
			cfile << "\n\t";
		}

		//Write value to file
		cfile << "0x" << std::hex << std::setw(4) << std::setfill('0') << shortSinVal << ",";
	}

	cfile << "\n};\n" << std::endl;

	cfile.close();

	return 0;

}
