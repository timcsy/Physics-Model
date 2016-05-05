//以下程式均由成大資工108級甲班張頌宇F74046462製作
//matlab.h包含輸出Matlab檔(.m)的函式

#ifndef matlab_h
#define matlab_h

#include <iostream>
#include <fstream>
using namespace std;

//2維作圖 
void matlab2(string outfile,int num,string xfile[],string yfile[],string property[],string legend[],string collide,string title,string xlabel,string ylabel)
{
	fstream fout;
	fout.open(outfile.c_str(),ios::out);
	fout<<"clear all"<<endl;
	
	for(int i=0;i<num;i++)
	{
		fstream finx,finy;
		finx.open(xfile[i].c_str(),ios::in);
		finy.open(yfile[i].c_str(),ios::in);
		string x;
		finx>>x;
		fout<<"x"<<i<<"=["<<x;
		while(finx>>x) fout<<","<<x;
		fout<<"]"<<endl;
		string y;
		finy>>y;
		fout<<"y"<<i<<"=["<<y;
		while(finy>>y) fout<<","<<y;
		fout<<"]"<<endl;
		finx.close();
		finy.close();
	}
	
	fout<<"plot(x0,y0,\'"<<property[0]<<"\'";
	for(int i=1;i<num;i++)
	{
		fout<<",x"<<i<<",y"<<i<<",\'"<<property[i]<<"\'";
	}
	fout<<")"<<endl;
	fout<<"legend(\'"<<legend[0]<<"\'";
	for(int i=1;i<num;i++)
	{
		fout<<",\'"<<legend[i]<<"\'";
	}
	fout<<")"<<endl;
	fstream finc;
	finc.open((collide).c_str(),ios::in);
	string cx,cy,cz,ctext;
	while(finc>>cx>>cy>>cz>>ctext) fout<<"text("<<cx<<","<<cy<<",[\'"<<ctext<<"\'],\'BackgroundColor\',[1 1 1])"<<endl;
	finc.close();
	fout<<"title(\'"<<title<<"\')"<<endl;
	fout<<"xlabel(\'"<<xlabel<<"\')"<<endl;
	fout<<"ylabel(\'"<<ylabel<<"\')"<<endl;
	fout<<"grid on"<<endl;
	fout.close();
}

//3維作圖 
void matlab3(string outfile,int num,string xfile[],string yfile[],string zfile[],string property[],string legend[],string collide,string title,string xlabel,string ylabel,string zlabel)
{
	fstream fout;
	fout.open(outfile.c_str(),ios::out);
	fout<<"clear all"<<endl;
	
	for(int i=0;i<num;i++)
	{
		fstream finx,finy,finz;
		char none='0';
		int s=0,t=0,u=0;
		if(xfile[i]!="0") finx.open(xfile[i].c_str(),ios::in);
		if(yfile[i]!="0") finy.open(yfile[i].c_str(),ios::in);
		if(zfile[i]!="0") finz.open(zfile[i].c_str(),ios::in);
		if(xfile[i]!="0")
		{
			string x;
			finx>>x;
			fout<<"x"<<i<<"=["<<x;
			while(finx>>x){fout<<","<<x;s++;}
			fout<<"]"<<endl;
		}
		else none='x';
		if(yfile[i]!="0")
		{
			string y;
			finy>>y;
			fout<<"y"<<i<<"=["<<y;
			while(finy>>y){fout<<","<<y;t++;}
			fout<<"]"<<endl;
		}
		else none='y';
		if(zfile[i]!="0")
		{
			string z;
			finz>>z;
			fout<<"z"<<i<<"=["<<z;
			while(finz>>z){fout<<","<<z;u++;}
			fout<<"]"<<endl;
		}
		else none='z';
		if(xfile[i]!="0") finx.close();
		if(yfile[i]!="0") finy.close();
		if(zfile[i]!="0") finz.close();
		
		switch(none)
		{
			case 'x':
				fout<<"x"<<i<<"=[0";
				for(int j=0;j<t;j++) fout<<",0";
				fout<<"]"<<endl;
				break;
			case 'y':
				fout<<"y"<<i<<"=[0";
				for(int j=0;j<s;j++) fout<<",0";
				fout<<"]"<<endl;
				break;
			case 'z':
				fout<<"z"<<i<<"=[0";
				for(int j=0;j<s;j++) fout<<",0";
				fout<<"]"<<endl;
				break;
		}
	}
	
	fout<<"plot3(x0,y0,z0,\'"<<property[0]<<"\'";
	for(int i=1;i<num;i++)
	{
		fout<<",x"<<i<<",y"<<i<<",z"<<i<<",\'"<<property[i]<<"\'";
	}
	fout<<")"<<endl;
	fout<<"legend(\'"<<legend[0]<<"\'";
	for(int i=1;i<num;i++)
	{
		fout<<",\'"<<legend[i]<<"\'";
	}
	fout<<")"<<endl;
	fstream finc;
	finc.open((collide).c_str(),ios::in);
	string cx,cy,cz,ctext;
	while(finc>>cx>>cy>>cz>>ctext) fout<<"text("<<cx<<","<<cy<<","<<cz<<",[\'"<<ctext<<"\'],\'BackgroundColor\',[1 1 1])"<<endl;
	finc.close();
	fout<<"title(\'"<<title<<"\')"<<endl;
	fout<<"xlabel(\'"<<xlabel<<"\')"<<endl;
	fout<<"ylabel(\'"<<ylabel<<"\')"<<endl;
	fout<<"zlabel(\'"<<zlabel<<"\')"<<endl;
	fout<<"grid on"<<endl;
	fout.close();
}
#endif
