#include<string>
#include<iostream>
#include<vector>
using namespace std;

const vector<wstring> e2 = { // 7 x 4
	L" '...'",
	L" l'l'l",
	L".'l'l'.",
	L"' ' ' '"
};
int width(vector<wstring> wstr) {
	int max = 0;
	for (int i = 0; i < wstr.size(); i++) {
		cout << i << " " << wstr[i].length() << " " << max << endl;
		if (wstr[i].length() > max)
			max = wstr[i].length();
	}
	return max;
}
int height(vector<wstring> wstr) { return wstr.size(); }

int main() {
	cout << width(e2) << endl << height(e2);
	return 0;
}