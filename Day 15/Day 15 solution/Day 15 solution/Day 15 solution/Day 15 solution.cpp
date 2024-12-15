using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <deque>
ifstream fin("input.in");
ofstream fout("output.out");
map<char, pair<int, int>> mp;
char matrix[300][300];
int n, m;
int robotX, robotY;
string instructions;
void getInfo()
{
	string s;
	while (getline(fin, s))
	{
		if (s == "")
			break;
		m = s.size();
		for (int i = 0; i < m; i++)
		{
			matrix[n][i] = s[i];
			if (s[i] == '@')
			{
				robotX = n;
				robotY = i;
			}
		}
		n++;

	}

	while (getline(fin, s))
	{
		instructions += s;
	}
}

void getInfoP2()
{
	string s;
	int j = 0;
	while (getline(fin, s))
	{
		j = 0;
		if (s == "")
			break;
		m = 2 * s.size();
		for (int i = 0; i < m; i++)
		{
			
			if (s[j] == '@')
			{
				matrix[n][i] = s[j];
				robotX = n;
				robotY = i;
				i++;
				matrix[n][i] = '.';				
				j++;
			}
			else if (s[j] == 'O')
			{
				matrix[n][i] = '[';
				i++;
				matrix[n][i] = ']';
				j++;
			}
			else if (s[j] == '#')
			{
				matrix[n][i] = '#';
				i++;
				matrix[n][i] = '#';
				j++;
			}
			else if (s[j] == '.')
			{
				matrix[n][i] = '.';
				i++;
				matrix[n][i] = '.';
				j++;
			}						
		}
		n++;

	}

	while (getline(fin, s))
	{
		instructions += s;
	}



}

void tryToMove(char direction)
{
	int nextX = robotX + mp[direction].first;
	int nextY = robotY + mp[direction].second;
	if (matrix[nextX][nextY] == '.')
	{
		swap(matrix[robotX][robotY], matrix[nextX][nextY]);
		robotX += mp[direction].first;
		robotY += mp[direction].second;
	}
	else if (matrix[nextX][nextY] == 'O')
	{
		int whereToMoveX = nextX;
		int whereToMoveY = nextY;
		while (matrix[whereToMoveX][whereToMoveY] != '#')
		{
			whereToMoveX += mp[direction].first;
			whereToMoveY += mp[direction].second;
			if (matrix[whereToMoveX][whereToMoveY] == '.')
			{
				matrix[whereToMoveX][whereToMoveY] = 'O';
				matrix[nextX][nextY] = '@';
				matrix[robotX][robotY] = '.';
				robotX += mp[direction].first;
				robotY += mp[direction].second;
				break;				
			}
		}
	}

}

void showMatrix()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fout << matrix[i][j] << " ";
		}
		fout << '\n';
	}


}

void tryToMoveP2(char direction)
{
	int nextX = robotX + mp[direction].first;
	int nextY = robotY + mp[direction].second;
	
	if (matrix[nextX][nextY] == '.')
	{
		swap(matrix[robotX][robotY], matrix[nextX][nextY]);
		robotX += mp[direction].first;
		robotY += mp[direction].second;
		
	}
	else if ((matrix[nextX][nextY] == ']' || matrix[nextX][nextY] == '[') && (direction == '<' || direction == '>'))
	{
		int whereToMoveX = nextX;
		int whereToMoveY = nextY;
		while (matrix[whereToMoveX][whereToMoveY] != '#')
		{
			whereToMoveX += mp[direction].first;
			whereToMoveY += mp[direction].second;
			if (matrix[whereToMoveX][whereToMoveY] == '.')
			{
				while (matrix[whereToMoveX - mp[direction].first][whereToMoveY - mp[direction].second] != '@')
				{
					swap(matrix[whereToMoveX][whereToMoveY], matrix[whereToMoveX - mp[direction].first][whereToMoveY - mp[direction].second]);
					whereToMoveX -= mp[direction].first;
					whereToMoveY -= mp[direction].second;

				}
				matrix[robotX][robotY] = '.';
				robotX += mp[direction].first;
				robotY += mp[direction].second;
				matrix[robotX][robotY] = '@';
				break;
			}
		}
		
	}
	else if ((matrix[nextX][nextY] == ']' || matrix[nextX][nextY] == '[') && (direction == 'v' || direction == '^'))
	{
		deque<pair<int, int>> q;
		q.push_back({ nextX, nextY });
		if (matrix[nextX][nextY] == '[')
			q.push_back({ nextX, nextY + 1 });
		else q.push_back({ nextX, nextY - 1 });

		deque<pair<int, int>> bq = q;
		bool canMove = true;
		while (!q.empty())
		{
			pair<int, int> current = q.front();
			q.pop_front();
			int furtherX = current.first + mp[direction].first;
			int furtherY = current.second + mp[direction].second;
			if (matrix[furtherX][furtherY] == '[')
			{
				pair<int, int> further = { furtherX, furtherY };
				auto it = find(q.begin(), q.end(), further);
				if (it == q.end())
				{
					q.push_back({ furtherX,furtherY });
					q.push_back({ furtherX, furtherY + 1 });
					bq.push_back({ furtherX,furtherY });
					bq.push_back({ furtherX, furtherY + 1 });
				}
				
			}
			else if (matrix[furtherX][furtherY] == ']')
			{
				pair<int, int> further = { furtherX, furtherY };
				auto it = find(q.begin(), q.end(), further);
				if (it == q.end())
				{
					q.push_back({ furtherX,furtherY });
					q.push_back({ furtherX, furtherY - 1 });
					bq.push_back({ furtherX,furtherY });
					bq.push_back({ furtherX, furtherY - 1 });
				}				
			}
			else if (matrix[furtherX][furtherY] == '#')
			{
				canMove = false;
				break;
			}			
		}

		if (canMove)
		{
			while (!bq.empty())
			{
				pair<int, int> current = bq.back();
				bq.pop_back();
				int furtherX = current.first + mp[direction].first;
				int furtherY = current.second + mp[direction].second;
				swap(matrix[furtherX][furtherY], matrix[current.first][current.second]);
			}
			matrix[robotX + mp[direction].first][robotY + mp[direction].second] = '@';
			matrix[robotX][robotY] = '.';
			robotX += mp[direction].first;
			robotY += mp[direction].second;
		}
		
	}
	/*fout << '\n';
	fout << direction << '\n';
	showMatrix();*/
}


void solveFirstPart()
{
	getInfo();
	
	for (int i = 0; i < instructions.size(); i++)
	{
		tryToMove(instructions[i]);
	}

	long long sum = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (matrix[i][j] == 'O')
			{
				sum += 100 * i + j;
			}
		}
	}

	fout << sum;
}

void solveSecondPart()
{
	getInfoP2();
	
	for (int i = 0; i < instructions.size(); i++)
	{
		tryToMoveP2(instructions[i]);
	}

	long long sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (matrix[i][j] == '[')
			{
				sum += 100 * i + j;				
			}		
		}	
	}
	fout << '\n';
	showMatrix();
	fout << sum;

}

int main()
{
	mp['>'] = { 0,1 };
	mp['<'] = { 0, -1 };
	mp['v'] = { 1, 0 };
	mp['^'] = { -1,0 };
	//solveFirstPart();
	solveSecondPart();
	
}
