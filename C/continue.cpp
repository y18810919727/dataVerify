/* ***********************************************
Author        :yuanzhaolin
Created Time  :2017年07月09日 星期日 09时09分07秒
File Name     :continue.cpp
************************************************ */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <utility>
#include <sstream>
#include <fstream>
using namespace std;
#define repp(i,a,b) for(int i=a;i<=b;i++)
#define rep(i,a) for(int i=0;i<a;i++)
#define REP(i,a) for(int i=1;i<=a;i++)
#define per(i,a,b) for(int i=a-1;i>=b;i--)
#define foreach(i,a) for(int i=head[a];i>=0;i=ee[i].next)
#define Foreach(i,a) for(__typeof((a).begin())i=(a).begin();i!=(a).end();i++)
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define mp make_pair
#define m0(x) memset(x,0,sizeof(x))
#define mff(x) memset(x,0xff,sizeof(x))
#define fi first
#define se second
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define SZ(x) ((int)(x).size())
#define sqr(x) ((x)*(x))
#define C1(x) cout<<x<<endl
#define C2(x,y) cout<<x<<" "<<y<<endl
#define C3(x,y,z) cout<<x<<" "<<y<<" "<<z<<endl
typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector< pair<int,int> > VPII;
const ll mod=(ll)1e9+7;
const ll maxn=(ll)1e5+7;
const ll maxe=(ll)1e6+7;
const ll INF=(ll)1e17+7;
const double PI=acos(-1);
int dx[4]={0,0,1,-1};
int dy[4]={-1,1,0,0};
char str[1000];
//切割;
void split(string s,char t,vector<string> &res) {  for(int i=0;i<s.length();i++) if(s[i]==t) { res.push_back(s.substr(0,i)); split(s.substr(i+1),t,res); return ; } if(s.length()!=0) res.push_back(s);
}
//字符串转long long 
ll str2ll(string s)
{
	istringstream istr;
	istr.str(s.c_str());
	ll a;
	istr>>a;
	return a;
}
//代表transaction的数据结构
struct T{
	string code,date,fun,flag;
	ll id,time,aid,bid,price,volume;
	T(){}
	//初始化方法
	T(string s)
	{
		vector<string> sl;
		split(s,';',sl);
		code=sl[0];date=sl[2];time=str2ll(sl[3]);id=str2ll(sl[4]);fun=sl[5];flag=sl[7];price=str2ll(sl[8]);volume=str2ll(sl[9]);aid=str2ll(sl[10]);bid=str2ll(sl[11]);
		
	}
	void prt()
	{
		cout<<id<<" "<<date<<" "<<time<<" "<<price<<" "<<volume<<" "<<fun<<" "<<flag<<" "<<aid<<" "<<bid<<endl;
	}
};
//代表order的数据结构
struct O
{
	string code,date,side,kind;
	ll id,price,volume,time;
	O(){}
	//初始化方法
	O(string s)
	{
		vector<string> sl;
		split(s,';',sl);
		code=sl[0];date=sl[2];time=str2ll(sl[3]);side=sl[5];kind=sl[6];id=str2ll(sl[7]);price=str2ll(sl[8]);volume=str2ll(sl[9]);
		if(kind=="1")
		{
			if(side=="S")
				price=INF;
			else
				price=-INF;
		}
	}
	bool isShi()
	{
		if(kind=="1") return true;
		else return false;
	}
	void prt()
	{
		if(id==-1)
			cout<<"Don't exist"<<endl;
		else
		{
			printf("id\tprice\tvolume\ttime\t\tkind\tside\n");
			printf("%lld\t%lld\t%lld\t%lld\t%s\t%s\n",id,price,volume,time,kind.c_str(),side.c_str());
		}
	}
	bool operator < (const O &a) const
	{
		if(price!=a.price) 
		{
			if(side=="S")
			return price<a.price;
			else
				return price>a.price;
		}
		else if(a.id!=id)
		return id<a.id;
		else
			return time<a.time;

	}
};
/*
代表业务的数据结构
type:0 代表transaction，1代表order
id: 该业务在原列表的id
time: hhmmssxxx
*/
map<ll,ll> Left;
struct ST
{
	int id;
	long time;
	int type;
	ST(){}
	ST(int id,long time,int ty):id(id),time(time),type(ty)
	{
	}
	bool operator < (const ST & a) const
	{
		if(time!=a.time)
			return time<a.time;
		else if(type!=a.type)
			return type<a.type;
		else
			return id<a.id;
	}
	void prt()
	{
		cout<<type<<" "<<time<<" "<<id<<endl;
	}
};
vector<O> os;//总的order
vector<ST> ss; //总的ST
vector<T> ts;//总的transaction
bool cmpO(O o1,O o2)
{
	if(o1.id!=o2.id)
	return o1.id<o2.id;
	else
		return o1.time<o2.time;
}
bool cmpT(T t1,T t2)
{
	if(t1.id!=t2.id)
	return t1.id<t2.id;
	else
		return t1.time<t2.time;
}
O findObyID(ll id)
{
	O o ;
	o.id=id;
	o.time=0;
	return *lower_bound(os.begin(),os.end(),o,cmpO);
}
T findTbyID(ll id)
{
	T t ;
	t.id=id;
	return *lower_bound(ts.begin(),ts.end(),t,cmpT);
}
void vecprt(vector<ll> v)
{
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<endl;
}
map<ll,ll> getleft()
{
	map<ll,ll> m;
	for(int i=0;i<os.size();i++)
		m[os[i].id]=os[i].volume;
	for(int i=0;i<ts.size();i++)
	{
		int aid=ts[i].aid;
		int bid=ts[i].bid;
		if(ts[i].fun=="C")
		{
			if(aid!=0) m[aid]-=ts[i].volume;
			else m[bid]-=ts[i].volume;
		}
		else
		{
			m[aid]-=ts[i].volume;
			m[bid]-=ts[i].volume;
		}
	}
	/*
	for(int i=0;i<os.size();i++)
	{
		if(m[os[i].id]!=0)
			cout<<os[i].id<<" "<<m[os[i].id]<<endl;
	}
	*/
	return m;
}
struct Q
{
	set<O> que;
	string side;
	long long fetfp()
	{
		return (que.begin())->price;
	}
	O getO(ll id)
	{
		O o= findObyID(id);
		o.time=0;
		set<O>::iterator it=que.upper_bound(o);
		if(it==que.end()||it->id!=id)
			o.id=-1;
		else
			o=*it;
		return o;
	}
	void insert(O o)
	{
		que.insert(o);	
	}
	bool erase(ll index,long long volume)
	{
		O o= findObyID(index);
		o.time=0;
		set<O>::iterator it=que.upper_bound(o);
		if(it==que.end())
		{
			cout<<"can't find this order"<<endl;
			while(1);
		}
		if(it->id==o.id)
		{
			o=*(it);
			que.erase(it);
			o.volume-=volume;
			if(o.volume>0)
				que.insert(o);
			else if(o.volume<0)
			{
				cout<<"volume is negative"<<endl;
				cout<<o.id<<endl;
				while(1);
			}
		}
		else
		{
			cout<<"can't find this order"<<endl;
			while(1);
		}
	}
	vector<ll> getbestIDs()
	{
		ll p = que.begin()->price;
		set<O>::iterator it =que.begin();
		vector<ll> res;
		while(it!=que.end()&&it->price==p)
		{
			res.push_back(it->id);
			it++;
		}
		return res;
	}
	vector<ll> getorderqueue()
	{
		ll p = que.begin()->price;
		set<O>::iterator it =que.begin();
		vector<ll> res;
		while(it!=que.end()&&it->price==p)
		{
			res.push_back(it->volume);
			it++;
		}
		return res;
	}
	vector<ll> fiveprice()
	{
		vector<ll> res;
		ll price=que.begin()->price;
		O o;
		o.side=side;
		o.time=o.id=INF;
		for(int i=0;i<5;i++)
		{
			res.push_back(price);
			o.price=price;
			set<O>::iterator it=que.upper_bound(o);
			if(it==que.end()) break;
			price=it->price;
		}
		while(res.size()<5) res.push_back(-1);
		return res;
	}
	vector<ll> fivevolume()
	{
		vector<ll> prices=fiveprice();
		for(int i=0;i<prices.size();i++)
			prices[i]=getvolumebyp(prices[i]);
		return prices;
	}
	int pos(ll p)
	{
		ll price=que.begin()->price;
		O o;
		o.side=side;
		for(int i=1;i<=10;i++)
		{
			if(price==p) return i;
			o.price=price;
			o.time=o.id=INF;
			set<O>::iterator it=que.upper_bound(o);
			if(it==que.end()) return -1;
			price=it->price;
		}
		return 100;
	}
	ll getvolumebyp(ll p)
	{
		O o;
		o.side=side;
		o.price=p;
		o.time=o.id=0;
		ll sum=0;
		set<O>::iterator it=que.upper_bound(o);
		while(it!=que.end()&&it->price==p)
		{
			sum+=it->volume;
			it++;
		}
		return sum;
	}
	bool isinque(ll index)
	{
		O o= findObyID(index);
		o.time=0;
		set<O>::iterator it=que.upper_bound(o);
		if(it==que.end()||((*it).id)!=o.id)
		{
			return false;
		}
		else return true;
	}
	O findinque(ll index)
	{
		O o= findObyID(index);
		o.time=0;
		set<O>::iterator it=que.upper_bound(o);
		return *it;
	}
};
Q buy,sell;
vector<string> readFile(string path)
{
	vector<string> res;
	ifstream infile(path.c_str());
	string tmp;
	while(getline(infile,tmp))
	{
		res.push_back(tmp);
	}
	return res;
}
void init()
{
	const string tpath="../DataReader/300273SZ_20170601_transac.txt";
	const string opath="../DataReader/300273SZ_20170601_order.txt";
	/*
	const string tpath="transaction";
	const string opath="order";
	*/
	vector<string> slist=readFile(tpath);
	//vector<string> slist=readFile("continue.in");
	for(int i=0;i<slist.size();i++)
	{
		ts.push_back(T(slist[i]));
	}
	slist=readFile(opath);
	for(int i=0;i<slist.size();i++)
	{
		os.push_back(O(slist[i]));
	}
	buy.side="B";
	sell.side="S";
	Left=getleft();
}
void log(T t,O so,O bo)
{
	if(t.time==92500000||t.time==150000000) return ;
	char s=so.kind[0];
	int bpos=buy.pos(bo.price);
	int spos=sell.pos(so.price);
	//if(bpos1||spos==1) return ;
	//if(bpos!=1&&spos==1) return ;
	//if(s!='0'||s=='1') return;
	//if(pr==t.price) return ;
	if(so.kind=="0"&&bo.kind=="0") return ;
	ll pr=(so.kind=="0")?so.price:bo.price;
	string fl=(so.time>bo.time)?"B":"S";
	if(fl!=t.flag) return ;
	//if(pr==t.price) return ;
	cout<<"It's a trade."<<endl;
	printf("sid\tbid\tsprice\tbprice\ttprice\tspos\tbpos\tflag\n");
	printf("%lld\t%lld\t%lld\t%lld\t%lld\t%d\t%d\t%s\n",t.aid,t.bid,so.price,bo.price,t.price,spos,bpos,t.flag.c_str());
	cout<<"sell_order"<<endl;
	so.prt();
	cout<<"buy_order"<<endl;
	bo.prt();
	cout<<endl;
	/*
	printf("the top five prices\n");
	cout<<"buy"<<endl;
	vecprt(buy.fivevolume());
	cout<<"sell"<<endl;
	vecprt(sell.fivevolume());
	*/
}
void getTimeQue()
{
	for(int i=0;i<ts.size();i++)
	{
		ss.push_back(ST(i,ts[i].time,0));
	}
	for(int i=0;i<os.size();i++)
	{
		ss.push_back(ST(i,os[i].time,1));
	}
	sort(ss.begin(),ss.end());
}
void solveT(T t,bool isLog=false)
{
		if(t.fun=="C")	
		{
	//		cout<<"It's a cancel"<<endl;
			ll theID = t.aid?t.aid:t.bid;
			O o = findObyID(theID);
	//		printf("orderID\tprice\tvolume\ttime\tside\n");
	//		o.prt();
			if(t.aid!=0)
			{
				sell.erase(t.aid,t.volume);
	//			sell.getO(t.aid).prt();
			}
			else
			{
				buy.erase(t.bid,t.volume);
	//			buy.getO(t.bid).prt();
			}
		}
		else
		{
			O bo = findObyID(t.bid);
			O so = findObyID(t.aid);
			if(isLog)
			log(t,so,bo);
			sell.erase(t.aid,t.volume);
			buy.erase(t.bid,t.volume);
		}
}
void solveO(O o)
{
	if(o.side=="B")
		buy.insert(o);
	else
		sell.insert(o);
}
void solveS(ST s)
{
	if(s.type==0)
	{
		T t=ts[s.id];
		solveT(t);
	}
	else
	{
		O o=os[s.id];
		solveO(o);
	}
}
void run()
{
	map<ll,ll> m;
	for(int i=0;i<os.size();i++)
		m[os[i].id]=os[i].volume;
	for(int i=0;i<ts.size();i++)
	{
		int aid=ts[i].aid;
		int bid=ts[i].bid;
		if(ts[i].fun=="C")
		{
			if(aid!=0) m[aid]-=ts[i].volume;
			else m[bid]-=ts[i].volume;
		}
		else
		{
			m[aid]-=ts[i].volume;
			m[bid]-=ts[i].volume;
		}
	}
	int cnt1=0;
	int cnt2=0;
	int cnt3=0;
	int cnt4=0;
	int cnt=0;
	for(int i=0;i<os.size();i++)
	{
		if(m[os[i].id]!=0)
		{
			os[i].prt();
			//os[i].volume=m[os[i].id];
			if(os[i].volume!=m[os[i].id]&&os[i].side=="S") cnt++;
			if(os[i].kind=="0"&&os[i].side=="S")
			cnt1++;
			if(os[i].kind=="U"&&os[i].side=="S")
			cnt2++;
			if(os[i].kind=="0"&&os[i].side=="B")
			cnt3++;
			if(os[i].kind=="U"&&os[i].side=="B")
			cnt4++;
		}
	}
	cout<<cnt<<endl;
	cout<<cnt1<<" "<<cnt2<<" "<<cnt3<<" "<<cnt4<<endl;
}
void fivepriceprint()
{
	cout<<"five buy price"<<endl;
	vecprt(buy.fiveprice());	
	cout<<"five buy volume"<<endl;
	vecprt(buy.fivevolume());	
	cout<<"five sell price"<<endl;
	vecprt(sell.fiveprice());	
	cout<<"five sell volume"<<endl;
	vecprt(sell.fivevolume());	
	cout<<endl;

}
void fivesellpriceprint()
{
	cout<<"five sell price"<<endl;
	vecprt(sell.fiveprice());	
	cout<<"five sell volume"<<endl;
	vecprt(sell.fivevolume());	
	cout<<"order queue volume"<<endl;
	vecprt(sell.getorderqueue());
	cout<<"order queue id"<<endl;
	vecprt(sell.getbestIDs());
	cout<<endl;

}
void fivebuypriceprint()
{
	cout<<"five buy price"<<endl;
	vecprt(buy.fiveprice());	
	cout<<"five buy volume"<<endl;
	vecprt(buy.fivevolume());	
	cout<<"order queue volume"<<endl;
	vecprt(buy.getorderqueue());
	cout<<"order queue id"<<endl;
	vecprt(buy.getbestIDs());
	cout<<endl;
}
void shijiasolve()
{
	int cnt1=0;
	int cnt2=0;
	for(int i=0;i<ss.size();i++)	
	{
		if(ss[i].type==1) solveS(ss[i]);
		else 
		{ 
			T t=ts[ss[i].id];
			if(t.fun=="C") 
			{ 
				solveT(t);
				continue; 
			} 
			ll id=0; 
			O a=sell.findinque(t.aid);
			O b=buy.findinque(t.bid);
			bool flag = false;
			if(a.isShi()&&(buy.pos(b.price)!=1||flag))
			{
				cout<<"----------------------------"<<endl;
				cout<<"本记录为卖方为市价方"<<endl;
				cnt1++;
				cout<<"time = "<<t.time<<" "<<"transaction id = "<<t.id<<endl;
				cout<<"trade volume = "<<t.volume<<" trade price = "<<t.price<<endl;
				cout<<"aid = "<<a.id<<" bid = "<<b.id<<"\n";
				cout<<"市价方剩余volume"<<" "<<a.volume<<endl;
				cout<<"对方为买 "<<buy.pos(b.price)<<" 价"<<endl;
				fivebuypriceprint();
			}
			else if(b.isShi()&&(sell.pos(a.price)!=1||flag))
			{
				cout<<"----------------------------"<<endl;
				cout<<"本记录为买方为市价方"<<endl;
				cnt2++;
				cout<<"time = "<<t.time<<" "<<"transaction id = "<<t.id<<endl;
				cout<<"trade volume = "<<t.volume<<" trade price = "<<t.price<<endl;
				cout<<"bid = "<<b.id<<" aid = "<<a.id<<"\n";
				cout<<"市价方剩余volume"<<" "<<b.volume<<endl;
				cout<<"对方为卖 "<<sell.pos(a.price)<<" 价"<<endl;
				fivesellpriceprint();
				vector<ll> v=sell.getbestIDs();
				for(int j=0;j<v.size();j++)
				{
					cout<<v[j]<<" ";
					cout<<Left[(int)v[j]]<<" "<<endl;
				}
			}	
			solveT(t);
			/*
			if(sell.isinque(t.aid))
			sell.findinque(t.aid).prt();
			else
				cout<<"have erase"<<endl;
			if(buy.isinque(t.bid))
			buy.findinque(t.bid).prt();
			else
				cout<<"have erase"<<endl;
				*/
		}
	}
	cout<<"S B"<<endl;
	cout<<cnt1<<" "<<cnt2<<endl;
}
void shijia2()
{
	int allshi=0;
	for(int i=0;i<os.size();i++)
	{
		if(!os[i].isShi()) continue;
		allshi++;
		O o = os[i];
		int cnt=0;
		int cnt1=0;
		int cnt2=0;
		map<ll,int> m;
		vector<pair<ll,ll> > vp; 
		for(int j=0;j<ts.size();j++)
		{
			T t= ts[j];
			if(ts[j].aid!=o.id&&ts[j].bid!=o.id) continue;
			m[ts[j].price]+=1;
			ll id=(o.side=="S")?t.bid:t.aid;
			O other=findObyID(id);
			if(other.price!=t.price) 
			{
				cnt2++;
				vp.push_back(make_pair(other.id,other.price));
			}
			cnt1++;
		}
		map<ll,int>::iterator it = m.begin();
		if(cnt2==0) continue;
		cout<<"---------------"<<endl;
		cout<<"id flag time"<<endl;
		cout<<o.id<<" "<<o.side<<" "<<o.time<<endl;
		cout<<"价格  交易次数"<<endl;
		while(it!=m.end())
		{
			cout<<(it->fi)<<" "<<(it->se)<<endl;
			it++;
			cnt++;
		}
		cout<<"与限价委托价格不同的笔数 = "<<cnt2<<" 总交易笔数 = "<<cnt1<<" 交易价格种类数 = "<<cnt<<endl;
		cout<<"与委托价不同的限价id 和它的价格、时间"<<endl;
		for(int i=0;i<vp.size();i++)
		{
			cout<<vp[i].fi<<" "<<vp[i].se<<" "<<findObyID(vp[i].fi).time<<endl;
		}
		
	}
	cout<<"all shi"<<allshi<<endl;
}
void getinfor(ll time)
{
	for(int i=0;i<ss.size();i++)
	{
		solveS(ss[i]);
		if(ss[i].time>=time) break;
		fivesellpriceprint();
		fivebuypriceprint();
	}
}
void getshijia3()
{
	getinfor(1);
}
int main()
{
    //freopen("in.txt","r",stdin);
    freopen("shijia.txt","w",stdout);
    init();
    getTimeQue();
    cout<<os.size()<<endl;
    cout<<ts.size()<<endl;
   // solve();
//	run();
//	shijiasolve();
	shijia2();
	//shijia3();
	cout<<buy.que.size()<<" "<<sell.que.size()<<endl;
    return 0;
}
