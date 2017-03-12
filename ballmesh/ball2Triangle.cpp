#include "stdafx.h"
#include "ball2Triangle.h"
#include <algorithm>
#include <math.h>
#include <fstream>
void generateCirclePoint(double r,double l,Vector3d o,vector<pointVer> &Pset)
{
	int pointCount=0;
	double alpha;
	//ֻ��������
	if (l>r*sqrt(3)/2)
	{
		pointCount=3;
		alpha=acos(0.5);
	}else
	{
		alpha=2*asin(l/(2*r));
		pointCount=int(2*M_PI/alpha);
	}
	for (int i=0;i<pointCount;i++)
	{
		pointVer tmp;
		tmp.coordinates.z=o.z;
		tmp.coordinates.x=o.x+r*cos(i*alpha);
		tmp.coordinates.y=o.y+r*sin(i*alpha);
		Pset.push_back(tmp);
	}
	//
}
/************************************************************************/
/* �뾶Ϊr��һ����,��������Ϊ0��0��������z1~z2����֮�����Ƭ����Ƭƽ������Ϊl           */
/************************************************************************/
void generateMesh(BallStruct ball, std::vector<Vector3d> &V,std::vector<Vector3i> &F	)
{
	if (ball.z1<ball.z2)//z1Ϊ�ϲ��ֵ�ֵ
	{
		swap(ball.z1,ball.z2);
	}
	if( (ball.z1>ball.center.z+ball.r)||(ball.z2<ball.center.z-ball.r))
	{
		return;
	}
	int layer=int((ball.z1-ball.z2)/ball.l+1);


	//��ÿһ��ȡ�㣬��z1��ʼ
	vector<vector<pointVer> >totalPoint;
	vector<Vector3i> totalFace;
	
	for (int i=0;i<layer;i++)
	{
		//������һ���Բ��
		Vector3d tmpCenter;
		if (i==layer-1)
		{
			tmpCenter.z=ball.z2;
		}else
		{
			tmpCenter.z=ball.z1-i*ball.l;
		}
		tmpCenter.x=ball.center.x;
		tmpCenter.y=ball.center.y;
		//������һ��İ뾶
		double tmpR=sqrt((ball.r)*(ball.r)-(tmpCenter.z-ball.center.z)*(tmpCenter.z-ball.center.z));

		vector<pointVer> pSet;
		generateCirclePoint(tmpR,ball.l,tmpCenter,pSet);
		totalPoint.push_back(pSet);		
	}

	//�����еĵ����ID����0��ʼ. �������V
	int id=0;	
	for (unsigned int i=0;i<totalPoint.size();i++)
	{
		for (unsigned int j=0;j<totalPoint[i].size();j++)
		{	
			totalPoint[i][j].id=id;
			id++;//��0��ʼ
			V.push_back(Vector3d(totalPoint[i][j].coordinates));
		}
	}
	generateFace(totalPoint,F);

	std::ofstream  output("D:\\312.obj");
	output<<std::fixed;
	for (unsigned int i=0;i<totalPoint.size();i++)
	{
		for (unsigned int j=0;j<totalPoint[i].size();j++)
		{
			output<<"v  "<<totalPoint[i][j].coordinates.x<<" "<<totalPoint[i][j].coordinates.y<<" "<<totalPoint[i][j].coordinates.z<<endl;
		}
	}
	for (unsigned int k=0;k<F.size();k++)
	{
		output<<"f  "<<F[k].x+1<<"  "<<F[k].y+1<<" "<<F[k].z+1<<endl;
	}
	output.close();
}

void	generateFace(vector<vector<pointVer>  >&totalPoint,vector<Vector3i> &F	)
{

	for (unsigned int i=0;i<totalPoint.size()-1;i++)
	{
		for (unsigned int j=0;j<totalPoint[i].size();j++)
		{
			int j_next=(j+1)%totalPoint[i].size();
			int id1=getNearestVertex(totalPoint[i][j],totalPoint[i+1]);
			int id2=getNearestVertex(totalPoint[i][j_next],totalPoint[i+1]);

			if (id1==id2)
			{
				//���id��0��ʼ���㣬���Ҫд��obj���ǵ�+1��
				F.push_back(Vector3i(totalPoint[i][j].id,totalPoint[i][j_next].id,totalPoint[i+1][id2].id));
			}else
			{
				F.push_back(Vector3i(totalPoint[i][j].id,totalPoint[i][j_next].id,totalPoint[i+1][id1].id));
				int count=id1;
				for (;count!=id2;)//i����һ��
				{
					int nextcount=(count+1)%totalPoint[i+1].size();
					F.push_back(Vector3i(totalPoint[i][j_next].id,totalPoint[i+1][nextcount].id,totalPoint[i+1][count].id));
					count=nextcount;
				}
			}




		}
	}
}

double point_distance(const pointVer a,const pointVer b)
{
	return sqrt(pow((a.coordinates.x-b.coordinates.x),2)+pow((a.coordinates.y-b.coordinates.y),2)+pow((a.coordinates.z-b.coordinates.z),2));
}

int getNearestVertex(const pointVer a,const vector<pointVer>&b)
{
	double minlenght=point_distance(a,b[0]);
	double pre=minlenght;
	int  id=0;
	for (unsigned int i = 1; i < b.size(); i++)
	{
		double tmplen=point_distance(a,b[i]);
		if (tmplen<minlenght)
		{
			minlenght=tmplen;
			id=i;
		}
		//if (tmplen>pre)
		//{
		//	break;
		//}
	}
	return id;
}