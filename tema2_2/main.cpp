#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;
vector<int> m[100][100];
vector <int> nfa[100][100];
vector <int> dfa[100][100];

int col(char alfa[10],char x)
{
    for(int i=0;i<strlen(alfa);i++)
        if(x==alfa[i])
            return i+1;
    return -1;
}

void afisare(int n, int r,vector <int> h[100][100])
{
    for(int i=0;i<n;i++)
       {    cout<<i<<" ";
            for(int j=0;j<=r;j++)
            {
                cout<<"[ ";
                for(int k=0;k<h[i][j].size();k++)
                    cout<<h[i][j][k]<<" ";
                cout<<"] ";
            }
            cout<<endl<<endl;
       }
       cout<<"Da";
}
bool cautaelem(int x, vector <int> v)
{
    for(int i=0;i<v.size();i++)
        if(v.at(i)==x)
            return true;
    return false;
}

void reuniune(vector<int> a,vector<int> &b)
{
    int f;
    for(int i=0;i<a.size();i++)
    {
        f=0;
        for(int j=0;j<b.size();j++)
        {
            if(a[i]!=b[j])
                f++;
        }
        if(f==b.size())
            b.push_back(a[i]);
    }
    std::sort(b.begin(),b.end());

}
bool vectoriegali(vector <int> a,vector<int> b)
{
    std::sort(a.begin(),a.end());
    std::sort(b.begin(),b.end());
    if(a.size()==b.size())
    {
        for(int i=0;i<a.size();i++)
            if(a[i]!=b[i])
                return false;
        return true;
    }
    return false;
}
void DFS (vector<int> &s,int n,int c)
{
   for(int i=1;i<=c;i++)
   {
       if(!m[s.back()][i].empty() && i!=c)
       {
           reuniune(m[s.back()][i],nfa[s.back()][i]);
           for(int j=s.size()-2;j>=0;j--)
                reuniune(m[s.back()][i],m[s[j]][i]);
       }
       else{
            if(i==c)
            {
                for(int j=0;j<m[s.back()][c].size();j++)
                {
                    s.push_back(m[s.back()][i][j]);
                    DFS(s,n,c);
                    s.pop_back();
                }

            }
       }

   }
}
void transNFA(int q[20],int c,int n)
{
    vector <int> s;
    for(int i=0;i<n;i++)
    {
        s.push_back(i);
        DFS(s,n,c);
        if(!s.empty()) s.pop_back();
    }

}
void DFA(int &c,int &n)
{
    int s=1;
    dfa[0][0].push_back(0);
    for(int i=1;i<=c-1;i++)
       {
        for(int j=0;j<nfa[0][i].size();j++)
            dfa[0][i].push_back(nfa[0][i][j]);
        s++; //0,  3,8  5
        reuniune(dfa[0][i],dfa[i][0]);



       }
    int cont=0;
     for(int i=1;i<=s;i++)
        for(int j=1;j<=c-1;j++)
          {

            for(int k=0;k<dfa[i][0].size();k++)
                reuniune(nfa[dfa[i][0][k]][j],dfa[i][j]);
            cont=0;
            for(int p=0;p<s;p++)
                if(!vectoriegali(dfa[p][0],dfa[i][j]))
                    cont++;
            if(cont==s)
            {
                reuniune(dfa[i][j],dfa[s][0]);
                s++;

            }
          }
        c--;
        n=s-1;
        }

void ordonare(int n,int r)
{
     for(int i=0;i<n;i++)
        for(int j=0;j<=r;j++)
             std::sort(m[i][j].begin(),m[i][j].end());

}
int main()
{
    ifstream f("lnfa.txt");
    int q[10],tr,x,y,ini,fin[10],n,i,c,j,nrfin;
    char alfa[10],z,sir[30];
    f>>n;    //numarul starilor
    for(i=1;i<=n;i++)
           f>>q[i];  //starile
    f>>c; //nr de caractere
    for(i=0;i<c;i++)
        f>>alfa[i]; //caracterele
    f>>tr; //nr de tranzitii
    for(int i=1;i<=tr;i++)
    {
        f>>x>>y>>z;
        j=col(alfa,z);
        m[x][j].push_back(y);
    }
    f>>ini;
    f>>nrfin;
    for(int i=1;i<=n;i++)
        f>>fin[i];
    for(int i=0;i<=n;i++)
        m[i][0].push_back(i);
    for(int i=0;i<=n;i++)
        nfa[i][0].push_back(i);

    //adancime
    ordonare(n,c);
   // cout<<"stare  a   b   lambda"<<endl;
    afisare(n,c,m);
    cout<<endl<<endl<<endl;
    for(int i=0;i<n;i++)
        transNFA(q,c,n);
   // cout<<"stare  a   b   lambda"<<endl;
    afisare(n,c,nfa);
    DFA(c,n);

    cout<<endl<<endl<<endl<<endl;

    afisare(n,c,dfa);
   /* for(int i=1;i<=c;i++)
        for(int j=0;j<dfa[1][i].size();j++)
            cout<<dfa[1][i][j]<<" ";
*/

    cout<<"Starile DFA: "<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<dfa[i][0].size();j++)
            cout<<dfa[i][0][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
    cout<<"Stari finale"<<endl;
    /*for(int k=1;k<=nrfin;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<c;j++)
               if(cautaelem(fin[k],dfa[i][j]))
               {
                    for(int p=0;p<dfa[i][j].size();p++)
                        cout<<dfa[i][j][p]<<" ";
                    cout<<endl;
               }*/
    vector<int> sf[30];
    int l=0,ve=0;
    for(int k=1;k<=nrfin;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<c;j++)
               if(cautaelem(fin[k],dfa[i][j]))
               {
                   for(int h=0;h<l;h++)
                        if(vectoriegali(sf[h],dfa[i][j])) ve++;
                    if(ve==0){
                       for(int p=0;p<dfa[i][j].size();p++)
                                sf[l].push_back(dfa[i][j][p]);
                       l++;}
               }
    for(int i=0;i<l;i++)
    {
        for(int p=0;p<sf[i].size();p++)
            cout<<sf[i][p]<<" ";
        cout<<endl;
    }





    cout << "Hello world!" << endl;
    return 0;
}
