using namespace std;
#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
ifstream fin("input.in");
ofstream fout("output.out");
struct point {
	int x;
	int y;


};
unordered_map<char, vector<point>> mp;
int n = 0, m = 0;
void getInfo()
{
	string s;
	
	while (getline(fin, s))
	{
		for (int i = 0; i < s.size(); i++)
		{
			m = s.size();
			if (islower(s[i]) || isupper(s[i]) || isdigit(s[i]))
			{
				mp[s[i]].push_back({ n, i });
				fout << "found point at " << n << " " << i << '\n';
			}
		}
		n++;
	}


}
bool checkMatrix[300][300];

bool isValid(point Point)
{
	if (Point.x >= 0 && Point.x < n && Point.y >= 0 && Point.y < m)
		return true;
	return false;
}

point computeCandidate(point Point, point tendency)
{
	point candidate;
	candidate.x = Point.x + tendency.x;
	candidate.y = Point.y + tendency.y;
	return candidate;

}

void solveFirstPart()
{
	getInfo();
	int distinctAntinodes = 0;
	for (auto& coordinates : mp)
	{
		for (int i = 0; i < coordinates.second.size() - 1; i++)
		{
			for (int j = i + 1; j < coordinates.second.size(); j++)
			{
				point point1 = coordinates.second[i];
				point point2 = coordinates.second[j];
				fout << "point1 " << point1.x << " " << point1.y << '\n';
				fout << "point2 " << point2.x << " " << point2.y << '\n';
				point antinode1, antinode2;
				antinode1.x = (point1.x - point2.x) + point1.x;
				antinode1.y = (point1.y - point2.y) + point1.y;
				antinode2.x = (point2.x - point1.x) + point2.x;
				antinode2.y = (point2.y - point1.y) + point2.y;
				fout << "an1 " << antinode1.x << " " << antinode1.y << '\n';
				fout << "an2 " << antinode2.x << " " << antinode2.y << '\n';
				if (isValid(antinode1))
				{
					if (!checkMatrix[antinode1.x][antinode1.y])
					{
						checkMatrix[antinode1.x][antinode1.y] = true;
						distinctAntinodes++;
					}
				}
				if (isValid(antinode2))
				{
					if (!checkMatrix[antinode2.x][antinode2.y])
					{
						checkMatrix[antinode2.x][antinode2.y] = true;
						distinctAntinodes++;
					}
				}
			}
		}


	}
	fout << distinctAntinodes;

}

void solveSecondPart()
{
	getInfo();
	int distinctAntinodes = 0;
	for (auto& coordinates : mp)
	{
		for (int i = 0; i < coordinates.second.size() - 1; i++)
		{
			for (int j = i + 1; j < coordinates.second.size(); j++)
			{
				point point1 = coordinates.second[i];
				point point2 = coordinates.second[j];
				if (!checkMatrix[point1.x][point1.y])
				{
					checkMatrix[point1.x][point1.y] = true;
					distinctAntinodes++;
				}
				if (!checkMatrix[point2.x][point2.y])
				{
					checkMatrix[point2.x][point2.y] = true;
					distinctAntinodes++;
				}
				fout << "point1 " << point1.x << " " << point1.y << '\n';
				fout << "point2 " << point2.x << " " << point2.y << '\n';
				point tendency1, tendency2;
				tendency1.x = (point1.x - point2.x);
				tendency1.y = (point1.y - point2.y);
				tendency2.x = (point2.x - point1.x);
				tendency2.y = (point2.y - point1.y);
				fout << "tend1 " << tendency1.x << " " << tendency1.y << '\n';
				fout << "tend2 " << tendency2.x << " " << tendency2.y << '\n';
				
				point candidate = computeCandidate(point1, tendency1);
				while (isValid(candidate))
				{
					if (!checkMatrix[candidate.x][candidate.y])
					{
						checkMatrix[candidate.x][candidate.y] = true;
						distinctAntinodes++;
					}
					candidate = computeCandidate(candidate, tendency1);
				}
				candidate = computeCandidate(point2, tendency2);
				while (isValid(candidate))
				{
					if (!checkMatrix[candidate.x][candidate.y])
					{
						checkMatrix[candidate.x][candidate.y] = true;
						distinctAntinodes++;
					}
					candidate = computeCandidate(candidate, tendency2);
				}
			}
		}
	}
	fout << distinctAntinodes;
}



int main()
{
	//solveFirstPart();
	solveSecondPart();







}


