//以下程式均由成大資工108級甲班張頌宇F74046462製作
//record.h包含各種自定義的Record標籤 

#ifndef record_h
#define record_h

#include "physics.h"
using namespace std;

/*example for particle
string S_value(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.value;
	ss>>s;
	return s;
}
Record R_record("value",S_value);
*/
/*example for system
string S_value(System& sys,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<sys.value;
	ss>>s;
	return s;
}
Record R_record("value",S_value);
*/
//here you go
string S_t(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.t;
	ss>>s;
	return s;
}
Record<Particle> R_t("t",S_t);

string S_x(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.x();
	ss>>s;
	return s;
}
Record<Particle> R_x("x",S_x);

string S_y(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.y();
	ss>>s;
	return s;
}
Record<Particle> R_y("y",S_y);

string S_z(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.z();
	ss>>s;
	return s;
}
Record<Particle> R_z("z",S_z);

string S_vx(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.vx();
	ss>>s;
	return s;
}
Record<Particle> R_vx("vx",S_vx);

string S_vy(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.vy();
	ss>>s;
	return s;
}
Record<Particle> R_vy("vy",S_vy);

string S_vz(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.vz();
	ss>>s;
	return s;
}
Record<Particle> R_vz("vz",S_vz);

string S_ax(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.ax();
	ss>>s;
	return s;
}
Record<Particle> R_ax("ax",S_ax);

string S_ay(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.ay();
	ss>>s;
	return s;
}
Record<Particle> R_ay("ay",S_ay);

string S_az(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<p.az();
	ss>>s;
	return s;
}
Record<Particle> R_az("az",S_az);

string S_Us(Particle& p,void** parameter=0)
{
	double k=1;
	Vector L(0,0,0);
	if(parameter!=0)
	{
		L=*(Vector*)parameter[1];
		k=*(double*)parameter[2];
	}
	stringstream ss;
	string s;
	ss<<(p.r()-L)*(p.r()-L)/2;
	ss>>s;
	return s;
}
Record<Particle> R_Us("Us",S_Us);

string S_Ek(Particle& p,void** parameter=0)
{
	stringstream ss;
	string s;
	ss<<(p.m)*(p.v())*(p.v())/2;
	ss>>s;
	return s;
}
Record<Particle> R_Ek("Ek",S_Ek);

string S_E(Particle& p,void** parameter=0)
{
	double k=1;
	Vector L(0,0,0);
	if(parameter!=0)
	{
		L=*(Vector*)parameter[1];
		k=*(double*)parameter[2];
	}
	stringstream ss;
	string s;
	ss<<(p.r()-L)*(p.r()-L)/2+(p.m)*(p.v())*(p.v())/2;
	ss>>s;
	return s;
}
Record<Particle> R_E("E",S_E);
#endif
