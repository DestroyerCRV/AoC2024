using namespace std;
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
ifstream fin("input.in");
ofstream fout("output.out");
#include <string>
#include <sstream>
map<string, vector<string>> mp;
vector<string> pageUpdates;
void getRules()
{
    string s;
    
    while (getline(fin,s))
    {
        if (s == "")
            break;
        stringstream X(s);
        string f;
        vector<string> v;
        while (getline(X, f, '|'))
        {
            v.emplace_back(f);
        }
        mp[v[0]].emplace_back(v[1]);
    }
}

void getUpdates()
{
    string s;
    while (getline(fin, s))
    {
        pageUpdates.emplace_back(s);           
    }
}




int main()
{
    getRules();
    getUpdates();
    int sumOfMiddles = 0, sumOfCorrectedMiddles = 0;
    for (auto& update : pageUpdates)
    {
        stringstream X(update);
        vector<string> v;
        string f;
        while (getline(X, f, ','))
        {
            v.emplace_back(f);
        }
        bool correctUpdate = true, correctedUpdate = false;
        for (int i = 0; i < v.size() - 1; i++)
        {
            vector<string> afterPages = mp[v[i]];
            auto it = find(afterPages.begin(), afterPages.end(), v[i + 1]);
            if (!(afterPages.size() != 0 && it != afterPages.end()))
            {
                correctUpdate = false;
                break;
            }
        }
        if (correctUpdate)
            sumOfMiddles += stoi(v[v.size() / 2]);

        for (int i = 0; i < v.size() - 1; i++)
        {
            vector<string> afterPages = mp[v[i]];
            auto it = find(afterPages.begin(), afterPages.end(), v[i + 1]);
            if (!(afterPages.size() != 0 && it != afterPages.end()))
            {
                swap(v[i], v[i + 1]);
                i = -1;
                correctedUpdate = true;
            }

        }
        if (correctedUpdate)
            sumOfCorrectedMiddles += stoi(v[v.size() / 2]);
    }

    fout << sumOfMiddles << '\n';
    fout << sumOfCorrectedMiddles;

}


