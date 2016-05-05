//以下程式均由成大資工108級甲班張頌宇F74046462製作
//physics.h包含質點(particle)及系統(system)的類別(class) 
//目的是簡單的給出由多質點組成的系統及運動方程式(微分形式)，
//就可以得到古典物理運動中時間、位置等詳細資訊

#ifndef physics_h
#define physics_h

#include <io.h>
#include <cstdlib>
#include "ODE.h"
#include "matlab.h"
using namespace std;

template<class T>
struct Record
{
	public:
		string name;
		string (*value)(T&,void**);
		
		Record(string _name,string (*_value)(T&,void**)):name(_name),value(_value){}
};
struct Plotinfo
{
	public:
		string x;
		string y;
		string z;
		string p;
		string l;
		
		Plotinfo(string _x,string _y,string _z,string _p,string _l):x(_x),y(_y),z(_z),p(_p),l(_l){}
		Plotinfo(string _x,string _y,string _p,string _l):x(_x),y(_y),z(""),p(_p),l(_l){}
};

typedef Vector_Space (*Equation)(double&,Vector_Space&,void**);

const double PI=3.14159265359;
const double G=6.11e-17;
const double K=1e9;
const double ep0=1/(4*PI*K);
const double mu0=4*PI*1e-7;
double rad(double deg){return deg*PI/180;}

Vector Zero(Vector r){return Vector(0);}
Vector_Space Zero(double& t,Vector_Space& V,void**){return V;}

class Particle
{
	typedef Record<Particle> Rec;
	public:
		Vector_Space Y;
		double t;
		double m;
		double q;
		string name;
		vector<Plotinfo> plotinfo;
		vector<Rec> record;
		Equation eq;
		
		Particle(Equation f,string pname):Y(2),t(0),m(1),q(0),name(pname),eq(f){}
		Particle(Equation f,Vector_Space Yi,double ti,double mi,double qi,string pname,vector<Rec> _record,vector<Plotinfo> _plotinfo):Y(Yi),t(ti),m(mi),q(qi),name(pname),record(_record),plotinfo(_plotinfo),eq(f){}
		Particle(Equation f,double mi,string pname):Y(2),t(0),m(mi),q(0),name(pname),eq(f){}
		Particle(Equation f,double mi,double qi,string pname):Y(2),t(0),m(mi),q(qi),name(pname),eq(f){}
		Particle(Equation f,double ti,double mi,double qi,string pname):Y(2),t(ti),m(mi),q(qi),name(pname),eq(f){}
		Particle(Equation f):Y(2),t(0),m(1),q(0),name("particle"),eq(f){}
		
		Vector r(){return Y[0];}
		Vector v(){return Y[1];}
		Vector a(void** parameter=0){return eq(t,Y,parameter)[1];}
		double x(){return Y[0][0];}
		double y(){return Y[0][1];}
		double z(){return Y[0][2];}
		double vx(){return Y[1][0];}
		double vy(){return Y[1][1];}
		double vz(){return Y[1][2];}
		double ax(void** parameter=0){return eq(t,Y,parameter)[1][0];}
		double ay(void** parameter=0){return eq(t,Y,parameter)[1][1];}
		double az(void** parameter=0){return eq(t,Y,parameter)[1][2];}
		
		void r(double x,double y,double z){Y[0][0]=x;Y[0][1]=y;Y[0][2]=z;}
		void r(double x,double y){Y[0][0]=x;Y[0][1]=y;Y[0][2]=0;}
		void v(double vx,double vy,double vz){Y[1][0]=vx;Y[1][1]=vy;Y[1][2]=vz;}
		void v(double vx,double vy){Y[1][0]=vx;Y[1][1]=vy;Y[1][2]=0;}
		void x(double x){Y[0][0]=x;}
		void y(double y){Y[0][1]=y;}
		void z(double z){Y[0][2]=z;}
		void vx(double vx){Y[1][0]=vx;}
		void vy(double vy){Y[1][1]=vy;}
		void vz(double vz){Y[1][2]=vz;}
		
		void setRecord(int N,Rec* _record){record.clear();for(int i=0;i<N;i++) record.push_back(_record[i]);}
		void setPlot(int N,Plotinfo* _plotinfo){plotinfo.clear();for(int i=0;i<N;i++) plotinfo.push_back(_plotinfo[i]);}
		
		fstream** fout(string sname="default",bool first=0);//開啟檔案
		void stepmotion(fstream** fout,double h,bool first=0,void** parameter=0);
		void foutclose(fstream** fout);//關閉檔案
		void wait(double ti,double h,void** parameter=0){while(t<ti)ODE(eq,Y,t,h,parameter);}
		bool collide(Particle& b,fstream& cfout,void** parameter=0,double eps=5e-4);
};
fstream** Particle::fout(string sname,bool first)
{
	string filedir="result\\"+sname+"\\"+name;
	int N=record.size()+1;
	string* filename=new string[N];
	filename[0]="particletY";
	for(int i=1;i<N;i++) filename[i]=record[i-1].name;
	fstream** fout=new fstream*[N];
	if(first)
	{
		string mkfiledir="mkdir "+filedir;
		if((_access(filedir.c_str(),0))==-1) system(mkfiledir.c_str());
		for(int i=0;i<N;i++)
		{
			fout[i]=new fstream;
			fout[i]->open((filedir+"\\"+filename[i]+".txt").c_str(),ios::out);
		}
		return fout;
	}
	else
	{
		for(int i=0;i<N;i++)
		{
			fout[i]=new fstream;
			fout[i]->open((filedir+"\\"+filename[i]+".txt").c_str(),ios::out|ios::app);
		}
		return fout;
	}
}
void Particle::stepmotion(fstream** fout,double h,bool first,void** parameter)
{
	if(!first) ODE(eq,Y,t,h,parameter);
	(*fout[0])<<"t = "<<t<<" ; Y = "<<Y<<endl;
	for(int i=1;i<=record.size();i++) (*fout[i])<<record[i-1].value(*this,parameter)<<endl;
}
void Particle::foutclose(fstream** fout)
{
		for(int i=0;i<=record.size();i++) fout[i]->close();
}
bool Particle::collide(Particle& b,fstream& cfout,void** parameter,double eps)
{
	static bool collided=0;
	static Particle ia(Zero);
	static Particle ib(Zero);
	static Particle fa(Zero);
	static Particle fb(Zero);
	Particle& a=*this;
	double dis=(a.r()-b.r()).magnitude();
	if(dis<eps)
	{
		if(collided==0){ia=a; ib=b; fa=a; fb=b;}
		else{fa=a; fb=b;}
		collided=1;
		return 1;
	}
	else
	{
		if(collided==1)
		{
			Vector cr=(ia.r()+fa.r()+ib.r()+fb.r())/4;
			cfout<<cr[0]<<" "<<cr[1]<<" "<<cr[2]<<" ";
			cfout<<"t="<<(ia.t+fa.t)/2<<"\',sprintf(\'\\n\'),\'"<<(ia.r()+fa.r()+ib.r()+fb.r())/4<<endl;
			cout<<a.name<<", "<<b.name<<" collide at t = "<<(ia.t+fa.t)/2<<" ; r = "<<(ia.r()+fa.r()+ib.r()+fb.r())/4<<endl;
			cout<<" r("<<a.name<<") = "<<(ia.r()+fa.r())/2<<" ; r("<<b.name<<") = "<<(ib.r()+fb.r())/2<<" ;"<<endl;
			cout<<" v("<<a.name<<") = "<<(ia.v()+fa.v())/2<<" ; v("<<b.name<<") = "<<(ib.v()+fb.v())/2<<" ;"<<endl;
			cout<<" a("<<a.name<<") = "<<(ia.a(parameter)+fa.a(parameter))/2<<" ; a("<<b.name<<") = "<<(ia.a(parameter)+fa.a(parameter))/2<<endl;
			cout<<endl;
			collided=0;
			return 0;
		}
		else
		{
			collided=0;
			return 0;
		}
	}
}


class System
{
	typedef Record<System> Rec;
	public:
		Particle* particle;
		int n;
		string name;
		vector<Plotinfo> plotinfo;
		vector<Rec> record;
		
		System(int N,Particle* ptc,string sname,vector<Rec> _record,vector<Plotinfo> _plotinfo):particle(ptc),n(N),name(sname),record(_record),plotinfo(_plotinfo){}
		System(int N,Particle* ptc,string sname,vector<Rec> _record):particle(ptc),n(N),name(sname),record(_record){}
		System(int N,Particle* ptc,string sname):particle(ptc),n(N),name(sname){}
		
		void setRecord(int N,Rec* _record){record.clear();for(int i=0;i<N;i++) record.push_back(_record[i]);}
		void setPlot(int N,Plotinfo* _plotinfo){plotinfo.clear();for(int i=0;i<N;i++) plotinfo.push_back(_plotinfo[i]);}
		
		fstream** fout(bool first=0);
		void stepmotion(fstream** fout,void** parameter=0);
		void foutclose(fstream** fout);
		void motion(double tf,double h=1e-2,void** parameter=0);
		void wait(double ti,double h,void** parameter=0){while(particle[0].t<ti)for(int i=0;i<n;i++) ODE(particle[i].eq,particle[i].Y,particle[i].t,h,parameter);}
		void motion(double ti,double tf,double h,void** parameter=0){wait(ti,h,parameter); motion(tf,h,parameter);}
		
		double tvar(double h,double precise=1e4,double eps=1e-6);
		void varmotion(double tf,double h,void** parameter=0);
		void varwait(double ti,double h,void** parameter=0){while(particle[0].t<ti)for(int i=0;i<n;i++) ODE(particle[i].eq,particle[i].Y,particle[i].t,tvar(h),parameter);}
		void varmotion(double ti,double tf,double h,void** parameter=0){wait(ti,tvar(h)); varmotion(tf,tvar(h),parameter);}
		
		void collide(void** parameter=0,bool collided=1,double eps=5e-4);
		
		void plot(string sname,string xlabel,string ylabel,string zlabel="");
};
fstream** System::fout(bool first)
{
	string filedir="result\\"+name;
	int N=record.size()+1;
	string* filename=new string[N];
	filename[0]="systemtY";
	for(int i=1;i<N;i++) filename[i]=record[i-1].name;
	fstream** fout=new fstream*[N];
	if(first)
	{
		string mkfiledir="mkdir "+filedir;
		if((_access(filedir.c_str(),0))==-1) system(mkfiledir.c_str());
		for(int i=0;i<N;i++)
		{
			fout[i]=new fstream;
			fout[i]->open((filedir+"\\"+filename[i]+".txt").c_str(),ios::out);
		}
		return fout;
	}
	else
	{
		for(int i=0;i<N;i++)
		{
			fout[i]=new fstream;
			fout[i]->open((filedir+"\\"+filename[i]+".txt").c_str(),ios::out|ios::app);
		}
		return fout;
	}
}
void System::stepmotion(fstream** fout,void** parameter)
{
	(*fout[0])<<"t = "<<particle[0].t<<endl;
	for(int i=0;i<record.size();i++) (*fout[i])<<record[i].value(*this,parameter)<<endl;
}
void System::foutclose(fstream** fout)
{
		for(int i=0;i<=record.size();i++)
		{
		fout[i]->close();
		}
		
}
void System::motion(double tf,double h,void** parameter)
{
	fstream*** pfout=new fstream**[n];
	fstream** sfout=new fstream*[record.size()];
	for(int i=0;i<n;i++) pfout[i]=particle[i].fout(name,1);
	sfout=fout(1);
	for(int i=0;i<n;i++) particle[i].stepmotion(pfout[i],h,1,parameter);
	stepmotion(sfout,parameter);
	if(n>1) collide(parameter,0,h*50);
	for(int i=0;i<n;i++) particle[i].foutclose(pfout[i]);
	foutclose(sfout);
	for(int i=0;i<n;i++) pfout[i]=particle[i].fout(name,0);
	sfout=fout(0);
	while(particle[0].t<=tf)
	{
		for(int i=0;i<n;i++) particle[i].stepmotion(pfout[i],h,0,parameter);
		stepmotion(sfout,parameter);
		if(n>1) collide(parameter,1,h*50);
	}
	for(int i=0;i<n;i++) particle[i].foutclose(pfout[i]);
	foutclose(sfout);
	for(int i=0;i<n;i++) cout<<particle[i].name<<" done"<<endl;
}
double System::tvar(double h,double precise,double eps)
{
	double dis=0;
	bool flag=false;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			dis=(particle[i].Y[0]-particle[j].Y[0]).magnitude();
			if(dis/precise<h){flag=true;break;}
		}
		if(flag) break;
	}
	if(flag) return (dis/precise)>eps?(dis/precise):eps;
	else return h;
}
void System::varmotion(double tf,double h,void** parameter)
{
	fstream*** pfout=new fstream**[n];
	fstream** sfout=new fstream*[record.size()];
	for(int i=0;i<n;i++) pfout[i]=particle[i].fout(name,1);
	sfout=fout(1);
	for(int i=0;i<n;i++) particle[i].stepmotion(pfout[i],tvar(h),1,parameter);
	stepmotion(sfout,parameter);
	if(n>1) collide(parameter,0,5e-4);
	for(int i=0;i<n;i++) particle[i].foutclose(pfout[i]);
	foutclose(sfout);
	for(int i=0;i<n;i++) pfout[i]=particle[i].fout(name,0);
	sfout=fout(0);
	while(particle[0].t<=tf)
	{
		for(int i=0;i<n;i++) particle[i].stepmotion(pfout[i],tvar(h),0,parameter);
		stepmotion(sfout,parameter);
		if(n>1) collide(parameter,1,5e-4);
	}
	for(int i=0;i<n;i++) particle[i].foutclose(pfout[i]);
	foutclose(sfout);
	for(int i=0;i<n;i++) cout<<particle[i].name<<" done"<<endl;
}
void System::collide(void** parameter,bool collided,double eps)
{
	string filedir="result\\"+name;
	string fcoutname=filedir+"\\collide.txt";
	fstream fcout;
	if(collided==0)
	{
		string mkfiledir="mkdir "+filedir;
		if((_access(filedir.c_str(),0))==-1) system(mkfiledir.c_str());
		fcout.open(fcoutname.c_str(),ios::out);
	}
	else fcout.open(fcoutname.c_str(),ios::out|ios::app);
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			particle[i].collide(particle[j],fcout,parameter,eps);
	fcout.close();
}
void System::plot(string sname,string xlabel,string ylabel,string zlabel)
{
	vector<int> number;
	for(int i=0;i<n;i++) number.push_back(particle[i].plotinfo.size());
	number.push_back(plotinfo.size());
	int sum=0;
	for(int i=0;i<=n;i++) sum+=number[i];
	
	string* xfile=new string[sum];
	string* yfile=new string[sum];
	string* zfile=new string[sum];
	string* property=new string[sum];
	string* legend=new string[sum];
	string collide="result\\"+name+"\\collide.txt";
	
	int k=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<number[i];j++)
		{
			xfile[k]=((particle[i].plotinfo[j].x=="")?"0":"result\\"+name+"\\"+particle[i].name+"\\"+particle[i].plotinfo[j].x+".txt");
			yfile[k]=((particle[i].plotinfo[j].y=="")?"0":"result\\"+name+"\\"+particle[i].name+"\\"+particle[i].plotinfo[j].y+".txt");
			property[k]=particle[i].plotinfo[j].p;
			legend[k]=particle[i].plotinfo[j].l;
			k++;
		}
	}
	for(int j=0;j<number[n];j++)
	{
		xfile[k]=((plotinfo[j].x=="")?"0":"result\\"+name+"\\"+plotinfo[j].x+".txt");
		yfile[k]=((plotinfo[j].y=="")?"0":"result\\"+name+"\\"+plotinfo[j].y+".txt");
		property[k]=plotinfo[j].p;
		legend[k]=plotinfo[j].l;
		k++;
	}
	
	bool havez=false;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<number[i];j++)
		{
			if(particle[i].plotinfo[j].z!=""){havez=true;break;}
		}
		if(havez) break;
	}
	for(int j=0;j<number[n];j++)
	{
		if(plotinfo[j].z!=""){havez=true;break;}
	}
	if(havez)
	{
		int k=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<number[i];j++)
			{
				zfile[k]=((particle[i].plotinfo[j].z=="")?"0":"result\\"+name+"\\"+particle[i].name+"\\"+particle[i].plotinfo[j].z+".txt");
				k++;
			}
		}
		for(int j=0;j<number[n];j++)
		{
			zfile[k]=((plotinfo[j].z=="")?"0":"result\\"+name+"\\"+plotinfo[j].z+".txt");
			k++;
		}
	}
	
	string matlabdir="matlab";
	string mkfiledir="mkdir "+matlabdir;
	if((_access(matlabdir.c_str(),0))==-1) system(mkfiledir.c_str());
	string matlabfile=matlabdir+"\\"+name+".m";
	if(havez) matlab3(matlabfile,sum,xfile,yfile,zfile,property,legend,collide,sname,xlabel,ylabel,zlabel);
	else matlab2(matlabfile,sum,xfile,yfile,property,legend,collide,sname,xlabel,ylabel);
	cout<<name<<" done"<<endl;
}
#endif
