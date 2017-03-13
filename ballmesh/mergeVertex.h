#ifndef  MERGEVERTEX
#define  MERGEVERTEX

#include "vector.h"
#include <vector>
using namespace std;

typedef struct objNode  
{
	double x;
	double y;
	double z;
};

void importObjFile(string objPath, std::vector<Vector3d> &V,std::vector<Vector3i>& F);

void exporObj(string objPath,std::vector<Vector3d> &V,std::vector<Vector3i>& F);

void mergeVertice(vector<vector<Vector3d> >&arrayV,vector<vector<Vector3i>  >&arrayF);

void updateVertexIndex(vector<Vector3d>& sourcePoint,vector<objNode>& totalpoints);

void updateFaceIndex(vector<Vector3d>& sourcePoint,vector<objNode>& totalpoints,vector<Vector3i >&sourceF);
#endif