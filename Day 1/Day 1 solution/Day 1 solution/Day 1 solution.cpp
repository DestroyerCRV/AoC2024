using namespace std;
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
typedef long long ll;
ifstream fin("input.in");
ofstream fout("output.out");
map<ll, ll> secondListMap;
int main()
{
	ll a, b, ans = 0,secondAns = 0;
	vector<ll> firstList, secondList;
	
	while (fin >> a >> b)
	{
		firstList.emplace_back(a);
		secondList.emplace_back(b);
		secondListMap[b]++;
	}
	sort(firstList.begin(), firstList.end());
	sort(secondList.begin(), secondList.end());

	for (ll i = 0; i < firstList.size(); i++)
	{
		ans += abs(firstList[i] - secondList[i]);		
		secondAns += firstList[i] * secondListMap[firstList[i]];
	}
	fout << "Total distance between the left list and the right list: " << ans << '\n';
	fout << "Total similarity score: " << secondAns;
}


