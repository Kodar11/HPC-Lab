#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of Fibonacci terms: ";
    cin >> n;

    vector<long long> fib(n);
    fib[0] = 0;
    fib[1] = 1;

    #pragma omp parallel
    {
        #pragma omp single
        {
            cout << "Thread " << omp_get_thread_num() << " initializing first terms\n";
        }

        for (int i = 2; i < n; i++) {
            #pragma omp critical
            {
                fib[i] = fib[i - 1] + fib[i - 2];
                cout << "Thread " << omp_get_thread_num()
                     << " computed fib[" << i << "] = " << fib[i] << "\n";
            }
        }
    }

    cout << "\nFibonacci Series: ";
    for (int i = 0; i < n; i++)
        cout << fib[i] << " ";
    cout << endl;

    return 0;
}
