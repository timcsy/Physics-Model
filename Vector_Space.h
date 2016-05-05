//�H�U�{�����Ѧ��j��u108�ťүZ�i�|�tF74046462�s�@
//Vector_Space is the class that store a series of Vectors
//Vector_Space �㦳�u�ʥN�ƪ��ʽ�(���[�k�B�Y�ƿn���B��)�A�i�H����Runge-Kutta method���w�q��έȰ�

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
		
		friend Vector_Space operator+(Vector_Space a,Vector_Space b); //�w�q�[�k(�����۹��������ӧO�ۥ[)
		friend Vector_Space operator-(Vector_Space a,Vector_Space b); //�w�q��k(�����۹��������ӧO�۴�)
		friend Vector_Space operator*(Vector_Space a,double b);  //�w�q�Y�ƿn(�U�������H�@���)
		friend Vector_Space operator*(double a,Vector_Space b); //�w�q�Y�ƿn(�U�������H�@���)
		friend Vector_Space operator/(Vector_Space a,double b); //�w�q�Y�ƿn(�U�������H�@���)
		Vector_Space operator-() const //�w�q�[�k�Ϥ��� 
		{Vector_Space Zero(this->size());return Zero-*this;}
		
		template<class T>
		Vector_Space& operator+=(T b){*this=*this+b;return *this;} //�w�q+=�B��l
		template<class T>
		Vector_Space& operator-=(T b){*this=*this-b;return *this;} //�w�q-=�B��l
		template<class T>
		Vector_Space& operator*=(T b){*this=*this*b;return *this;} //�w�q*=�B��l
		template<class T>
		Vector_Space& operator/=(T b){*this=*this/b;return *this;} //�w�q/=�B��l
		
		friend bool operator==(Vector_Space a,Vector_Space b); //�w�q==�B��l
		friend bool operator!=(Vector_Space a,Vector_Space b){return !(a==b);} //�w�q!=�B��l
		
		Vector& operator [](int i) //���oVector_Space����i����Vector
		{if(i<V.size())return V[i];else throw "index overflow";}
		template<class T>
		Vector_Space& operator=(T b){*this=Vector_Space(b);return *this;} //definition of assignment operator
		
		int size() const //���oVector_Space�}�C����
		{return V.size();}
		
		string toString() //�NVector_Space�ন�ƹ�Φ��r��
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
		friend ostream& operator<<(ostream& output,Vector_Space a) //�w�q��X��Ƭy
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
