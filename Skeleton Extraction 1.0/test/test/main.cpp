#include<iostream>
#include< ctime>
#include"solution/Tool.h"
#include"solution/ToolMesh.h"
using namespace std;
using namespace MeshLib;
void main(int argc, char** argv)
{
	CTMesh mesh;
	clock_t time_start = clock();
	mesh.read_obj("E:\\Skeleton Extraction 1.0\\test\\data\\dog.obj");
	CTool<CTMesh> tool(&mesh);
	tool.test();
	tool.Simplification(0.05);
	cout << "��ʼ��ȡ��λ��㼯" << endl;
	tool.com_size();
	tool.com_square_face();
	tool.com_normal_face();
	tool.com_normal();
	tool.extend_Vertex();
	tool.filtrate_Vertex();
	tool.link_Vertex();
	//tool.show();
	//mesh.write_obj("E:\\Skeleton Extraction 1.0\\test\\data\\sSS.obj");
	tool.write("E:\\Skeleton Extraction 1.0\\test\\data\\dog.txt");
	cout << "�Ǽ��ļ�������ɣ��ļ���Ϊdog.txt" << endl;
	getchar();



}