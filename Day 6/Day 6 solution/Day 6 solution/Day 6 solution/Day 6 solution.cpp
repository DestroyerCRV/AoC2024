using namespace std;
#include <iostream>
#include <set>
#include <fstream>
#include <utility>
ifstream fin("input.in");
ofstream fout("output.out");
set<pair<int, int>> distinctCoords;
char matrix[600][600];
int n, m;
string movement = "^>v<";
int diri[4] = { -1,0,1,0 };
int dirj[4] = { 0, 1,0,-1 };
int startX, startY;

void getLayout()
{
    string s;
    while (fin >> s)
    {
        m = s.size();
        for (int i = 0; i < s.size(); i++)
        {
            matrix[n][i] = s[i];
            if (matrix[n][i] == '^')
            {
                startX = n;
                startY = i;
            }
        }
        n++;
    }
}

void solveFirstPart()
{
    getLayout();
    int it = movement.find(matrix[startX][startY]);

    distinctCoords.insert({ startX, startY });
    while (startX >= 0 && startX < n && startY >= 0 && startY < m)
    {
        if (matrix[startX + diri[it]][startY + dirj[it]] != '#')
        {
            startX += diri[it];
            startY += dirj[it];
            distinctCoords.insert({ startX, startY });
        }
        else
        {
            if (it == 3)
                it = 0;
            else it++;
        }
    }

    fout << distinctCoords.size() - 1;
}


void solveSecondPart()
{
    getLayout();
    int backupX, backupY;
    backupX = startX;
    backupY = startY;
    int possibleLoops = 0;
    set<pair<int, int>> uniquePlacements;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != '#' && (i != backupX || j != backupY))
            {
                matrix[i][j] = '#';
                int Sisyphus = 0;
                startX = backupX;
                startY = backupY;
                auto it = movement.find(matrix[backupX][backupY]);
                while (startX >= 0 && startX < n && startY >= 0 && startY < m)
                {
                    if (matrix[startX + diri[it]][startY + dirj[it]] != '#')
                    {
                        startX += diri[it];
                        startY += dirj[it];                        
                    }
                    else
                    {
                        if (it == 3)
                            it = 0;
                        else it++;
                    }
                    Sisyphus++;
                    if (Sisyphus == 5685)
                    {                      
                        uniquePlacements.insert({ i,j });                       
                        matrix[i][j] = '.';
                        break;
                    }
                }
                matrix[i][j] = '.';
            }                 
        }
    }
    fout << uniquePlacements.size();
}


int main()
{
    //solveFirstPart();
    solveSecondPart();

}

