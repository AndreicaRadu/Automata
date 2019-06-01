#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <string>
using namespace std;

int state[10001];
stack < char > S;
map < pair < int , pair < char , char > > , pair < int , string > > M;

int delta(int a , string word , int counter)
{
    if(S.empty() && counter < word.length())
    {
        if (M[make_pair(a, make_pair(word[counter], '.'))].first == 0)
            return 0;
        else
        {
            if(M[ make_pair( a , make_pair( word[counter] , '.' ) ) ].second != ".")
                for(int i=0 ; i<M[ make_pair( a , make_pair( word[counter] , '.' ) ) ].second.size() ; i++)
                    S.push(M[ make_pair( a , make_pair( word[counter] , '.' ) ) ].second[i]);
            counter++;
            return delta(a , word , counter);
        }
    }
    if(counter == word.length()) return a;
    if(M[ make_pair( a , make_pair( word[counter] , S.top() ) ) ].first == 0)
        return 0;
    else
    {
        char aux = S.top();
        S.pop();
        if(M[ make_pair( a , make_pair( word[counter] , aux ) ) ].second != ".")
            for(int i=0 ; i<M[ make_pair( a , make_pair( word[counter] , aux ) ) ].second.size() ; i++)
                S.push(M[ make_pair( a , make_pair( word[counter] , aux ) ) ].second[i]);

        a = M[ make_pair( a , make_pair( word[counter] , aux ) ) ].first;
        counter++;
        return delta(a , word , counter);
    }
}
int main()
{
    //===============READING DPDA DATA===============//
    ifstream fin("dpda.in");
    ofstream fout("dpda.out");
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
        int a , b;
        char x , y;
        string z;
        fin >> a >> x >> y >> b >> z;
        M[make_pair(a , make_pair(x , y))] = make_pair(b , z);
    }
//=======================================================//

    int nrc;
    fin >> nrc;
    for(int i=0 ; i<nrc ; i++)
    {
        S.push('$');
        string word;
        fin >> word;
        int a = delta(state[q] , word , 0);

        if(final[a] || S.empty())
            fout << "DA" << "\n";
        else
            fout << "NU" << "\n";
        while(!S.empty())
            S.pop();
    }
    return 0;
}