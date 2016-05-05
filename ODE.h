//�H�U�{�����Ѧ��j��u108�ťүZ�i�|�tF74046462�s�@
//ODE.h�]�t�ѷL����{�һݭn���禡
//��Runge-Kutta method(RK4)�B�کԪk(RK1)�H�Υ�ODE�k�D�X���n��
//�H�U������ 
/*******************************************************************************
 *	Let y'=f(t,y)
 *		y(t0)=c��l���� (�Ϊ̰O�@y(t0)[i]=c[i])
 *	�����@��ODE�p�ߤ�{�աAy(t)�����׬�m���V�q�A�L���O��t�L���A�n��Xy(t)
 *	�μg�@�Gy(t)=y(t0)+Integral(f(t',y)dt'),t'=t0~t
 *
 *	f(t,y)�n���ͪ��׬�m���V�q�A�䤤
 *	yf[0]=f1(t,y[0],y[1],...,y[m-1])		=y[0]'
 *	yf[1]=f2(t,y[0],y[1],...,y[m-1])		=y[1]'
 *	yf[2]=f3(t,y[0],y[1],...,y[m-1])		=y[2]'
 *	...
 *	yf[m-1]=fm-1(t,y[0],y[1],...,y[m-1])	=y[m-1]'
 *
 *	��󰪶�ODE
 *	(dnx/dtn)=an-1(t)(dn-1x/dtn-1)+...+a2(t)(d2x/dt2)+a1(t)(dx/dt)+a0(t)x+a(t)=g(t,x)
 *	���w��l����A�n��Xx(t)
 *	Let 
 *	y[0]=x
 *	y[1]=x'
 *	y[2]=x''
 *	...
 *	y[m-1]=x'''(m-1���L��)
 *	���by(t)���A���i��ܡGy[m]=x'''(m���L��)=g(t,x)
 *	
 *	�G
 *	y[0]'	=x'				=y[1]
 *	y[1]'	=x''			=y[2]
 *	y[2]'	=x'''			=y[3]
 *	...
 *	y[m-1]'	=x'''(m���L��)	=y[m]	=(dnx/dtn)=g(t,x)=g(t,y[0],y[1],...,y[m-1])
 *
 *	�ҥH�Af(t,y)�n���ͪ��׬�m���V�q�A�䤤
 *	yf[0]=y[1]
 *	yf[1]=y[2]
 *	yf[2]=y[3]
 *	...
 *	yf[m-1]=g(t,y[0],y[1],...,y[m-1])
 ******************************************************************************/

#ifndef ODE_h
#define ODE_h

#include "Vector_Space.h"
using namespace std;

//using RK4(classical Runge-Kutta method),reference�Ghttps://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
//given f(t,y)=y',yn=y(t=tn),tn,h,and space to store t(n+1)=tnp1 and y(t=t(n+1))=ynp1. h is step-size
template<class VS>
void RK4(VS (*f)(double&,VS&,void**),VS& ynp1,VS& yn,double& tnp1,double& tn,double& h,void** parameter=0)
{
	VS k1,k2,k3,k4,k5,_yn;
	double _tn;
	_tn=tn; _yn=yn;
	k1=f(_tn,_yn,parameter);
	_tn=tn+(h/2); _yn=yn+(h*k1/2);
	k2=f(_tn,_yn,parameter);
	_tn=tn+(h/2); _yn=yn+(h*k2/2);
	k3=f(_tn,_yn,parameter);
	_tn=tn+(h); _yn=yn+(h*k3);
	k4=f(_tn,_yn,parameter);
	ynp1=yn+h*(k1+2*k2+2*k3+k4)/6;
	tnp1=tn+h;
}
//using RK1(Euler method),reference�Ghttps://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
//given f(t,y)=y',yn=y(t=tn),tn,h,and space to store t(n+1)=tnp1 and y(t=t(n+1))=ynp1. h is step-size
template<class VS>
void RK1(VS (*f)(double&,VS&,void**),VS& ynp1,VS& yn,double& tnp1,double& tn,double& h,void** parameter=0)
{
	VS k1,_yn;
	double _tn;
	_tn=tn; _yn=yn;
	k1=f(_tn,_yn,parameter);
	ynp1=yn+h*(k1);
	tnp1=tn+h;
}
//y=y(t=tn),t=tn�A����RK4�� y=y(t=t(n+1)),t=t(n+1). h is step-size
template<class VS>
void ODE(VS (*f)(double&,VS&,void**),VS& y,double& t,double h,void** parameter=0)
{
	RK4(f,y,y,t,t,h,parameter);
}
//using RK4 to count y0+Integral(f(t',y)dt'),t'=t0~t. h is step-size
template<class VS>
VS Integral(VS (*f)(double&,VS&,void**),VS y0,double t0,double t,double h,void** parameter=0)
{
	VS b_y=y0;
	double b_t=t0;
	VS _y;
	double _t;
	RK4(f,_y,b_y,_t,b_t,h,parameter);
	while(_t<t)
	{
		b_y=_y;
		b_t=_t;
		RK4(f,_y,b_y,_t,b_t,h,parameter);
	}
	return b_y;
}
/*Example function of a Classic Newton 2nd Law
double m(double t){return 10.0;}
Vector F(double t){return Vector(0,0,-98.0);}
template<class VS>
VS N2(double& t,VS& x,void** parameter=0)
{
	VS xf(x.size());
	xf[0]=x[1]; //xf[0]=x'
	xf[1]=x[2]; //xf[1]=x''
	xf[2]=Vector(0); //xf[2]=x'''
	return xf;
}
*/
#endif
