using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <tuple>
ifstream fin("input.in");
ofstream fout("output.out");
char matrix[500][500];
bool visitedPerimeter[501][501];
bool visited[501][501];
int n, m;
int diri[4] = { -1, 0, 1, 0 };
int dirj[4] = { 0, 1, 0 , -1 };
vector<tuple<int, int, int>> DIRI = { {0, -1, -1}, {0, -1, - 1}, {0, 1, 1}, {0, 1, 1} };
vector<tuple<int, int, int>> DIRJ = { {-1, 0, -1}, {1, 0, 1}, {1, 0, 1}, {-1, 0, -1} };

struct point {
    int x;
    int y;
};
bool isValid(point a)
{
    if (a.x >= 0 && a.x < n && a.y >= 0 && a.y < m)
        return true;
    return false;
}
int isExteriorCorner(point Point)
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        point vecin1, vecin2;
        vecin1.x = Point.x + get<0>(DIRI[i]);
        vecin1.y = Point.y + get<0>(DIRJ[i]);
        vecin2.x = Point.x + get<1>(DIRI[i]);
        vecin2.y = Point.y + get<1>(DIRJ[i]);
        if (!isValid(vecin1) && !isValid(vecin2))
        {
            sum++;
            fout << "C1" << '\n';
        }                        
        else if (matrix[vecin1.x][vecin1.y] != matrix[Point.x][Point.y] && matrix[vecin2.x][vecin2.y] != matrix[Point.x][Point.y])
        {
            sum++;
            fout << "C3" << '\n';
        }
            
    }
    return sum;
}

int isInteriorCorner(point Point)
{
    int sum = 0;
    for (int i = 0; i < 4; i++)
    {
        point vecin1, vecin2, vecin3;
        vecin1.x = Point.x + get<0>(DIRI[i]);
        vecin1.y = Point.y + get<0>(DIRJ[i]);
        vecin2.x = Point.x + get<1>(DIRI[i]);
        vecin2.y = Point.y + get<1>(DIRJ[i]);
        vecin3.x = Point.x + get<2>(DIRI[i]);
        vecin3.y = Point.y + get<2>(DIRJ[i]);
        if (isValid(vecin1) && isValid(vecin2) && isValid(vecin3))
        {
            if (matrix[vecin1.x][vecin1.y] == matrix[vecin2.x][vecin2.y] && 
                matrix[vecin3.x][vecin3.y] != matrix[Point.x][Point.y] && 
                matrix[vecin3.x][vecin3.y] != matrix[vecin1.x][vecin1.y] && 
                matrix[vecin1.x][vecin1.y] == matrix[Point.x][Point.y])
            {
                sum++;
                fout << "E" << '\n';
            }               
        }                     
    }

    return sum;
}

void getInfo()
{
    string s;
    while (getline(fin, s))
    {
        m = s.size();
        for (int i = 0; i < s.size(); i++)
        {
            matrix[n][i] = s[i];
        }
        n++;
    }
}

void solveFirstPart()
{
    getInfo();
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if (!visited[i][j])
            {
                int area = 0, perimeter = 0;
                char plotType = matrix[i][j];
                visited[i][j] = true;
                queue<point> q;
                point initial;
                initial.x = i;
                initial.y = j;
                q.push(initial);
                
                while (!q.empty())
                {
                    area++;
                    point node = q.front();
                    q.pop();
                    for (int k = 0; k < 4; k++)
                    {
                        point vecin;
                        vecin.x = node.x + diri[k];
                        vecin.y = node.y + dirj[k];
                        if (isValid(vecin) && matrix[vecin.x][vecin.y] == plotType && !visited[vecin.x][vecin.y])
                        {
                            q.push(vecin);
                            visited[vecin.x][vecin.y] = true;
                        }
                        else if (!isValid(vecin) || matrix[vecin.x][vecin.y] != plotType)
                        {
                            perimeter++;
                        }
                    }
                }
                ans += perimeter * area;
            }        
        }
    }
    fout << ans;
}


void solveSecondPart()
{

    getInfo();
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!visited[i][j])
            {
                int area = 0, sides = 0;
                char plotType = matrix[i][j];
                visited[i][j] = true;
                queue<point> q;
                point initial;
                initial.x = i;
                initial.y = j;
                q.push(initial);
              
                while (!q.empty())
                {
                    area++;
                    point node = q.front();
                    q.pop();

                    sides += isExteriorCorner(node);
                    sides += isInteriorCorner(node);

                    for (int k = 0; k < 4; k++)
                    {
                        point vecin;
                        vecin.x = node.x + diri[k];
                        vecin.y = node.y + dirj[k];
                        if (isValid(vecin) && matrix[vecin.x][vecin.y] == plotType && !visited[vecin.x][vecin.y])
                        {
                            q.push(vecin);
                            visited[vecin.x][vecin.y] = true;
                        }                      
                    }
                }
                fout << sides << " for region " << plotType << '\n';
                ans += sides * area;
            }
        }
    }
    fout << ans;
}



int main()
{
    
    //solveFirstPart();
    solveSecondPart();
}

