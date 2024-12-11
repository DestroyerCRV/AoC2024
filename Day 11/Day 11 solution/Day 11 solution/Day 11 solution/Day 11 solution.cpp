using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <numeric>
ifstream fin("input.in");
ofstream fout("output.out");
vector<string> v;
map<long long, long long> mp;
map<long long, long long> auxMP;

void getInfo2()
{
    string s;
    getline(fin, s);
    stringstream X(s);
    string f;
    while (getline(X, f, ' '))
    {
        mp[stoi(f)]++;
    }
}

void getInfo()
{
    string s;
    getline(fin, s);
    stringstream X(s);
    string f;
    while (getline(X, f, ' '))
    {
        v.emplace_back(f);
    }
}

void solveFirstPart()
{
    getInfo();
    vector<string> aux;
    for (int i = 0; i < 25; i++)
    {
        for (auto& element : v)
        {
            if (element == "0")
                aux.emplace_back("1");
            else if (element.size() % 2 == 0)
            {
                string fH = element.substr(0, element.size() / 2);
                string sH = element.substr(element.size() / 2, element.size() / 2);
                aux.emplace_back(fH);
                aux.emplace_back(to_string(stoll(sH)));
            }
            else
                aux.emplace_back(to_string(stoll(element) * 2024));                        
        }

        v = aux;
        aux.clear();
    }
    fout << v.size();
}


void solveSecondPart()
{
    getInfo2();
    
    for (int i = 0; i < 75; i++)
    {
        //mp = auxMP;
        auxMP = mp;
        for (auto& element :auxMP)
        {
            if (element.second == 0)
                continue;

            if (element.first == 0)
            {
                mp[1] += element.second;
                mp[0] -= element.second;
            }
            else if (to_string(element.first).length() % 2 == 0)
            {
                string element_str = to_string(element.first);
                int new_len = element_str.length() / 2;
                int fH = stoi(element_str.substr(0, new_len));
                int sH = stoi(element_str.substr(new_len));
                mp[fH] += element.second;
                mp[sH] += element.second;
                mp[element.first] -= element.second;
                //auxMP = mp;
            }
            else
            {
                mp[element.first * 2024] += element.second;
                mp[element.first] -= element.second;
                //auxMP = mp;
            }
                                               
            //mp[element.first] = 0;
            //auxMP.erase(element.first);
        }
    }

    long long ans = 0;
    for (auto& i : mp)
    {
        ans += i.second;
        fout << i.second << " ";
    }
    fout << '\n';


    /*long long ans = accumulate(mp.begin(), mp.end(), 0, [&](int value, const map<string, int>:: value_type& mapa) {
        return value + mapa.second;
        });*/
    fout << ans;
}





int main()
{
    //solveFirstPart();
    solveSecondPart();

}


