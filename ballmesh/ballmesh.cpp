// ballmesh.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ball2Triangle.h"
#include "mergeVertex.h"






int _tmain(int argc, _TCHAR* argv[])
{
	//BallStruct ball;
	//ball.center=Vector3d(0,0,0);
	//ball.r=10;
	//ball.l=0.5;
	//ball.z1=8;
	//ball.z2=6;

	//vector<Vector3d> V;
	//vector<Vector3i> F;
	//generateMesh(ball,V,F);
	vector<vector<Vector3d> > arrayV;
	vector<vector<Vector3i>  > arrayF;
	string a="C:\\Users\\joilee\\Desktop\\111\\prism.obj";
	string b="C:\\Users\\joilee\\Desktop\\111\\prism_part1.obj";
	string c="C:\\Users\\joilee\\Desktop\\111\\prism_part2.obj";
	std::vector<Vector3d> V1,V2,V3;
	std::vector<Vector3i> F1,F2,F3;
	importObjFile(a,V1,F1);
	importObjFile(b,V2,F2);
	importObjFile(c,V3,F3);
	arrayV.push_back(V1);
	arrayV.push_back(V2);
	arrayV.push_back(V3);
	arrayF.push_back(F1);
	arrayF.push_back(F2);
	arrayF.push_back(F3);

	mergeVertice(arrayV,arrayF);
	string d="D:\\12.obj";
	exporObj(d,arrayV[1],arrayF[1]);
	string e="D:\\13.obj";
	exporObj(e,arrayV[2],arrayF[2]);
	return 0;
}

