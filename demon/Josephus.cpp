#include <vector>
#include<iostream>
#include<cstdlib>
using namespace std;

int josephus(int n, int m) {
	vector<bool> stay(n,true);	// stay[i]=true indicates person i in the circle
	int k = n, j = -1;			// k: the number of persons who stay in the circle

	while (k > 1) {
		int i = 0;
		while(i<m) {
			j = (j + 1) % n;	// index of j is increased by one,
			if (stay[j]) ++i;	// only persons in the cirlce are counted	
		}
		stay[j] = false;		// person j out
		k--;					// the number of remaining people -- 
	} 
	int i;
	for (i = 0; i < n; ++i) if (stay[i]) break;
	return i;
}

int josephus2(int n, int m) {
	vector<int> stay(n);	
	for (int i = 0; i < n; ++i) stay[i] = i;

	int j = 0;			
	while (stay.size() > 1) {
		j = (j + m-1) % stay.size();
		stay.erase(stay.begin() + j);		 
	}

	return stay[0];
}

int josephus3(int n, int m) {
	if (n == 1) return 0;
	return (josephus3(n - 1, m) + m ) % n;
}

int main() {
	int n, m;

	cout << "please give n and m :";
	cin >> n >> m;
	cout << josephus(n, m)<<endl;
	cout << josephus2(n, m) << endl;
	cout << josephus3(n, m) << endl;
	system("pause");
}