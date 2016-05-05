//�H�U�{�����Ѧ��j��u108�ťүZ�i�|�tF74046462�s�@
//equation.h�]�t�U�عB����������{��

#ifndef equation_h
#define equation_h
using namespace std;

//����B�� 
Vector_Space projectile(double& t,Vector_Space& x,void** parameter=0)
{
	Vector_Space xf(x.size());
	xf[0]=x[1]; //xf[0]=x'
	xf[1]=Vector(0,-9.8,0); //xf[1]=x''
	return xf;
}

//�����B�� 
Vector_Space vibration(double& t,Vector_Space& x,void** parameter=0)
{
	double m=1,k=1,c=0;
	Vector L(0,0,0);
	if(parameter!=0)
	{
		m=*(double*)parameter[0];
		L=*(Vector*)parameter[1];
		k=*(double*)parameter[2];
		c=*(double*)parameter[3];
	}
	
	Vector_Space xf(x.size());
	xf[0]=x[1]; //xf[0]=x'
	xf[1]=(-k*(x[0]-L)-c*(x[1][0]!=0?x[1].unit():0))/m; //xf[1]=x''
	return xf;
}

//�Ů���O�B�� 
Vector_Space RM(double& t,Vector_Space& x,void** parameter=0)
{
	Vector_Space xf(x.size());
	xf[0]=x[1]; //xf[0]=x'
	xf[1]=Vector(9.8,0,0)-10*x[1]; //xf[1]=x''
	return xf;
}

//��� 
Vector_Space rotate(double& t,Vector_Space& x,void** parameter=0)
{
	Vector_Space xf(x.size());
	xf[0]=x[1]; //xf[0]=x'
	xf[1]=-1*(x[0]!=Vector(0)?x[0].unit():0); //xf[1]=x''
	return xf;
}
#endif
