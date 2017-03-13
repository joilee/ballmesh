#ifndef BALLTRIANGLE
#define  BALLTRIANGLE

#include <iostream>
#include <vector>
#include "vector.h"
#define  _USE_MATH_DEFINES
using namespace std;
typedef struct Ball
{
	double r;
	double l;
	Vector3d center;
	double z1;
	double z2;
}BallStruct;

typedef struct pointVer
{
	Vector3d coordinates;
	int id;
	int layerId;
}pv;

void generateMesh(BallStruct ball, std::vector<Vector3d> &V,std::vector<Vector3i>& F	);
void generateCirclePoint(double r,double l,Vector3d o,vector<pointVer> &Pset);
void	generateFace(vector<vector<pointVer> >&totalPoint,vector<Vector3i> &F	);
int getNearestVertex(const pointVer a,const vector<pointVer>&b);

#endif