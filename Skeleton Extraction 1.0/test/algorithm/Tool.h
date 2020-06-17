#ifndef _TOOL_H_
#define _TOOL_H_

#include<vector>
#include<map>
#include<math.h>
#include "ToolMesh.h"
#ifndef PI
#define PI 3.1415926535
#endif

namespace MeshLib
{
	using namespace std;
	class Sphere //��������
	{
	public:
		Sphere() {};
		~Sphere() {};
		int    m_id;
		CPoint p;
		CPoint normal;
		double r;
		int key;
		bool isCover;


	};
	template<typename M>
	class CTool
	{
	public:
		CTool(M* pMesh);
		~CTool(){};
		void test();//���㶥����
		void _change_color();//�ı���ɫ
		void com_normal();//�����ķ�����
		void com_normal_face();//������ķ�����
		void com_square_face();//����������
		void com_size();//��������ƽ���߳�
		void extend_Vertex();
		CPoint  extend(CPoint &p1, CPoint& p2, double L);//p2�㣬
		CPoint  extend2(CPoint &p1, CPoint&  normal, double L);//p2Ϊ������

	protected:
		typename M* m_pMesh;
		double L=0;//ƽ���߳�
		double B = 0.3;
		std::map<int,int>           m_edges;//�Ǽܱ�
		std::map<int ,CPoint>         m_verts;//�Ǽܵ�
	};

	template<typename M>
	CTool<M>::CTool(M* pMesh)
	{
		m_pMesh = pMesh;
	}

	template<typename M>
	void CTool<M>::test()
	{
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			pVertex->point() = extend2(pVertex->point(), pVertex->normal(), 0.1*B*L);
		}
		cout << "ģ������" << endl;
		
	}

	template<typename M>
	void CTool<M>::_change_color()
	{
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			pVertex->rgb()[0] = 1;
			pVertex->rgb()[1] = 0;
			pVertex->rgb()[2] = 0;
		}
	}
	template<typename M>
	void CTool<M>::com_normal()
	{
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			int i = 0;
			double sum = 0;
			for (M::VertexFaceIterator me(pVertex); !me.end(); me++)
			{
				M::CFace* pFace = me.value();
				i++;
				pVertex->normal()= pVertex->normal()+pFace->normal();
			}
			pVertex->normal() = pVertex->normal() / i;
			//cout << "�������Ϊ" << pVertex->point()[0] << " " << pVertex->point()[1] << " " << pVertex->point()[2] << endl;
			//cout <<"��ķ�����Ϊ"<< pVertex->normal()[0] << " " << pVertex->normal()[1] << " " << pVertex->normal()[2] << endl;
			//CPoint temp = extend2(pVertex->point(), pVertex->normal(), 0.1*B*L);
			//cout << "������������Ϊ" << temp[0] << " " << temp[1] << " " << temp[2] << endl;
			//break;
		}
		
		cout << "�����ķ�����" << endl;
	}
	//������ķ�����
	template<typename M>
	void CTool<M>::com_normal_face()
	{
		for (M::MeshFaceIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CFace*  pFace =mv.value();
			CPoint p0= pFace->halfedge()->source()->point();
			CPoint p1=pFace->halfedge()->target()->point();
			CPoint p2=pFace->halfedge()->he_next()->target()->point();
			pFace->normal() = (p1 - p0) ^ (p2 - p1);
		}
		cout << "������ķ�����"<<endl;
	}
	//������
	template<typename M>
	void CTool<M>::com_square_face()
	{
		for (M::MeshFaceIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CFace* pFace = mv.value();
			int i=0;
			double s[3];
			for (M::FaceEdgeIterator me(pFace); !me.end(); me++)
			{
				M::CEdge* pEdge = me.value();
				s[i++] =m_pMesh->edgeLength(pEdge);
			}
			double p =( s[0] + s[1] + s[2])/2;
			pFace->Square() = sqrt(p*(p - s[0]) * (p - s[1])*(p - s[2]));
		}
			
			cout<<m_pMesh->faces().back()->Square()<<endl;
	}
	template<typename M>
	void CTool<M>::com_size()
	{
		L = 0;
		for (M::MeshFaceIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CFace* pFace = mv.value();
			for (M::FaceEdgeIterator me(pFace); !me.end(); me++)
			{
				M::CEdge* pEdge = me.value();
				L=L+ m_pMesh->edgeLength(pEdge);
			}
		}	
		L = L / (m_pMesh->numEdges() * 3);
		cout << "�������" << m_pMesh->numEdges() << endl;
		cout << "����ƽ���߳���" << L << endl;
	}
	//�ӳ�����
	template<typename M>
	CPoint CTool<M>::extend(CPoint &p1, CPoint& p2,double L)
	{
		double xyz[3];
		for (int i = 0; i < 3; i++)
		{
			xyz[i]= (p2[i] - p1[i])*L / sqrt(pow((p2[0] - p1[0]), 2) + pow((p2[1] - p1[1]), 2) + pow((p2[2] - p1[2]), 2)) + p2[i];
		}
		CPoint p3(xyz[0], xyz[1], xyz[2]);
		return p3;
	}
	//��ģ�ͱ�������ŵ�ķ���������BxL������
	template<typename M>
	CPoint CTool<M>::extend2(CPoint &p1, CPoint& normal, double L)
	{
		//cout << "���ε������Ϊ" << p1[0] << " " << p1[1] << " " << p1[2] << endl;
		//cout << "���ε�ķ�����Ϊ" << normal[0] << " " << normal[1] << " " << normal[2] << endl;
		double xyz[3];
		for (int i = 0; i < 3; i++)
		{
			xyz[i] =p1[i]-(normal[i])*L / sqrt(pow((normal[0]), 2) + pow((normal[1]), 2) + pow((normal[2]), 2));
			//cout << xyz[i] << endl;
		}
		CPoint p2(xyz[0], xyz[1], xyz[2]);
		//cout << "�����������������Ϊ" << p2[0] << " " << p2[1] << " " << p2[2] << endl;
		return p2;
	}
	template<typename M>
	void CTool<M>::extend_Vertex()
	{
		vector<Sphere> s;
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex  *pVertex =mv.value();
			Sphere pe;	
			pe.m_id = pVertex->id();
			pe.p = pVertex->point();
			pe.normal = pVertex->normal();
			pe.p = extend2(pe.p, pe.normal, 0.1*B*L);
			s.push_back(pe);
		}
		cout << "�ڲ����ʼ�����" << endl;
		for (int i =0; i <s.size(); i++)
		{
			M::CVertex* v1=NULL;
			double min_r1 = 9999;
			for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
			{
				M::CVertex* pVertex = mv.value();
				double temp= sqrt(pow((s[i].p)[0]- pVertex->point()[0],2)+ pow((s[i].p)[1] - pVertex->point()[1], 2)+ pow((s[i].p)[2] - pVertex->point()[2], 2));
				if (temp <min_r1)
				{
					min_r1 = temp;
					v1 = pVertex;
				}
			}
			M::CVertex* v2=NULL;
			double before_min = 0;
			double min_r2 = 9999;
			int count = 0;
			for(;;)
			{
				min_r2 = 9999;
				s[i].p = extend(v1->point(), s[i].p, B*L);
				for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
				{
					M::CVertex* pVertex = mv.value();
					double temp = sqrt(pow((s[i].p)[0] - pVertex->point()[0], 2) + pow((s[i].p)[1] - pVertex->point()[1], 2) + pow((s[i].p)[2] - pVertex->point()[2], 2));
					if (temp < min_r2)
					{
						min_r2 = temp;
						v2 = pVertex;
					}
				}
				if (min_r2 < before_min)
				{
					s[i].r = before_min;
					//cout << "����" <<count << "���ҵ���λ���" << endl;
					break;
				}
				else
				{
					//cout <<++ count<< endl;
					//cout <<"�ٴ�����"<< before_min <<" ";
					before_min = min_r2;
					//cout << min_r2 << endl;
				}
			}
			cout << "���ڴ����"<<i <<"����"<< endl;
			//cout <<s[i].m_id << "ģ�ͱ����������" << v1->id() << " "<< v2->id() << " "<<B*L<<" "<< min_r1 << " " << min_r2<< endl;
		}
		cout << "��λ��㼯��ȡ���" << endl;
		int i_size = 0;
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex  *pVertex = mv.value();
			pVertex->point() = s[i_size++].p;
		}
		cout << "�������" << endl;
	}
		
}
#endif