//以下程式均由成大資工108級甲班張頌宇F74046462製作
//Vector_Space is the class that store a series of Vectors
//Vector_Space 具有線性代數的性質(有加法、係數積等運算)，可以做為Runge-Kutta method的定義域及值域

#ifndef Vector_Space_h
#define Vector_Space_h

#include "Vector.h"
using namespace std;

class Vector_Space
{
	protected:
		vector<Vector> V; //V to store Vectors series 
	public:
		Vector_Space(); //1 initialization of Vector_Space
		Vector_Space(int n); //2 initialization of Vector_Space, n is the total index
		Vector_Space(vector<Vector> v):V(v){} //3 initialization of Vector_Space
		Vector_Space(int n,Vector* v); //4 initialization of Vector_Space, n is the total index, v is a Vector array whose length is n
		
		friend Vector_Space operator+(Vector_Space a,Vector_Space b); //定義加法(內部相對應元素個別相加)
		friend Vector_Space operator-(Vector_Space a,Vector_Space b); //定義減法(內部相對應元素個別相減)
		friend Vector_Space operator*(Vector_Space a,double b);  //定義係數積(各元素乘以一實數)
		friend Vector_Space operator*(double a,Vector_Space b); //定義係數積(各元素乘以一實數)
		friend Vector_Space operator/(Vector_Space a,double b); //定義係數積(各元素除以一實數)
		Vector_Space operator-() const //定義加法反元素 
		{Vector_Space Zero(this->size());return Zero-*this;}
		
		template<class T>
		Vector_Space& operator+=(T b){*this=*this+b;return *this;} //定義+=運算子
		template<class T>
		Vector_Space& operator-=(T b){*this=*this-b;return *this;} //定義-=運算子
		template<class T>
		Vector_Space& operator*=(T b){*this=*this*b;return *this;} //定義*=運算子
		template<class T>
		Vector_Space& operator/=(T b){*this=*this/b;return *this;} //定義/=運算子
		
		friend bool operator==(Vector_Space a,Vector_Space b); //定義==運算子
		friend bool operator!=(Vector_Space a,Vector_Space b){return !(a==b);} //定義!=運算子
		
		Vector& operator [](int i) //取得Vector_Space索引i中的Vector
		{if(i<V.size())return V[i];else throw "index overflow";}
		template<class T>
		Vector_Space& operator=(T b){*this=Vector_Space(b);return *this;} //definition of assignment operator
		
		int size() const //取得Vector_Space陣列長度
		{return V.size();}
		
		string toString() //將Vector_Space轉成數對形式字串
		{
			if(V.empty()) return "(0)";
			string s;
			stringstream ss;
			ss<<"("<<V[0];
			for(int i=1;i<size();i++) ss<<","<<V[i];
			ss<<")";
			ss>>s;
			return s;
		}
		friend ostream& operator<<(ostream& output,Vector_Space a) //定義輸出資料流
		{output<<a.toString();return output;}
};
//define Vector_Space functions
Vector_Space::Vector_Space()
{
	V.clear();
}
Vector_Space::Vector_Space(int n)
{
	V.resize(n,Vector(0));
}
Vector_Space::Vector_Space(int n,Vector* v)
{
	V.resize(n,Vector(0));
	for(int i=0;i<n;i++) V[i]=v[i];
}

Vector_Space operator+(Vector_Space a,Vector_Space b)
{
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) a[i]+=b[i];
		return a;
	}
	else throw "different index of two vectors.";
}
Vector_Space operator-(Vector_Space a,Vector_Space b)
{
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) a[i]-=b[i];
		return a;
	}
	else throw "different index of two vectors.";
}
Vector_Space operator*(double a,Vector_Space b) //Scalar multiplication
{
	for(int i=0;i<b.size();i++) b[i]*=a;
	return b;
}
Vector_Space operator*(Vector_Space a,double b) //Scalar multiplication
{
	for(int i=0;i<a.size();i++) a[i]*=b;
	return a;
}
Vector_Space operator/(Vector_Space a,double b) //Scalar multiplication
{
	if(b==0.0) throw "divide by 0.";
	else
	{
		for(int i=0;i<a.size();i++) a[i]/=b;
		return a;
	}
}

bool operator==(Vector_Space a,Vector_Space b)
{
	bool m=true;
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) if(a[i]!=b[i]){m=false;break;}
	}
	else m=false;
	return m;
}
#endif
