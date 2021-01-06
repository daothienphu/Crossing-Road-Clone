#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <chrono>
#include <ctime>    
using namespace std;
int main()
{
    auto start = chrono::system_clock::now();
    int n;
    cin >> n;
    auto end = chrono::system_clock::now();

    chrono::duration<double> elapsed_seconds = end - start;
    time_t end_time = chrono::system_clock::to_time_t(end);

    cout << "finished computation at " << ctime(&end_time)
        << "elapsed time: " << elapsed_seconds.count() << "s\n";
}