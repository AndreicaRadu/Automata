#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int T[1000][26][1000];
int* delta(int* v , string s , int counter)
{
    if(counter == s.length()) return v;
    int w[10001] = { 0 };
    for(int i=1 ; i<=10000 ; i++)
    {
        if(v[i] == 1)
        {
            for(int j=1 ; j<=T[i][(int)s[counter]-97][0] ; j++)
                w[T[i][(int)s[counter]-97][j]] = 1;
        }
    }
    counter++;
    return delta(w , s , counter);
}
int main()
{
//=========READING NFA DATA=========//
    ifstream fin("nfa.in");
    ofstream fout("nfa.out");
    int nrs, nrl, aux, state[10001];
    char letter[26];
    fin >> nrs;
    for (int i = 1; i <= nrs; i++)
    {
        fin>>aux;
        state[aux] = i;
    }
    fin >> nrl;
    for (int i = 0; i < nrl; i++)
        fin >> letter[i];
    int q;
    fin >> q;
    int nrf, final[10001] = {0};
    fin >> nrf;
    for (int i = 0; i < nrf; i++)
    {
        fin >> aux;
        final[state[aux]] = 1;
    }
    int nrt;
    fin >> nrt;
    for (int i = 0; i < nrt; i++)
    {
        int a, c;
        char b;
        fin >> a >> b >> c;
        int d = b;
        T[state[a]][d - 97][0]++;
        T[state[a]][d - 97][T[state[a]][d - 97][0]] = state[c];
    }
//===================================//
    int nrc;
    fin>>nrc;
    string s;
    getline(fin,s);
    for(int i=0 ; i<nrc ; i++)
    {
        string s;
        getline(fin,s);
        int v[10001] = { 0 };
        v[state[q]] = 1;
        int* w = delta(v , s , 0);

        int k = 0;
        for(int j=1 ; j<=10000 ; j++)
            if(final[j] && w[j] && k==0)
            {
                fout<<"DA"<<"\n";
                k=1;
            }
        if(k==0) fout<<"NU"<<"\n";
    }
    return 0;
}