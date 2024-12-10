using namespace std;
#include <iostream>
#include <fstream>
ifstream fin("input.in");
ofstream fout("output.out");
#include <queue>
#include <string>
#include <vector>

struct point {
    int x;
    int y;
};
vector<point> zeroLocations;
char matrix[400][400];
bool visited[400][400];
int n, m;
int diri[4] = { -1, 0, 1, 0 };
int dirj[4] = { 0, 1, 0, -1 };
bool isValid(point a)
{
    if (a.x >= 0 && a.x < n && a.y >= 0 && a.y < m)
        return true;
    return false;
}

void getInfo()
{
    string s;
    while (getline(fin, s))
    {
        m = s.size();
        for (int i = 0; i < m; i++)
        {
            matrix[n][i] = s[i];
            if (s[i] == '0')
            {
                point Point;
                Point.x = n;
                Point.y = i;
                zeroLocations.emplace_back(Point);
            }
        }
        n++;
    }


}

void solveFirstPart()
{
    getInfo();
    int totalSum = 0;
    for (auto& zero : zeroLocations)
    {
        queue<point> q;
        q.push(zero);
        int sum = 0;
        while (!q.empty())
        {
            
            point node = q.front();
            q.pop();
            if (matrix[node.x][node.y] == '9')
                sum++;

            for (int i = 0; i < 4; i++)
            {
                point vecin;
                vecin.x = node.x + diri[i];
                vecin.y = node.y + dirj[i];
                if (isValid(vecin) && !visited[vecin.x][vecin.y] && matrix[vecin.x][vecin.y] - '0' == (matrix[node.x][node.y] - '0') + 1)
                {
                    visited[vecin.x][vecin.y] = true;
                    q.push(vecin);
                }         
            }

        }
        totalSum += sum;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                visited[i][j] = false;

    }
    fout << totalSum;
}

void solveSecondPart()
{
    getInfo();
    int totalSum = 0;
    for (auto& zero : zeroLocations)
    {
        queue<point> q;
        q.push(zero);
        int sum = 0;
        while (!q.empty())
        {

            point node = q.front();
            q.pop();
            if (matrix[node.x][node.y] == '9')
                sum++;

            for (int i = 0; i < 4; i++)
            {
                point vecin;
                vecin.x = node.x + diri[i];
                vecin.y = node.y + dirj[i];
                if (isValid(vecin) && matrix[vecin.x][vecin.y] - '0' == (matrix[node.x][node.y] - '0') + 1)
                {                  
                    q.push(vecin);
                }
            }

        }
        totalSum += sum;
    }
    fout << totalSum;
}


int main()
{
    //solveFirstPart();
    solveSecondPart();





}




