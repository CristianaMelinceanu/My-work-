#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
int col(char alfa[10],int c,char x)
{
    for(int i=0;i<strlen(alfa);i++)
        if(x==alfa[i])
            return i+1;
    return -1;
}

int main()
{
    ifstream f("l.in");
    int q[10],i,m[10][10]={-1},n,c,j,tr,x,y,ini,fin[10];
    char alfa[10],z,sir[30];
    f>>n;
    for(i=1;i<=n;i++)
        f>>q[i];
    f>>c;
    for(i=0;i<c;i++)
        f>>alfa[i];
    f>>tr;
    for(i=1;i<=tr;i++)
    {
        f>>x>>y>>z;
        j=col(alfa,c,z);
        if(j!=-1)
            m[x][j]=y;
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=c;j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
    }
    f>>ini;
    int nrfin;
    f>>nrfin;
    for(i=1;i<=nrfin;i++)
        f>>fin[i];
    cin>>sir;
    int lsir=0;
    i=0;
    if(strchr(sir,'*')!=NULL)
    {
        int j;
        for( j=1;j<=nrfin;j++)
            if(ini==fin[j])
            {
                     cout<<"Cuvantul vid e acceptat de limbaj"<<endl;
                     j=nrfin+5;
            }
        if(j==nrfin+1)
            cout<<"Nu se poate!"<<endl;
        return 0;
    }

    while(i<strlen(sir))
    {
        j=col(alfa,c,sir[i]);
        if(j==-1)
        {
            cout<<sir[i]<<"  nu face parte din alfabet"<<endl;
            i=strlen(sir)+2;
        }
        else
        {
            if(m[ini][j]!=-1)
                ini=m[ini][j];
            else
            {
                cout<<"Nu exista tranzitie!"<<endl;
                i=strlen(sir)+2;
            }

        }
        i++;

    }
    if(i==strlen(sir))
    {
        for(int k=1;k<=nrfin;k++)
            if(ini==fin[k])
            {
                cout<<"Cuvantul apartine limbajului"<<endl;
                return 0;
            }

        cout<<"Cuvantul nu apartine limbajului(nu a ajuns in starea finala)";
    }




    return 0;
}
