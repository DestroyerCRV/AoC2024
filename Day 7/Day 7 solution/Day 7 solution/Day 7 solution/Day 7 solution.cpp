using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
ifstream fin("input.in");
ofstream fout("output.out");
vector<long long> v;
string backupEquation;
string equation;
long long result;

vector<string> splitStringByDelimiters(string& inputString,
    string& delimiters)
{

    vector<string>
        result; // Vector to store the split substrings
    long long startPos = 0;
    long long endPos = 0;

    // Loop until endPos is not equal to string::npos
    while ((endPos = inputString.find_first_of(delimiters,
        startPos))
        != string::npos) {

        if (endPos != startPos) { // Checking if the
            // substring is non-empty
            result.push_back(inputString.substr(
                startPos, endPos - startPos));
        }

        startPos
            = endPos + 1; // Update startPos to the position
        // after the delimiter
    }

    // Extract the substring from startPos to the end of the
    // string and add it to result
    if (startPos != inputString.length()) {
        result.push_back(inputString.substr(startPos));
    }
    return result;
}
bool getInfoP2()
{
    string s;
    getline(fin, s);
    //cout << s << '\n';

    string delimiters = ":";
    if (s == "")
        return false;
    vector<string> x = splitStringByDelimiters(s, delimiters);
    result = stoll(x[0]);
    s = x[1];
    s.erase(s.begin());
    equation = s;
    backupEquation = s;

    return true;
}

bool getInfo()
{
    string s;
    getline(fin, s);
    //cout << s << '\n';
    string delimiters = ": ";
    if (s == "")
        return false;
    vector<string> x = splitStringByDelimiters(s, delimiters);
    result = stoll(x[0]);
    for (long long i = 1; i < x.size(); i++)
        v.emplace_back(stoll(x[i]));
    return true;
}

long long sumOfResults = 0;
void solveFirstPart()
{
    //srand(time(NULL));
    while (getInfo())
    {
        // 0 is + and 1 is *
        for (long long j = 0; j < 1000000; j++)
        {
            long long ans;

            long long n = rand() % 2;
            if (n == 0)
                ans = v[0] + v[1];
            else
                ans = v[0] * v[1];

            for (long long i = 2; i < v.size(); i++)
            {
                n = rand() % 2;
                if (n == 0)
                    ans += v[i];
                else ans *= v[i];

                if (ans > result)
                    break;

            }
            if (ans == result)
            {
                
                sumOfResults += result;
                break;
            }
               
        }
        
        v.clear();
    }
    fout << sumOfResults;
    
}

void solveSecondPart()
{
    
    while (getInfo())
    {
        srand(time(NULL));
        // 0 is + and 1 is *
        for (long long j = 0; j < 1000000; j++)
        {          
            long long ans = v[0];
            for (int i = 1; i < v.size(); i++)
            {
                int n = rand() % 3;
                if (n == 0)
                    ans += v[i];
                else if (n == 1)
                    ans *= v[i];
                else
                {
                    string tmp = to_string(ans);
                    tmp += to_string(v[i]);
                    ans = stoll(tmp);
                }

            }
           
            if (ans == result)
            {
                fout << "found " << result << '\n';
                sumOfResults += result;
                v.clear();
                break;
            }
            
        }
        v.clear();
    }
    fout << sumOfResults;

}


int main()
{
    
    //solveFirstPart();
    solveSecondPart();
    
    // concatenarea nu are prioritate

   

}


