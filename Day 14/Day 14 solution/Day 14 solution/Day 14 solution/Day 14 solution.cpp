using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
ifstream fin("input.in");
ofstream fout("output.out");
int matrix[120][120];
struct robot {
    int x;
    int y;
    int VX;
    int VY;
};
vector<robot> points;
map <int, int> mp;
void getInfo()
{
    string s;
    while (getline(fin, s))
    {
        stringstream X(s);
        string f;      
        string number = "";
        bool minus = false;
        robot robot;
        bool Allocated = false;
        while (getline(X, f, ' '))
        {
            for (int i = 0; i < f.size(); i++)
            {
                if (f[0] == 'p')
                {
                    if (isdigit(f[i]))
                    {
                        number += f[i];
                    }
                    else if (f[i] == ',')
                    {
                        robot.y = stoi(number);
                        number = "";
                    }

                }
                else if (f[0] == 'v')
                {
                    if (!Allocated)
                    {
                        robot.x = stoi(number);
                        Allocated = true;
                        number = "";
                    }
                        
                    if (f[i] == '-')
                    {
                        minus = true;
                    }
                    else if (isdigit(f[i]))
                    {
                        number += f[i];
                    }
                    else if (f[i] == ',')
                    {
                        robot.VY = stoi(number);
                        number = "";
                        if (minus)
                            robot.VY = -robot.VY;
                        minus = false;
                    }
                }
            }
            
        }
        robot.VX = stoi(number);
        if (minus)
            robot.VX = -robot.VX;
        points.emplace_back(robot);
    }
}

int checkQuadrant(robot a)
{
    if (a.x != 51 && a.y != 50)
    {
        if (a.x < 51 && a.y < 50)
            return 1;
        else if (a.x < 51 && a.y > 50)
            return 2;
        else if (a.x > 51 && a.y < 50)
            return 3;
        else if (a.x > 51 && a.y > 50)
            return 4;
    }
    return -1;
}

void solveFirstPart()
{
    getInfo();
    for (auto& currentPoint : points)
    {
        currentPoint.x = ((currentPoint.x + (currentPoint.VX * 100)) % 103);
        currentPoint.y = ((currentPoint.y + (currentPoint.VY * 100)) % 101);
        if (currentPoint.x < 0)
            currentPoint.x = 103 - abs(currentPoint.x);
        if (currentPoint.y < 0)
            currentPoint.y = 101 - abs(currentPoint.y);


        if (checkQuadrant(currentPoint) != -1)
        {
            mp[checkQuadrant(currentPoint)]++;
        }
    }
    long long ans = mp[1] * mp[2] * mp[3] * mp[4];
    fout << ans;
}

void solveSecondPart()
{
    getInfo();
    for (int time = 1; time < 100000; time++)
    {
        int seconds = 1;
        bool valid = true;

        for (int i = 0; i < 103; i++)
        {
            for (int j = 0; j < 101; j++)
            {
                matrix[i][j] = 0;
            }
        }


        for (auto& currentPoint : points)
        {
            currentPoint.x = ((currentPoint.x + (currentPoint.VX * seconds)) % 103);
            currentPoint.y = ((currentPoint.y + (currentPoint.VY * seconds)) % 101);
            if (currentPoint.x < 0)
                currentPoint.x = 103 - abs(currentPoint.x);
            if (currentPoint.y < 0)
                currentPoint.y = 101 - abs(currentPoint.y);

            matrix[currentPoint.x][currentPoint.y]++;
            if (matrix[currentPoint.x][currentPoint.y] > 1)
                valid = false;

            if (checkQuadrant(currentPoint) != -1)
            {
                mp[checkQuadrant(currentPoint)]++;
            }
        }
        if (valid)
        {
            for (int i = 0; i < 103; i++)
            {
                for (int j = 0; j < 101; j++)
                {
                    if (matrix[i][j] != 0)
                        fout << matrix[i][j] << " ";
                    else fout << "  ";
                }
                fout << '\n';
            }
            fout << time;
            break;
        }
       
    }
}

int main()
{
    //solveFirstPart();
    solveSecondPart();


}



