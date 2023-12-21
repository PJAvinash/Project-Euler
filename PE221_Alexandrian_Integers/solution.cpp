
#include <iostream>
#include <bits/stdc++.h>
#include <numeric>
#include <chrono>
#include <thread>
#include <future>
using namespace std;

long long gcd(long long a, long long b)
{
    while (b)
    {
        long long t = b;
        b = a - b * (a / b);
        a = t;
    }
    return a;
}

bool areCoprime(long long a, long long b)
{
    if (!(a & 1 || b & 1))
    {
        return false;
    }
    long long c = a - b;
    if (c == 1 || c == -1)
    {
        return true;
    }
    return (gcd(a, b) == 1);
}
// returns x >= 0 , such that ax = 1 mod b
long long inverse(long long a, long long b)
{
    if (a == 1 || b == 1)
    {
        return 1;
    }
    std::vector<long long> v;
    long long p = a;
    long long q = b;
    while (q)
    {
        long long x = p / q;
        long long t = p - x * q;
        p = q;
        q = t;
        v.push_back(x);
    }
    int k = v.size();
    long long P = 1;
    long long Q = v[k - 1];
    long long t = P;
    while (k--)
    {
        t = P;
        P = Q;
        Q = t - v[k] * Q;
    }
    P = P - (P / b) * b;
    if (P < 0)
    {
        P += b;
    }
    return P;
}

// pa - qb = +/- 1
bool addSolsFromBase(long long p, long long q, long long a, long long b, __int128_t max_limit, vector<long long> &alex)
{
    __int128_t n = (__int128_t)(p * b + q * a);
    __int128_t t = (__int128_t)(n * (n + p * p + q * q) * (n + a * a + b * b));
    bool atleastone = (t < max_limit);
    while (t < max_limit)
    {
        alex.push_back((long long)t);
        a += q;
        b += p;
        n = (p * b + q * a);
        t = n * (n + p * p + q * q) * (n + a * a + b * b);
    }
    return atleastone;
}

bool addSols(long long p, long long q, __int128_t max_limit, vector<long long> &alex)
{
    long long a = inverse(p, q);
    long long b = (p * a - 1) / q;
    bool atleastone1 = addSolsFromBase(p, q, a, b, max_limit, alex);
    long long c = q - a;
    long long d = (p * c + 1) / q;
    bool atleastone2 = addSolsFromBase(p, q, c, d, max_limit, alex);
    return (atleastone1 || atleastone2);
}

void removeDuplicates(vector<long long> &sorted_v, int resizeval)
{
    int St = 0;
    int En = 0;
    int s = sorted_v.size();
    for (En = 1; En < s; En++)
    {
        if (sorted_v[En] != sorted_v[St])
        {
            St++;
            sorted_v[St] = sorted_v[En];
        }
    }
    int NumbersToPop = En - St - 1;
    int NumbersToKeep = (s - (En - St - 1));
    NumbersToKeep = NumbersToKeep > resizeval ? resizeval : NumbersToKeep;
    sorted_v.resize(NumbersToKeep);
}

void addtrivial(int N, vector<long long> &alex)
{
    long long x1 = (N > 55108 ? 55108 : N) + 1;
    for (long long i = 1; i < x1; i++)
    {
        long long t = (i * (i + 1) * (1 + i + i * i));
        alex.push_back(t);
    }
    long long x2 = (N > 65536 ? 65536 : N) + 1;
    for (long long i = 1; i < x2; i += 2)
    {
        long long t = (i) * (i + 2) * (i + (i * i + 1) / 2);
        alex.push_back(t);
    }
}

long long getLimit(__int128_t MAX_ALEX)
{
    long long lim = (long long)cbrt((double)MAX_ALEX / 4);
    return lim + 2;
}
//returns a vector of first N Alexandrian Integers
vector<long long> calculateAlex(long long N)
{
    vector<long long> alex;
    addtrivial(N, alex);
    sort(alex.begin(), alex.end());
    removeDuplicates(alex, N);
    __int128_t MAX_ALEX = (__int128_t)alex[alex.size() - 1];
    long long lim = getLimit(MAX_ALEX);
    long long p_max = 2 + (long long)ceil(sqrt((double)lim / 2));
    for (long long p = 1; p < p_max; p++)
    {
        long long q_max = ceil(sqrt((double)(lim - p * p)));
        bool breakfor = true;
        for (long long q = p + 1; q < q_max && breakfor; q++)
        {
            if (areCoprime(p, q))
            {
                // p.a = 1 mod q;
                breakfor = addSols(p, q, MAX_ALEX, alex);
            }
        }
        if (alex.size() >= (N << 1))
        {
            sort(alex.begin(), alex.end());
            removeDuplicates(alex, N);
            MAX_ALEX = alex[alex.size() - 1];
            lim = getLimit(MAX_ALEX);
            q_max = ceil(sqrt((double)(lim - p * p)));
            p_max = 2 + (long long)ceil(sqrt((double)lim / 2));
        }
    }
    sort(alex.begin(), alex.end());
    removeDuplicates(alex, N);
    return alex;
}

vector<int> readInput()
{
    int q;
    scanf("%d", &q);
    vector<int> v{};
    for (int i = 0; i < q; i++)
    {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    return v;
}

void printResult(vector<long long> &R, vector<int> &Q)
{
    int s = Q.size();
    for (int i = 0; i < s; i++)
    {
        int index = Q[i] - 1;
        cout << R[index] << '\n';
    }
}

int main()
{
    vector<int> Q = readInput();
    int N = (*max_element(Q.begin(), Q.end()));
    vector<long long> R = calculateAlex(N);
    printResult(R, Q);
    return 0;
}