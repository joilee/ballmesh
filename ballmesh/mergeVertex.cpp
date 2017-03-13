#include "stdafx.h"
#include "mergeVertex.h"
#include <fstream>
#include <algorithm>
#include <map>


void importObjFile(string objPath, std::vector<Vector3d> &V,std::vector<Vector3i>& F)
{
	V.clear();
	F.clear();
	std::ifstream fileIn(objPath);
	if (!fileIn.is_open())
	{
		return;
	}
	char buffer[256];
	while (!fileIn.eof())
	{
		memset(buffer,0,256);
		fileIn.getline(buffer,256);
		if (strncmp(buffer,"v ",2) == 0) 
		{
			double px, py, pz;
			if (sscanf(buffer, "v %lf %lf %lf", &px, &py, &pz) == 3) 
			{
				V.push_back(Vector3d(px, py, pz));
			}else
			{
				cout<<"parse error, vertex "<<endl;
			}
		}else if (strncmp(buffer,"f ",2) == 0)	
		{
				int x,y,z;
				if (sscanf(buffer, "f %d %d %d", &x, &y, &z) == 3) 
				{
					F.push_back(Vector3i(x-1,y-1,z-1));
				}
		}
	}

}

void exporObj(string objPath,std::vector<Vector3d> &V,std::vector<Vector3i>& F)
{
	 std::ofstream  output(objPath);
	 output<<std::fixed;
	 for (int i=0;i<V.size();i++)
	 {
		 output<<"v "<<V[i].x<<" "<<V[i].y<<" "<<V[i].z<<endl;
	 }
	 for (int i=0;i<F.size();i++)
	 {
		 output<<"f "<<F[i].x+1<<" "<<F[i].y+1<<" "<<F[i].z+1<<endl;;
	 }
	 output.close();
	 return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
bool objNodeCmp(objNode a,objNode b)
{
	if (a.x!=b.x)
	{
		return a.x<b.x;
	}else
	{
	   if (a.y!=b.y)
	   {
		   return a.y<b.y;
	   }else
	   {
			return a.z<b.z;
	   }
	}
}






/************************************************************************/
/* 
���ܣ�������ά���꣬������ȵ��µ�ı��
*/
/************************************************************************/
int getNewIndex(Vector3d vertex,vector<objNode>& totalpoints)
{
	int res=-1;
	for (int i=0;i<totalpoints.size();i++)
	{
		if (vertex.x==totalpoints[i].x&&vertex.y==totalpoints[i].y&&vertex.z==totalpoints[i].z)
		{
			res=i;
			break;
		}
	}
	return res;
}


/************************************************************************/
/* 
���ܣ����µ������
��Σ�ԭʼ�㣬ԭʼ�棬ȫ���������
���Σ�ԭʼ���id�ᱻ����
*/
/************************************************************************/

void updateFaceIndex(vector<Vector3d>& sourcePoint,vector<objNode>& totalpoints,vector<Vector3i >&sourceF)
{
	map<int,int> mp;
	for (int i=0;i<sourcePoint.size();i++)
	{
		int newID=getNewIndex(sourcePoint[i],totalpoints);
		if (newID==-1)
		{
			cout<<"vertex not found "<<i<<endl;
			continue;
		}
		mp.insert(make_pair(i,newID));
	}

	for (int i=0;i<sourceF.size();i++)
	{
		sourceF[i].x=mp[sourceF[i].x];
		sourceF[i].y=mp[sourceF[i].y];
		sourceF[i].z=mp[sourceF[i].z];
	}
	return;
}

void updateVertexIndex(vector<Vector3d>& sourcePoint,vector<objNode>& totalpoints)
{
	sourcePoint.clear();
	for (int i=0;i<totalpoints.size();i++)
	{
		sourcePoint.push_back(Vector3d(totalpoints[i].x,totalpoints[i].y,totalpoints[i].z));
	}
	return;
}


/************************************************************************/
/*
���������ļ��ĵ���в�ȫ�����Ҹ��¶�Ӧ��ı��
��Σ������ļ��ĵ����顢������
���Σ������µ��ļ�����
*/
/************************************************************************/
void mergeVertice(vector<vector<Vector3d> >&arrayV,vector<vector<Vector3i>  >&arrayF)
{

	vector<objNode> totalPoints;
	for (int i=0;i<arrayV[0].size();i++)//arratV[0]�д��ԭʼ�����е�
	{
		objNode o;
		o.x=arrayV[0][i].x;
		o.y=arrayV[0][i].y;
		o.z=arrayV[0][i].z;
		totalPoints.push_back(o);
	}

	//�����е����һ������
	sort(totalPoints.begin(),totalPoints.end(),objNodeCmp);

	updateFaceIndex(arrayV[1],totalPoints,arrayF[1]);
	updateFaceIndex(arrayV[2],totalPoints,arrayF[2]);
	updateVertexIndex(arrayV[1],totalPoints);
	updateVertexIndex(arrayV[2],totalPoints);

	return;
}

