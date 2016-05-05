//�H�U�{�����Ѧ��j��u108�ťүZ�i�|�tF74046462�s�@
//Vector�O3���H�U���V�q
//���{����Vector���V�q�[��k�B�Y�ƿn�B���n�B�~�n�B�j�p�B��V�q�����B���V�q���\�� 

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
		Vector(double x,double y,double z); //5 initialization of Vector, x,y,z�O3���V�q�����q 
						
		double magnitude(); //�V�q�j�p 
		double angle(Vector b); //��V�q����
		Vector unit(); //���V�q
		
		friend Vector operator+(Vector a,Vector b); //�w�q�[�k(�����۹��������ӧO�ۥ[)
		friend Vector operator-(Vector a,Vector b); //�w�q��k(�����۹��������ӧO�۴�)
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
		Vector operator-() const //�[�k�Ϥ��� 
		{Vector Zero(0,0,0);return Zero-*this;}
		
		template<class T>
		Vector& operator+=(T b){*this=*this+b;return *this;} //�w�q+=�B��l
		template<class T>
		Vector& operator-=(T b){*this=*this-b;return *this;} //�w�q-=�B��l
		template<class T>
		Vector& operator*=(T b){*this=*this*b;return *this;} //�w�q*=�B��l
		template<class T>
		Vector& operator/=(T b){*this=*this/b;return *this;} //�w�q/=�B��l
		
		friend bool operator==(Vector a,Vector b); //�w�q==�B��l
		friend bool operator!=(Vector a,Vector b){return !(a==b);} //�w�q!=�B��l
		
		double& operator [](int i) //���oVector����i�������q
		{if(i<V.size())return V[i]; else throw "index overflow";}
		template<class T>
		Vector& operator=(T b){*this=Vector(b);return *this;} //definition of assignment operator
		
		int size() const //���oVector_Space�}�C����
		{return V.size();}
		
		string toString() //�NVector_Space�ন�ƹ�Φ��r��
		{
			string s;
			stringstream ss;
			ss<<"("<<V[0];
			for(int i=1;i<size();i++) ss<<","<<V[i];
			ss<<")";
			ss>>s;
			return s;
		}
		friend ostream& operator<<(ostream& output,Vector a) //�w�q��X��Ƭy
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
