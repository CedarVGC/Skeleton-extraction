#include<iostream>

#include"../algorithm/Tool.h"
#include"../algorithm/ToolMesh.h"

using namespace std;
using namespace MeshLib;


void main(int argc, char** argv)
{
	CTMesh mesh;
	mesh.read_m(argv[1]);
	CTool<CTMesh> tool(&mesh);
	tool.test();


	getchar();



}