#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<sstream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;

class process                      //to define class properties pid and b_time
{
    public:
    int pid;
    int b_time;
    process(int a,int b)
    {
        pid=a;
        b_time=b;
    }
    process()
    {
    }
};
int timer;
int iter;
int minimum_fitness;
int n;
int l[15];
int l1[15];
int p1,p2;         //identifying the two parents
int o1,o2;         //The two offsprings;
int reverse(int a)              //reverse the digits of an integer
{
int b=0;
while(a!=0)
{
int c=a%10;
b=b*10+c;
a=a/10;
}
return b;
}

float fit_func(int a,int n, process pro[])     //to evaluate the fitness of a chromosome
{
    int sum=0;
    int wait_sum=0;
    int wait[n];
    int d=reverse(a);
    while(d!=0)
    {
        int b=d%10;
        for(int i=0;i<n;i++)
        {
            if(pro[i].pid==b)
            {   
                wait[i]=sum;
                sum = sum + pro[i].b_time;
            }
            else
            {
                continue;
            }
        }
        d=d/10;
    }
    for(int i=0;i<n;i++)
        {
            wait_sum =wait_sum + wait[i];
        }
        float avg=wait_sum/n;
        return avg;
}
int fact(int a)                  //to find factorial of a number
{
    int f=1;
    if(a==1)    
    {
        return f;
    }
    else
    {
        f=a*fact(a-1);    
    }
}

void swap(char *x, char *y)              //to swap to characters
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

map<int,string> chromosomes;      //mapping vector of strings to int to represent chromosomes
map<int,int> fitness;           //to map chromosome to it's fitness
int flag=1;                       
void permute(char* a, int l, int r)         //to generate the permutations of the given processes
    {
        int i;
        if (l == r)
            {
                chromosomes[flag]=a;
                flag++;
            }
        else
        {
            for (i = l; i <= r; i++)
            {
                swap((a+l), (a+i));
                permute(a, l+1, r);
                swap((a+l), (a+i));
            }
        }
    }
int * crossover1(int k1,int k2,int n)   //crossover
{
    int b[n];
    for(int i=n-1;i>=0;i--)
    {
        l[i]=k1%10;
        k1=k1/10;
        b[i]=k2%10;
        k2=k2/10;
    }
    int d[n];
    for(int i=0;i<n;i++)
    {
        d[i]=0;
    }
    for(int i=n/3;i<(2*n)/3;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(l[i]==b[j])
            {
                d[j]=l[i];
            }
        }
    }

    for(int i=n/3;i<(2*n)/3;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(d[j]!=0)
            {   
                l[i]=d[j];
                d[j]=0;
                break;
            }
        }
    }
    return l;
}
int * crossover2(int k1,int k2,int n)   //crossover
{
    int b[n];
    for(int i=n-1;i>=0;i--)
    {
        l1[i]=k1%10;
        k1=k1/10;
        b[i]=k2%10;
        k2=k2/10;
    }
    int d[n];
    for(int i=0;i<n;i++)
    {
        d[i]=0;
    }
    for(int i=n/3;i<(2*n)/3;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(l1[i]==b[j])
            {
                d[j]=l1[i];
            }
        }
    }

    for(int i=n/3;i<(2*n)/3;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(d[j]!=0)
            {   
                l1[i]=d[j];
                d[j]=0;
                break;
            }
        }
    }
    return l1;
}
int min_fitness()
{
    int min=500;
    for (std::map<int,int>::iterator it=fitness.begin();it!=fitness.end();++it)
    {   
        int b = it -> second;
        if(b<min)
        {
            min = it->second;
        }
    }
    return min;
}
int stoi(string a)          //to convert string to integer
{
   int y=0;
   stringstream convert(a);
   convert>>y;
   return y;
}
string atoi(int a)
{
    string Result;
    stringstream convert;
    convert << a;
    Result = convert.str();
    return Result;
}
int optimal_sol()
{
int a= min_fitness();
int b;
int c;
for (std::map<int,int>::iterator it=fitness.begin();it!=fitness.end();++it)
    {   
        if(it->second == a)
        {
            b=it->first;
        }
    }
for (std::map<int,string>::iterator it=chromosomes.begin();it!=chromosomes.end();++it)
    {   
        if(it->first == b)
        {
            c=stoi(it->second);
        }
    }
    return c;    
}
 void delay(int d)
    {
        int i;
        float a;
        for (i=0;i<(d*10000);i++) a=(float)(i/0.1f);
    }
int findperm(int a)
{
    map<int,string>::iterator it=chromosomes.begin();
    while(a!=it->first)
    {
        ++it;
    }
    int b=stoi(it->second);
    return b;
}

int main()
{
    cout<<"Enter the number of processes:"<<endl;
    cin>>n;
    process pro[n];
    int b;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the burst time of process "<<i+1<<endl;
        cin>>b;
        pro[i]=process(i+1,b);
    }
    int f=fact(n);
    for(int i=0;i<f;i++)
    {
        chromosomes[i+1];
    }
    char a[n];
    for(int i=0;i<n;i++)
    {
    a[i]=49+i;
    }
    permute(a,0,n-1);          
    for(int i=0;i<f;i++)
    {
        fitness[i+1];
    }
    int glag=1;
    for (std::map<int,string>::iterator it=chromosomes.begin();it!=chromosomes.end();++it)
    {
        string a=it->second;
        int b=stoi(a);
        fitness[glag]=fit_func(b,n,pro);
        glag++;
    }
    cout<<"Loading"<<endl;
	for(int i=0; i<3; i++)
	{
	       for(int i=0; i<2; i++)
	       {
			delay(6000);
			cout<<".";
		}
	 }
	cout<<"The chromosomes are: "<<endl;
    for (std::map<int,string>::iterator it=chromosomes.begin();it!=chromosomes.end();++it)
    {
        cout<<it->first<<" : "<<it->second<<endl;
    }
    cout<<"The fitnesses are: "<<endl;
    for (std::map<int,int>::iterator it=fitness.begin();it!=fitness.end();++it)
    {
        cout<<it->first<<" : "<<it->second<<endl;
    }
    timer=0;
    iter=1;
    while(timer<=3)
    {
        cout<<"This is iteration number: "<<iter<<endl<<endl;
        iter++;
        minimum_fitness=min_fitness();
        int t=0;
        for (std::map<int,int>::iterator it=fitness.begin(); it!=fitness.end(); ++it)
        {
            t+= it->second;
        }
        srand(time(NULL));
        int r= 1 + rand()%t;
        cout<<"The sum of the expected values are "<<t<<endl;
        cout<<"The random variable generated between "<<0<<" and "<<t<<" is "<<r<<endl;
        int sum=0;
        map<int,int>::iterator it=fitness.begin();
        map<int,string>::iterator ct=chromosomes.begin();
        while(sum<=r)
        {
            sum=sum + it->second;
            ++it;
            ++ct;
        }
        p1=findperm(it->first);
        cout<<"Parent 1 is chromosome number "<<it->first<<endl;
        cout<<"Parent 1 solution set is "<<p1<<endl<<endl;
        cout<<"The sum of the expected values are "<<t<<endl;
        int r2= 1 + rand()%t;
        cout<<"The random variable generated between "<<0<<" and "<<t<<" is "<<r2<<endl;
        int sum1=0;
        map<int,int>::iterator it1=fitness.begin();
        map<int,string>::iterator ct1=chromosomes.begin();
        while(sum1<=r2)
        {
            sum1=sum1 + it1->second;
            ++it1;
            ++ct1;
        }
        p2=findperm(it1->first);
        cout<<"Parent 2 is chromosome number "<<it1->first<<endl;
        cout<<"Parent 2 solution set is "<<p2<<endl;
        int *p; 
        p = crossover1(p1,p2,n);
        int *q;
        q = crossover2(p2,p1,n);
        int h=1;
        for(int i=n-1;i>=0;i--)
        {
            o1=o1 + h*(*(p+i));
            o2=o2 + h*(*(q+i));
            h*=10;
        }
        cout<<"Offspring 1 is : "<<o1<<endl;
        cout<<"Offspring 2 is : "<<o2<<endl<<endl;
        int min1,min2,s1,s2;
        int p1_fit = fit_func(p1,n,pro);
        int p2_fit = fit_func(p2,n,pro);
        int o1_fit = fit_func(o1,n,pro);
        int o2_fit = fit_func(o2,n,pro);
        min1 = min(p1_fit,max(p2_fit,max(o1_fit,o2_fit)));
        if(min1==p1_fit)
        {
            s1=1;
        }
        else if(min1==p2_fit)
        {
            s1=2;
        }
        else if(min1==o1_fit)
        {
            s1=3;
        }
        else
        {
            s1=4;
        }
        if(s1==1)
        {
            min2 = min(p2_fit,min(o1_fit,o2_fit));
            if(min2=p2_fit)
            {
               s2=2;
            }
            else if(min1==o1_fit)
            {
                s2=3;
             }
            else
            {
                s2=4;
            }
        }
        if(s1==2)
        {
            min2 = min(p1_fit,max(o1_fit,o2_fit));
            if(min2=p1_fit)
            {
               s2=1;
            }
            else if(min1==o1_fit)
            {
                s2=3;
             }
            else
            {
                s2=4;
            }
        }
        if(s1==3)
        {
            min2 = min(p1_fit,min(p2_fit,o2_fit));
            if(min2=p1_fit)
            {
               s2=1;
            }
            else if(min1==p2_fit)
            {
                s2=2;
             }
            else
            {
                s2=4;
            }
        }
        if(s1==4)
        {
            min2 = min(p1_fit,min(p2_fit,o1_fit));
            if(min2=p1_fit)
            {
               s2=1;
            }
            else if(min1==p2_fit)
            {
                s2=2;
             }
            else
            {
                s2=3;
            }
        }
        if(s1==3)
        {
            if(p1_fit<p2_fit)
            {
                it1->second = o1_fit;
                ct1->second = atoi(o1);
            }
            else
            {
                it->second = o1_fit;
                ct->second = atoi(o1);
            }
            if(s2==4)
            {
                if(p1_fit<p2_fit)
                {
                    it1->second = o2_fit;
                    ct1->second = atoi(o2);
                }
                else
                {
                    it->second = o2_fit;
                    ct->second = atoi(o2);
                }
            }
        }
        if(s1==4)
        {
            if(p1_fit<p2_fit)
            {
                it1->second = o2_fit;
                ct1->second = atoi(o2);
            }
            else
            {
                it->second = o2_fit;
                ct->second = atoi(o2);
            }
            if(s2==3)
            {
                if(p1_fit<p2_fit)
                {
                    it1->second = o1_fit;
                    ct1->second = atoi(o1);
                }
                else
                {
                    it->second = o1_fit;
                    ct->second = atoi(o1);
                }
            }
        }
        if(s1==1)
        {
            if(s2==3)
            {
                it1->second =o1_fit;
                ct1->second = atoi(o1);
            }
            else if(s2==4)
            {
                it1->second =o2_fit;
                ct1->second = atoi(o2);
            }
        }
        if(s1==2)
        {
            if(s2==3)
            {
                it->second =o1_fit;
            }
            else if(s2==4)
            {
                it->second =o2_fit;
            }
        }
        if(min_fitness()==minimum_fitness)
        {
            timer++;
        }
        else
        {
            timer =0;
        }
        cout<<"The value of the timer is "<<timer<<endl;
    }
    cout<<"The optimal soultion hence with maximum fitness is "<<optimal_sol()<<endl;
    cout<<"The average waiting time of the optimal solution is "<<fit_func(optimal_sol(),n,pro);
}

