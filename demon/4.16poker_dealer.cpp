#include <iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<string>
#include<iomanip>
using namespace std;

void deal_card1() {
	char suit[4] = { 'S','H','D','C' };
	string rank[13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};
	vector<string> card;
	for (int i = 0; i < 13; ++i) {
		for (int j = 0; j < 4; ++j) {
			card.push_back(suit[j]+ rank[i]);
		}
	}
	vector<vector<string>> player(4);
	
	for (int i = 0; i < 52; ++i) {		//deal card
		int idx = rand() % card.size();
		player[i % 4].push_back(card[idx]);
		card.erase(card.begin() + idx);
	}

	cout << "Go:" << endl;
	for (int i = 0; i < 4; ++i) {
		for (auto &c : player[i])
			cout <<setw(5)<< c;
		cout << endl;
	}

}

void deal_card2() {
	char suit[4] = { 'S','H','D','C' };
	string rank[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
	vector<string> card;
	for (int i = 0; i < 13; ++i) {
		for (int j = 0; j < 4; ++j) {
			card.push_back(suit[j] + rank[i]);
		}
	}

	for (int i = 0; i < 26; ++i) {	//shufle 
		int idx1 = rand() % card.size(), idx2 = rand() % card.size();
		string c= card[idx1];
		card[idx1] = card[idx2];
		card[idx2] = c;
	}

	vector<vector<string>> player(4);
	for (int i = 0; i < 52; ++i) {	//deal card
		player[i % 4].push_back(card[i]);
	}

	cout << "Go:" << endl;
	for (int i = 0; i < 4; ++i) {
		for (auto &c : player[i])
			cout << setw(5) << c;
		cout << endl;
	}

}

int main()
{	
	srand(time(nullptr));
	deal_card1();
	deal_card2();
	return 0;
}