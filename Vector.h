//以下程式均由成大資工108級甲班張頌宇F74046462製作
//Vector是3維以下的向量
//本程式的Vector有向量加減法、係數積、內積、外積、大小、兩向量夾角、單位向量等功能 

#ifndef Vector_h
#define Vector_h

#include <vector>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Vector
{
	protected:
		vector<double> V; //V to store Vector
	public:
		Vector(); //1 initialization of Vector
		Vector(int n); //2 initialization of Vector, n is the total index
		Vector(vector<double> v):V(v){} //3 initialization of Vector
		Vector(int n,double* v); //4 initialization of Vector, n is the total index, v is a Vector array whose length is n
		Vector(double x,double y,double z); //5 initialization of Vector, x,y,z是3維向量的分量 
						
		double magnitude(); //向量大小 
		double angle(Vector b); //兩向量夾角
		Vector unit(); //單位向量
		
		friend Vector operator+(Vector a,Vector b); //定義加法(內部相對應元素個別相加)
		friend Vector operator-(Vector a,Vector b); //定義減法(內部相對應元素個別相減)
		friend Vector operator*(Vector a,double b); //Scalar multiplication
		friend Vector operator*(double a,Vector b); //Scalar multiplication
		friend double V_dotProduct(Vector a,Vector b); //dot product
		friend double dot(Vector a,Vector b) //dot product
		{return V_dotProduct(a,b);}
		friend Vector V_crossProduct(Vector a,Vector b); //cross product
		friend Vector cross(Vector a,Vector b) //cross product
		{return V_crossProduct(a,b);}
		friend Vector x(Vector a,Vector b) //cross product
		{return V_crossProduct(a,b);}
		friend double operator*(Vector a,Vector b) //dot product
		{return V_dotProduct(a,b);}
		friend Vector operator/(Vector a,double b); //Scalar multiplication
		Vector operator-() const //加法反元素 
		{Vector Zero(0,0,0);return Zero-*this;}
		
		template<class T>
		Vector& operator+=(T b){*this=*this+b;return *this;} //定義+=運算子
		template<class T>
		Vector& operator-=(T b){*this=*this-b;return *this;} //定義-=運算子
		template<class T>
		Vector& operator*=(T b){*this=*this*b;return *this;} //定義*=運算子
		template<class T>
		Vector& operator/=(T b){*this=*this/b;return *this;} //定義/=運算子
		
		friend bool operator==(Vector a,Vector b); //定義==運算子
		friend bool operator!=(Vector a,Vector b){return !(a==b);} //定義!=運算子
		
		double& operator [](int i) //取得Vector索引i中的分量
		{if(i<V.size())return V[i]; else throw "index overflow";}
		template<class T>
		Vector& operator=(T b){*this=Vector(b);return *this;} //definition of assignment operator
		
		int size() const //取得Vector_Space陣列長度
		{return V.size();}
		
		string toString() //將Vector_Space轉成數對形式字串
		{
			string s;
			stringstream ss;
			ss<<"("<<V[0];
			for(int i=1;i<size();i++) ss<<","<<V[i];
			ss<<")";
			ss>>s;
			return s;
		}
		friend ostream& operator<<(ostream& output,Vector a) //定義輸出資料流
		{output<<a.toString();return output;}
};
//define Vector functions
Vector::Vector()
{
	V.resize(3,double(0));
}
Vector::Vector(int n)
{
	V.resize(3,double(0));
}
Vector::Vector(int n,double* v)
{
	V.resize(3,double(0));
	if(n>0 && n<=3)
	{
		for(int i=0;i<n;i++) V[i]=v[i];
	}
	else throw "index > 3";
}
Vector::Vector(double x,double y,double z)
{
	V.resize(3,double(0));
	V[0]=x;
	V[1]=y;
	V[2]=z;
}

Vector operator+(Vector a,Vector b)
{
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) a[i]+=b[i];
		return a;
	}
	else throw "different index of two vectors.";
}
Vector operator-(Vector a,Vector b)
{
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) a[i]-=b[i];
		return a;
	}
	else throw "different index of two vectors.";
}
Vector operator*(double a,Vector b) //Scalar multiplication
{
	for(int i=0;i<b.size();i++) b[i]*=a;
	return b;
}
Vector operator*(Vector a,double b) //Scalar multiplication
{
	for(int i=0;i<a.size();i++) a[i]*=b;
	return a;
}
Vector operator/(Vector a,double b) //Scalar multiplication
{
	if(b==0.0) throw "divide by 0.";
	else
	{
		for(int i=0;i<a.size();i++) a[i]/=b;
		return a;
	}
}

bool operator==(Vector a,Vector b)
{
	bool m=true;
	if(a.size()==b.size())
	{
		for(int i=0;i<a.size();i++) if(a[i]!=b[i]){m=false;break;}
	}
	else m=false;
	return m;
}
double V_dotProduct(Vector a,Vector b) //dot product
{
	if(a.size()==b.size())
	{
		double c=0;
		for(int i=0;i<a.size();i++) c+=a[i]*b[i];
		return c;
	}
	else throw "different index of two vectors.";
}
double Vector::magnitude()
{
	double dot=V_dotProduct(*this,*this);
	return sqrt(dot);
}
double Vector::angle(Vector b)
{
	return acos(V_dotProduct(*this,b)/(this->magnitude()*b.magnitude()));
}
Vector Vector::unit()
{
	return (*this)/(magnitude());
}
//new define function-----------------------------------------------------------
Vector V_crossProduct(Vector a,Vector b) //cross product
{
	if(a.size()==b.size())
	{
		return Vector (a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]);;
	}
	else throw "different index of two vectors.";
}
#endif
