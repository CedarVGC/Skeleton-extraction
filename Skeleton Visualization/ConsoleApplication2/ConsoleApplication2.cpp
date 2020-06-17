
#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <map>
#include <GL/glut.h>
#include "StrUtil.h"
#include "Point.h"
#define MAX_LINE 2048
using namespace std;
vector<CPoint> Vertex;
map<int, vector<int> > Edge;
void read_E(const char * input)
{
	std::fstream is(input, std::fstream::in);
	if (is.fail())
	{
		fprintf(stderr, "Error in opening file %s\n", input);
		return;
	}

	char buffer[MAX_LINE];
	//is.getline(buffer, MAX_LINE);
	int count = 0;
	while (is.getline(buffer, MAX_LINE))
	{
		std::string line(buffer);
		line = strutil::trim(line);
		cout << "读入" << line << endl;
		strutil::Tokenizer stokenizer(line, " \r\n");
		stokenizer.nextToken();
		CPoint p;
		for (int i = 0; i < 3; i++)
		{
			std::string token = stokenizer.getToken();
			p[i] = strutil::parseString<float>(token);
			stokenizer.nextToken();
		}
		Vertex.push_back(p);
		stokenizer.nextToken();
		stokenizer.nextToken();
		vector<int> temp;
		string before;
		for (;;)
		{
			std::string token = stokenizer.getToken();
			temp.push_back(strutil::parseString<int>(token));
			before = token;
			stokenizer.nextToken();
			token = stokenizer.getToken();
			if (before==token)
			{
				cout << endl;
				break;
			}
		}
		Edge[count++] = temp;
		
	}

}
void rotate()
{
	for (int i = 0; i < Vertex.size(); i++)
	{
		float temp = Vertex[i][0];
		Vertex[i][0] = Vertex[i][2];
		Vertex[i][2] = -temp;
	}
}
void myDisplay(void) {
	rotate();
	glClear(GL_COLOR_BUFFER_BIT);     
	//glPointSize(50.0f);
	glBegin(GL_POINTS);
	/*glVertex3f(0, 0,0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f,- 0.5f);*/
	for (int i = 0; i < Vertex.size(); i++)
	{
		glVertex3f(Vertex[i][0], Vertex[i][1] ,Vertex[i][2] );
	}
	glEnd();
	//glLineWidth(500.0f);
	for (int i = 0; i < Edge.size(); i++)
	{
		for (int j = 0; j < Edge[i].size(); j++)
		{
			glBegin(GL_LINES);
			CPoint v1 = Vertex[i];
			CPoint v2 = Vertex[Edge[i][j]];
			glVertex3f(v1[0],v1[1],v1[2]);
			glVertex3f(v2[0], v2[1], v2[2]);
			glEnd();
		}
	}
	/*glBegin(GL_LINES);
	glVertex3f(0, 0,0);
	glVertex3f(0.5f, 0.5f,0.5f);
	glEnd();*/
	glFlush();		/*保证前面的 OpenGL 命令立即执行（而不是让它们在缓冲区中等待）。其作用跟 fflush(stdout)类似。 */
}
int main(int argc, char *argv[]) {
	read_E("dog.txt");
	cout << Vertex.size();
	for (int i = 0; i < Vertex.size(); i++)
	{
		cout << Vertex[i][0] << " " << Vertex[i][1] << " " << Vertex[i][2] << endl;
	}
	for (int i = 0; i < Edge.size(); i++)
	{
		cout << "和" << Edge[i].size() << "个边相连" << endl;
		for (int j = 0; j < Edge[i].size(); j++)
		{
			cout << Edge[i][j] << " ";
		}
		cout << endl;
	}
	getchar();
	glutInit(&argc, argv);    
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);    										
	glutInitWindowPosition(100, 100);     
	glutInitWindowSize(600, 400);     
	glutCreateWindow("第一个 OpenGL 程序");     							
	glutDisplayFunc(&myDisplay);
	glutMainLoop();   
	return 0;
}
