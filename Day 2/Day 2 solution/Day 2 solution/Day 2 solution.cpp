using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
ifstream fin("input.in");
ofstream fout("output.out");
bool isSafe(vector<int> v)
{
	bool increasing = false;
	

	if (v[1] != v[0] && abs(v[1] - v[0]) <= 3)
	{
		if (v[1] > v[0])
			increasing = true;	
	}
	else
	{
		return false;
	}

	for (int i = 1; i < v.size(); i++)
	{
		if (v[i] == v[i - 1] || abs(v[i] - v[i - 1]) > 3)
			return false;
		else if (v[i] > v[i - 1] && !increasing)
			return false;
		else if (v[i] < v[i - 1] && increasing)
			return false;
	}
	return true;

}


int main()
{
	string s;
	int Safe = 0;
	while (getline(fin, s))
	{
		stringstream X(s);
		string t;		
		vector<int> v, backup;
		while (getline(X, t, ' '))
		{
			v.emplace_back(stoi(t));
		}
		backup = v;	
		for (int i = 0; i < v.size(); i++)	
		{
			if (isSafe(v))
			{
				Safe++;
				break;
			}
			else 
			{
				v.erase(v.begin() + i);
				if (isSafe(v))
				{
					Safe++;
					break;
				}
			}
			v = backup;
		}
		
	}
	fout << Safe;
}


