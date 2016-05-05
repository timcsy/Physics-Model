//以下程式均由成大資工108級甲班張頌宇F74046462製作
//testphysic.cpp為主程式 

#include "Model.h"
using namespace std;

int main()
{
	//example of water and bug's collision(2D)
	{
		Particle w(projectile,"Water");
		w.r(0,0,0);
		w.v(1000*cos(rad(45)),1000*sin(rad(45)),0);
		Record<Particle> wrecord[]={R_x,R_y};
		w.setRecord(2,wrecord);
		Plotinfo wplot[]={Plotinfo("x","y",".","Water")};
		w.setPlot(1,wplot);
		
		Particle b(projectile,"Bug");
		b.r(100,100,0);
		b.v(0,0,0);
		Record<Particle> brecord[]={R_x,R_y};
		b.setRecord(2,brecord);
		Plotinfo bplot[]={Plotinfo("x","y",".","Bug")};
		b.setPlot(1,bplot);
		
		Particle pparticle[]={w,b};
		System Collide(2,pparticle,"Collide");
		
		Collide.varmotion(0.13,0.141425,1e-2);
		Collide.plot("水柱撞甲蟲y-x圖","x","y");
	}
	
		
	//example of water and bug's collision(3D)
	{
		Particle w3(projectile,"Water");
		w3.r(0,0,0);
		w3.v(1000*cos(rad(45)),1000*sin(rad(45)),0);
		Record<Particle> w3record[]={R_x,R_y};
		w3.setRecord(2,w3record);
		Plotinfo w3plot[]={Plotinfo("x","","y",".","Water")};
		w3.setPlot(1,w3plot);
		
		Particle b3(projectile,"Bug");
		b3.r(100,100,0);
		b3.v(0,0,0);
		Record<Particle> b3record[]={R_x,R_y};
		b3.setRecord(2,b3record);
		Plotinfo b3plot[]={Plotinfo("x","","y",".","Bug")};
		b3.setPlot(1,b3plot);
		
		Particle pparticle3[]={w3,b3};
		System Collide3(2,pparticle3,"Collide3");
		
		Collide3.varmotion(0.13,0.141425,1e-2);
		Collide3.plot("水柱撞甲蟲x--y圖","x","y");
	}
	
	
	//example of spring vibration
	{
		double m=0.1,k=1,c=0.1;
		Vector L(10,0,0);
		
		Particle Spring(vibration,m,"Spring");
		Spring.r(12,0,0);
		Spring.v(0,0,0);
		Record<Particle> srecord[]={R_t,R_x,R_vx,R_Ek,R_Us,R_E};
		Spring.setRecord(6,srecord);
		Plotinfo splot[]={Plotinfo("t","x","vx",".","Spring v"),Plotinfo("t","x","Ek",".","Spring Ek"),Plotinfo("t","x","Us",".","Spring Us"),Plotinfo("t","x","E",".","Spring E")};
		Spring.setPlot(4,splot);
		
		Particle vparticle[]={Spring};
		System Vibration(1,vparticle,"Vibration");
		
		void* vpm[/*m,L,k,c*/]={(void*)(&m),(void*)(&L),(void*)(&k),(void*)(&c)};
		
		Vibration.varmotion(0,15,1e-3,vpm);
		Vibration.plot("彈簧振動t-x-z圖","t","x","z");
	}
	
	
	//example of rotation
	{
		Particle Ball(rotate,"Ball");
		Ball.r(1,0,0);
		Ball.v(0,1,0);
		Record<Particle> rrecord[]={R_x,R_y};
		Ball.setRecord(2,rrecord);
		Plotinfo rplot[]={Plotinfo("x","y",".","Ball")};
		Ball.setPlot(1,rplot);
		
		Particle rparticle[]={Ball};
		System Rotate(1,rparticle,"Rotate");
		
		Rotate.varmotion(0,2,1e-3);
		Rotate.plot("球轉動x-y圖","x","y");
	}
	
	system("PAUSE");
	return 0;
}
