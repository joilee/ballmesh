// ballmesh.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ball2Triangle.h"







int _tmain(int argc, _TCHAR* argv[])
{
	BallStruct ball;
	ball.center=Vector3d(0,0,0);
	ball.r=10;
	ball.l=0.5;
	ball.z1=8;
	ball.z2=6;

	vector<Vector3d> V;
	vector<Vector3i> F;
	generateMesh(ball,V,F);

	return 0;
}

