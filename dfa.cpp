#include <iostream>
#include <fstream>
using namespace std;
int T[1000][26] , state[10001];

int delta(int a , string s , int counter)
{
    if(counter == s.length()) return a;
    if(!T[a][s[counter]-97])
        return 0;
    else a = T[a][s[counter]-97];

    counter++;
    return delta(a , s , counter);
}

int main()
{
//=========READING DFA DATA=========//
    ifstream fin("dfa.in");
    ofstream fout("dfa.out");
    int nrs, nrl, aux;
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
        T[state[a]][d - 97] = state[c];
    }
//===================================//
    int nrc;
    fin>>nrc;
    string s;
    getline(fin,s);
    for(int i=0 ; i<nrc ; i++)
    {
        getline(fin,s);

        int a = delta(state[q] , s , 0);

        if(final[a]) fout<<"DA"<<"\n";
        else fout<<"NU"<<"\n";
    }
    return 0;

}