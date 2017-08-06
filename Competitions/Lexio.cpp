#include<bits/stdc++.h>
using namespace std;
 
 
vector<long long int> factoradics(long long int n)
{
      vector<long long int> a;
 
 
   long long int i=1;
   long long  int rem;
    while(n!=0)
    {
 
        rem=n%i;
        n=(n/i);
        a.push_back(rem);
        i++;
    }
    return a;
}
 
int main()
{
    string s;
    int t;
    cin >> s;
    cin >> t;
    while(t!=0)
    {
        string c=s;
        string rem,na;
        long long int n;
        cin>>n;
        vector<long long int> fact = factoradics(n-1);
        reverse(fact.begin(),fact.end());
 
 
        na=c.substr(0,c.size()-fact.size());
        rem= c.substr(c.size()-fact.size(),fact.size());
       cout<<na;
        for(int i=0;i<fact.size();i++)
        {
            cout<<(rem[fact[i]]);
            rem.erase(fact[i],1);
        }
 
        cout<<endl;
 
    t--;
 
    }
}
