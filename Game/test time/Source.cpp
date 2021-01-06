#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <chrono>
#include <ctime>    
#include <string>
using namespace std;
string time_to_string(int t) {
	int m = t / 60;
	int s = t % 60;
	string res = "0";
	res += '0' + m;
	res += ':';
	res += '0' + s / 10;
	res += '0' + s % 10;
	return res;
}
int main()
{
    auto start = chrono::system_clock::now();
	cout << time_to_string(134) << endl;
    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
}