// sudoku.cpp:
//

#include "stdafx.h"
#include "EndProducer.h"
#include "SolveSudoku.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

int main(int argc,char** argv)
{
	clock_t start, finish;
	double totaltime;
	start = clock();

	if (argv[1][0] == '-' && argv[1][1] == 'c')
	{
		int Nums = atoi(argv[2]);
		if (Nums < 1 || Nums > 1000000) 
		{
			cout << "The Paramter must be positive[1, 10^6]!! Program exit abnormally......" << endl;
		}
		else 
		{
			EndProducer EP(Nums);
			EP.MainOperation();
		}
	}
	else if (argv[1][0] == '-' && argv[1][1] == 's')
	{
		int line = -1;
		int count = 0;
		int bufferMartix[81] = { 0 };
		int bufferFlag[81] = { 0 };
		SolveSudoku ss;
		string filepath;
		string buffer;
		string linestr;
		filepath = argv[2];

		fstream infile(filepath.c_str());
		fstream outfile(filepath.c_str());
		if (!infile)
		{
			cout << "Unable to open the file. Exit" << endl;
			exit(1);
		}
		buffer.assign(istreambuf_iterator<char>(infile), istreambuf_iterator<char>());
		stringstream strStr;
		strStr.str(buffer);

		do
		{
			for (int i = 0; linestr[i] != '\0'; i++) 
			{
				if (linestr[i] >= '0' && linestr[i] <= '9') 
				{
					bufferMartix[count] = linestr[i] - '0';
					if(linestr[i] != '0')
					{
						bufferFlag[count] = 1;
					}
					else
					{
					    bufferMartix[count] = NUM0;
					}
					count++;
				}
				else 
				{
					continue;
				}
			}
			line++;
			if (linestr == "\n" || line == 9)
			{
				//Solve the sudoku
				ss.setPuzzle(bufferMartix);
				ss.setFlag(bufferFlag);
				if (ss.Fill(0))
				{
					//$to do: find an efficent way to output to file
					for (int j = 0; j < 81; j++)
					{
						outfile << ss.getPuzzle()[j];
						if ((j + 1) % 9 == 0)
						{
							outfile << '\n';
							continue;
						}
						if (j < 81)
						{
							outfile << ' ';
						}
					}
					outfile << '\n';
				}
				memset(bufferFlag, 0, sizeof(int) * 81);
				memset(bufferMartix, 0, sizeof(int) * 81);
				ss.setPuzzle(bufferMartix);
				ss.setFlag(bufferFlag);
				count = 0;
				line = -1;
				continue;
			}
		} while (getline(strStr, linestr));
		cout << "Solved Sudoku!" << endl;
	}
	else if (argv[1][0] == '-' && argv[1][1] == 't') {
		string filepath;
		string buffer;
		string linestr;
		int zeroNum = -1;
		int zero_Count = 0;
		int zero_index = -1;
		int line = 0;
		filepath = argv[2];

		fstream infile(filepath.c_str());
		fstream outfile(filepath.c_str());
		if (!infile)
		{
			cout << "Unable to open the file. Exit" << endl;
			exit(1);
		}
		buffer.assign(istreambuf_iterator<char>(infile), istreambuf_iterator<char>());
		stringstream strStr;
		strStr.str(buffer);

		srand((unsigned)time(NULL));
		while (getline(strStr, linestr))
		{
			if (linestr[0] >= '1' && linestr[0] <= '9')
			{
				zeroNum = (rand() % 3) + 4;
				zero_Count = 0;
				while (true)
				{
					if (zero_Count < zeroNum)
					{
						if (line % 10 == 0)
						{
							zero_index = (rand() % 8) + 1;
						}
						else
						{
							zero_index = rand() % 9;
						}
						if (linestr[2 * zero_index] == '0')
						{
							continue;
						}
						linestr[2 * zero_index] = '0';
						zero_Count++;
					}
					else
					{
						outfile << linestr;
						outfile << "\n";
						break;
					}
				}
			}
			else 
			{
				outfile << "\n";
			}
			line++;
		}
	}

	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\nProgram time is " << totaltime << "s!" << endl;
    return 0;
}

