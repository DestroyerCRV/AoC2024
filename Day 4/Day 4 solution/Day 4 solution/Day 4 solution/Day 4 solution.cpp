using namespace std;
#include <iostream>
#include <string>
#include <fstream>
int diri[8] = { -1,-1, 0, 1, 1 , 1, 0, -1 };
int dirj[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
string word = "XMAS";
char matrix[200][200];
int n, m;
ifstream fin("input.in");
ofstream fout("output.out");
bool isValid(int x, int y)
{
	if (x >= 0 && x < n && y >= 0 && y < m)
		return true;
	
	return false;
}


int main()
{
	string s;
	int ans = 0, ans2 = 0;
	while (fin >> s)
	{
		m = s.size();
		for (int i = 0; i < m; i++)
			matrix[n][i] = s[i];

		n++;

	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			bool found;
			if (matrix[i][j] == 'X')
			{
				int x, y;
				
				for (int a = 0; a < 8; a++)
				{
					x = i, y = j;
					found = true;
					for (int b = 1; b <= 3; b++)
					{												
						x += diri[a];
						y += dirj[a];
						if (!isValid(x, y) || matrix[x][y] != word[b])
						{
							found = false;
							break;
						}
					}
					if (found)
						ans++;
				}
			}

			if (matrix[i][j] == 'A')
			{
				found = false;
				if (isValid(i - 1, j - 1) && isValid(i + 1, j + 1) && isValid(i - 1, j + 1) && isValid(i + 1, j - 1))
				{
					if (matrix[i - 1][j - 1] == 'M' && matrix[i + 1][j + 1] == 'S' && matrix[i - 1][j + 1] == 'M' && matrix[i + 1][j - 1] == 'S')
						found = true;
					else if (matrix[i - 1][j - 1] == 'S' && matrix[i + 1][j + 1] == 'M' && matrix[i - 1][j + 1] == 'S' && matrix[i + 1][j - 1] == 'M')
						found = true;
					else if (matrix[i - 1][j - 1] == 'M' && matrix[i + 1][j + 1] == 'S' && matrix[i - 1][j + 1] == 'S' && matrix[i + 1][j - 1] == 'M')
						found = true;
					else if (matrix[i - 1][j - 1] == 'S' && matrix[i + 1][j + 1] == 'M' && matrix[i - 1][j + 1] == 'M' && matrix[i + 1][j - 1] == 'S')
						found = true;


				}
				if (found)
					ans2++;
			}


		}
	}
	fout << ans << '\n';
	fout << ans2;
}


