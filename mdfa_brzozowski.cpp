#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <map>
using namespace std;
ofstream fout("dfa.out");
int T[1000][26] , state[10001] , nrs , nrl , aux , q , nrt , nrf, final[10001];
int Tn[1000][26][1000] , qn[10001] , fn , finaln[10001];
int Tf[1000][26] , nrsf , statef[10001] , qf , nrff = 0 , finalf[10001];
char letter[26];
set<set<int>> S;
map< set<int> , int> mp;

void read()
{
    ifstream fin("dfa.in");
    fin >> nrs;
    for (int i=1 ; i<=nrs ; i++)
    {
        fin>>aux;
        state[aux] = i;
    }
    fin >> nrl;
    for (int i = 0; i < nrl; i++)
        fin >> letter[i];
    fin >> q;
    fin >> nrf;
    for (int i = 0; i < nrf; i++)
    {
        fin >> aux;
        final[state[aux]] = 1;
    }
    fin >> nrt;
    for (int i = 0; i < nrt; i++)
    {
        int a, c;
        char b;
        fin >> a >> b >> c;
        int d = b;
        T[state[a]][d - 97] = state[c];

        Tn[state[c]][d - 97][0]++;
        Tn[state[c]][d - 97][Tn[state[c]][d - 97][0]] = state[a];
    }
    fin.close();
}

void reverse_dfa()
{
    for(int i=0 ; i<=nrs ; i++)
        qn[i] = final[i];
    finaln[state[q]] = 1;
    fn = q;
}

set<int> delta(const set<int>& v , char s)
{
    set<int> w;
    set <int> :: iterator it;
    for(it=v.begin() ; it!=v.end() ; ++it)
    {
        for(int j=1 ; j<=Tn[*it][(int)s - 97][0] ; j++)
                w.insert(Tn[*it][(int)s - 97][j]);
    }
    return w;
}

void pre()
{
    set<int> init;
    for(int i=0 ; i<=nrs ; i++)
        if(qn[i] == 1)
            init.insert(i);
    S.insert(init);
    nrsf = 1;
    statef[1] = 1;
    qf = 1;
    mp.insert(pair<set<int> , int> (init,1));
}
void dfs(const set<int>& g , int nrstate)
{
    for(int i=0 ; i<nrl ; i++)
    {
        set<int> k = delta(g , letter[i]);
        if(S.find(k) == S.end())
        {
            nrsf++;
            S.insert(k);
            mp.insert(pair<set<int> , int> (k , nrsf));
            statef[nrsf] = nrsf;
            Tf[nrstate][(int)letter[i] - 97] = nrsf;
            if(k.find(state[q]) != k.end())
            {
                nrff++;
                finalf[nrsf] = 1;
            }
            dfs(k , nrsf);
        } else if(k==g) {
            Tf[nrstate][(int)letter[i] - 97] = mp[k];
        } else if(Tf[nrstate][(int)letter[i] - 97] == 0) {
            Tf[nrstate][(int)letter[i] - 97] = mp[k];
            dfs(k,mp[k]);
        }
    }
}
void cout_intermediate_dfa()
{
    ofstream fin("dfa.in");
    fin << nrsf << "\n";
    for (int i = 1; i <= nrsf; i++)
    {
        fin << statef[i] << " ";
    }
    fin << "\n" << nrl << "\n";
    for (int i = 0; i < nrl; i++)
        fin << letter[i] << " ";

    fin <<"\n" << qf << "\n";
    fin << nrff << "\n";
    for (int i = 1; i <= nrsf; i++)
    {
        if(finalf[i] == 1)
            fin << i << " ";
    }
    fin << "\n" << nrl*nrsf << "\n";
    for (int i=1 ; i<=nrsf; i++)
        for (int j = 0; j < nrl; j++)
        {
            int a = j+97;
            fin << i << " "<< (char)a << " " << Tf[i][j] <<"\n";
        }
    fin<<"\n";
    fin.close();
}
void delete_arrays()
{
    S.clear();
    mp.clear();
    for(int i=0 ; i<=nrs ; i++)
    {
        state[i] = 0;
        final[i] = 0;
        qn[i] = 0;
        finaln[i] = 0;
        statef[i] = 0;
        finalf[i] = 0;
        for (int j = 0; j < nrl; j++)
        {
            T[i][j] = 0;
            Tf[i][j] = 0;
            for(int k=1 ; k<=Tn[i][j][0] ; k++)
                Tn[i][j][k] = 0;
            Tn[i][j][0] = 0;
        }
    }
    nrff = 0;
}
int main()
{
    read();
    reverse_dfa();
    pre();
    dfs(*S.begin() , nrsf);
    cout_intermediate_dfa();

    delete_arrays();

    read();
    reverse_dfa();
    pre();
    dfs(*S.begin() , nrsf);
    cout_intermediate_dfa();
}