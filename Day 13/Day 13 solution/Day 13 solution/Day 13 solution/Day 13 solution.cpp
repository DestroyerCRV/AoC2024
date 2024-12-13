using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
ifstream fin("input.in");
ofstream fout("output.out");
struct game {
    long long buttonAX;
    long long buttonAY;
    long long buttonBX;
    long long buttonBY;
    long long resultX;
    long long resultY;
};
vector<game> games;

void getInfo()
{
    string a, b, result;
    while (getline(fin, a) && getline(fin, b) && getline(fin, result))
    {
        fin.ignore();
        stringstream X(a);
        stringstream X2(b);
        stringstream X3(result);
        string f;
        string number = "";
        long long x = 0;
        game button;
        while (getline(X, f, ' '))
        {
            number = "";
            for (long long i = 0; i < f.size(); i++)
            {
                if (isdigit(f[i]))
                    number += f[i];
            }

            if (number != "" && x == 0)
            {
                button.buttonAX = stoll(number);
                x++;
            }
            else if (number != "" && x == 1)
            {
                button.buttonAY = stoll(number);
            }
        }
        x = 0;
        number = "";
        while (getline(X2, f, ' '))
        {
            number = "";
            for (long long i = 0; i < f.size(); i++)
            {
                if (isdigit(f[i]))
                    number += f[i];
            }

            if (number != "" && x == 0)
            {
                button.buttonBX = stoll(number);
                x++;
            }
            else if (number != "" && x == 1)
            {
                button.buttonBY = stoll(number);
            }
        }

        x = 0;
        number = "";
        while (getline(X3, f, ' '))
        {
            number = "";
            for (long long i = 0; i < f.size(); i++)
            {
                if (isdigit(f[i]))
                    number += f[i];
            }

            if (number != "" && x == 0)
            {
                button.resultX = (stoll(number) + 10e12);
                x++;
            }
            else if (number != "" && x == 1)
            {
                button.resultY = (stoll(number) + 10e12);
            }
        }
        games.emplace_back(button);
    }   
}

void solveFirstPart()
{
    getInfo();
    long long ans = 0;
    for (auto& currentGame : games)
    {
        long long APresses = 0;
        long long BPresses = 0;
        long long AX = currentGame.buttonAX * currentGame.buttonBY;
        long long BX = currentGame.buttonBX * currentGame.buttonAY;
        long long resultX = currentGame.resultX * currentGame.buttonBY;
        long long resultY = currentGame.resultY * currentGame.buttonBX;
        long long coordDif = abs(AX - BX);
        long long resultDif = abs(resultX - resultY);
        if (resultDif % coordDif == 0)
        {
            APresses = resultDif / coordDif;
            BPresses = (currentGame.resultX - (APresses * currentGame.buttonAX)) / currentGame.buttonBX;
            ans += (3 * APresses + BPresses);
        }
            
        

    }
    fout << ans;

}




int main()
{
    solveFirstPart(); // works for both parts


}


