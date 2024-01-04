/*
MOKETO KD 202100173
THABANA NJ 202100058
MOLAPO LS 202100013
MAH00ANA.C.D 202100036
LETUKA M.I 202100190
MOLAKALAKA T 202101925
PITSO MS 202004683

*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//An array of  opcodes
string opcodes[8]={"add","sub","and","or","addi","subi", "jmp","call"};
//array that stores opcodes in binary
string opcode_in_binary[8]={"00000/00", "00000/01", "00000/11", "00001/00", "00010/00","00010/01", "00101/11","00110"};

string REGISTER[14]={"$zero","$at","$v1","$v0","$a0","$a1", "$a2","$a3","$t0","$t1","$t2","$s0","$s1","$ra"};
string REGISTER_in_binary[14]={"00000", "00001", "00010", "00011","00100","00101","00110","00111","01000","01001","01010","01011","01100","01101"};

//pointer to array that is going to store instructions from the text file
string *instructions;

//stores opcodes only
string *OpcodeArray;


//length of the array of instructions
int length = 0;

//function that opens the text file and insert the instructions from the file into the array
string *openFile(string file_name)
{
	string line;
	instructions = new string[10000];// allocation of memory
	ifstream file (file_name);// This is the function that reads the file loaded into the emulator

	if(file.is_open())		// checks if the file is successfully opened
    {
  		while(!file.eof())// when its not the end of file we keep getting the lines
		{
			getline( file,line);
			instructions[length] = line;	// insert each line in the array of instruction
			length++;// to keep track of how many times we insert into the array

		}
		file.close();
		length = length;
	}
	else	//notifies the user that the file did not open
	{
		cout << "Unable to open the file" << endl;
	}
	return instructions;
}

// separates the opcode from the rest of the instruction string
string *get_Opcode(string *instructions, int length)
{
	int pos;//position of the space/separator between opcode and the registers

	OpcodeArray = new string[length];// allocate memory


	// Find position of the first whitespace using find()
	for(int i = 0; i < length; i++)
	{
	    pos = instructions[i].find(" ");

	    // Copy substring before pos
		OpcodeArray[i] = instructions[i].substr(0 , pos);
	}

	return OpcodeArray;
}

// function that translates each opcode into its binary value
string *Encode(string OpcodeArray[], string opcodes[], string opcode_in_binary[], int length)
{
	// defining an array that will store opcodes that are in binary
	string *instruction_opcodeBinary;
	instruction_opcodeBinary = new string[length];

	//looping through the instructions and saerching through the opcodes array to insert each of the binary opcode into their corresponding positions
	for(int i = 0; i< length; i++)
	{
		string token = OpcodeArray[i];
		for(int j=0; j<=37; j++)//looping through the opcodes
		{
			if(token == opcodes[j]){
				instruction_opcodeBinary[i] = opcode_in_binary[j];// inserting the binary opcode into the instruction_opcodeBinary
			}
		}
	}
	return instruction_opcodeBinary;
}

// concatenate the instruction array with the binary opcodes
void Assemble(string *encodedArray, string instructions[],int length)
{
	for (int i=0; i<length; i++){

		int InstrLen = instructions[i].length();// variable to store length of a single instruction

	    for(int j=0; j<InstrLen; j++){	//loops throught an instruction.


	            //string check = Instruction[i];
	            int check = instructions[i].find(" ");

	         	//replace the op-codes with binary coded op codes
				instructions[i].replace(0, check, encodedArray[i]);
        }
        cout << instructions[i] << endl;
    }
}

int main()
{
	string filename;
	cout<<" ENTER FILE NAME [FILENAME] : ";
	cin>>filename;
	string *openedfile = openFile(filename+".txt");
	cout<< length  << "\n\n\n";

	for(int i = 0; i < length; i++)
	{
		cout << *(Encode(get_Opcode(openedfile, length), opcodes, opcode_in_binary, length)+i) << endl;
	}

	cout << "\n\n";

	Assemble(Encode(get_Opcode(openedfile, length), opcodes, opcode_in_binary, length), openedfile, length);


return 0;
 }
