using namespace std;
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>
ifstream fin("input.in");
ofstream fout("output.out");
string s, decompressedInput;
string fileIdentifiers = "0123456789";
long long currentIdentifier;
vector<string> v;
void getInfo()
{
	fin >> s;
}

void decompressInput()
{
	
	for (long long i = 0; i < s.size(); i++)
	{
		
		if (i % 2 == 0)
		{
			bool validFile = false;
			for (long long j = 0; j < (s[i] - '0'); j++)
			{
				v.emplace_back(to_string(currentIdentifier));
				validFile = true;
			}
			
			if (validFile)
			{				
				currentIdentifier++;
			}
			
		}
		else
		{
			for (long long j = 0; j < (s[i] - '0'); j++)
			{
				v.emplace_back(".");
			}
		}
	}
}



void solveFirstPart()
{
	getInfo();
	decompressInput();

	long long i = 0, j = v.size() - 1;
	while (i < j)
	{
		if (v[i] == ".")
		{
			if (v[j] != ".")
			{
				swap(v[i],v[j]);
				i++;
				j--;
			}
			else j--;
		}
		else i++;
	}
	long long filesystemChecksum = 0;
	for (long long i = 0; i < v.size(); i++)
	{
		if (v[i] == ".")
			continue;
			
		filesystemChecksum += (i * stoi(v[i]));
	}

	fout << filesystemChecksum;
}





int main()
{
	solveFirstPart();



}


