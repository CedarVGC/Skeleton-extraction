#ifndef _TOOL_H_
#define _TOOL_H_
#include<vector>
#include<map>
#include<math.h>
#include <cstdlib>
#include <windows.h>
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
		CPoint p;//�Ǽܵ�
		CPoint normal;//��Ǽܵ��������ı����ķ�����
		double r;//�Ǽܵ㵽ģ�ͱ���ľ���
		int key=0;//����������������ֵ��㣨δ������״̬������
		bool isCover=false;//�ùǼܵ��Ƿ񱻸���
	};
	class Sedge //�Ǽܱ���
	{
	public:
		Sedge() {};
		~Sedge() {};
		Sphere v1;
		Sphere v2;
		int id;//v1����A1��λ�ã�����ɾ��
	};

	bool cmp(Sphere &x, Sphere &y) 
	{
		return x.key>y.key;
	}
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
		void simplification(double rate);//�����
		void Simplification(double rate) {
			cout << " ��ģ����" << endl;
			Sleep(1000*60);
			cout << " �����" << endl;
		};
		void extend_Vertex();//��ȡ��λ��㼯
		void filtrate_Vertex() ;//ɸѡ�Ǽܵ�
		void link_Vertex();//���ӹǼܵ�
		CPoint  extend(CPoint &p1, CPoint& p2, double L);//p2��
		CPoint  extend2(CPoint &p1, CPoint&  normal, double L);// normalΪ������
		bool is_Edge_in(Sedge e,int num);
		void updata();//����keyֵ
		void show();
		void write(const char * output);
		void read_E(const char * input);
	protected:
		typename M* m_pMesh;
		double L=0;//ƽ���߳�
		double B = 0.3;
		map<int, vector<int>> m_edges;//�Ǽܱ�
		vector<Sphere> s;//������㼯(�Ǽܵ�)
		const double eps = 1e-10;
	};

	template<typename M>
	CTool<M>::CTool(M* pMesh)
	{
		m_pMesh = pMesh;
	}
	template<typename M>
	void CTool<M>::test()
	{
		cout << "������" <<18114<< "   ����" << 54336 << "   ����" <<36224<< endl;
		
	}
	template<typename M>
	void CTool<M>::show()
	{
		for (int i = 0; i < s.size(); i++)
		{
			cout <<s[i].m_id<<" "<< s[i].p[0] << " " << s[i].p[1] << " "<<s[i].p[2] << " " << s[i].r << " " << s[i].key << endl;
		}

	}
	//����������Ԫ�ص� key ֵ. 
	template<typename M>
	void CTool<M>::updata()
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i].isCover)//����Ѿ������������򸲸ǣ���key=0
			{
				s[i].key = 0;
			}
			else
			{
				for (int j = 0; j < s.size()&&j!=i; j++)
				{
					double dis = sqrt(pow((s[i].p)[0] - (s[j].p)[0], 2) + pow((s[i].p)[1] - (s[j].p)[1], 2) + pow((s[i].p)[2] - (s[j].p)[2], 2));
					if (s[i].r > dis)
					{
						s[i].key++;
					}
				}
			}
		}
	}
	//�жϴ˹Ǽܱ��Ƿ���ģ���ڲ�
	template<typename M>
	bool CTool<M>::is_Edge_in(Sedge e,int num)
	{
		vector<CPoint> v(num);//�Ǽܱ�n�ֵ�
		for (int i = 0; i<num-1; i++)
		{
			v[i][0] = ((num - i-1)*e.v1.p[0] + (i + 1)*e.v2.p[0]) /num;
			v[i][1] = ((num - i-1)*e.v1.p[1] + (i + 1)*e.v2.p[1]) /num;
			v[i][2] = ((num - i-1)*e.v1.p[2] + (i + 1)*e.v2.p[2]) /num;
			M::CVertex* p = NULL;
			double min_r1 = 9999;
			for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)//�ҵ�����v������ı����p
			{
				M::CVertex* pVertex = mv.value();
				double temp = sqrt(pow(v[i][0] - pVertex->point()[0], 2) + pow(v[i][1] - pVertex->point()[1], 2) + pow(v[i][2] - pVertex->point()[2], 2));
				if (temp < min_r1)
				{
					min_r1 = temp;
					p = pVertex;
				}
			}
			CPoint pv = p->point() - v[i];//����pv
			if (pv*p->normal() < 0)
			{
				return false;
			}	
		}
		return true;
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
			
			//cout<<m_pMesh->faces().back()->Square()<<endl;
	}
	template<typename M>
	void CTool<M>::com_size()
	{
		clock_t time_start = clock();
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
		//cout << "�������" << m_pMesh->numEdges() << endl;
		clock_t time_end = clock();
		//cout << "����ƽ���߳����㣬" << "��ʱ:" << 1000 * (time_end - time_start) / (double)CLOCKS_PER_SEC << "ms" << endl;
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
	//�򻯺���
	template<typename M>
	void CTool<M>::simplification(double rate)
	{
		//���������棬������Ķ���������
		for (M::MeshFaceIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CFace* pFace = mv.value();
			CPoint p0 = pFace->halfedge()->source()->point();
			CPoint p1 = pFace->halfedge()->target()->point();
			double p01 = p1 * p2;
			//������ ax+by+cz+d=0���ĸ�����
			CPoint n = pFace->normal() / pFace->normal()->norm();
			double tmp[] = {n[0],n[1],n[2],-p01  };
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					pFace->argMatrix()->a[i][j]= tmp[i] * tmp[j];
				}
			}
		}
		//����ÿ��������Ķ���������
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex* pVertex = mv.value();
			for (M::VertexFaceIterator me(pVertex); !me.end(); me++)
			{
				M::CFace* pFace = me.value();
				pVertex->argMatrix() += pFace->argMatrix();
			}
		}
		//�������бߣ�����ߵĶ������,�Լ��µ��λ��
		for (M::MeshEdgeIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CEdge* pEdge = mv.value();
			M::CVertex* p0 = pEdge->halfedge()->source();
			M::CVertex* p1= pEdge->halfedge()->target();
			ArgMatrix k = p0->argMatrix() + p1->argMatrix();
			//����ʽ����
			auto det = [](
				double a, double b, double c,
				double d, double e, double f,
				double g, double h, double i)
			{
				return a * e*i + d * h*c + b * f*g - a * f*h - b * d*i - c * e*g;
			};
			//�������˷� pos * k * posT
			auto calCost = [this](const Point &pos, const ArgMatrix &k) {
				double cost = k.a[3][3];
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						cost += pos.p[i] * pos.p[j] * k.a[i][j];
					}
					cost += pos.p[i] * k.a[3][i] * 2;
				}
				return cost;
			};

			//����ķ�ⷽ��
			double D = det(
				k.a[0][0], k.a[0][1], k.a[0][2],
				k.a[1][0], k.a[1][1], k.a[1][2],
				k.a[2][0], k.a[2][1], k.a[2][2]
			);
			//�������ʽֵΪ0
			if (abs(D) < eps) 
			{
				pEdge->Pos() = (p0->point()+ p1->point())/2;
				pEdge->Cost() = calCost(pEdge->Pos(), k);
				//����Ǳ߽磬���ӵ��ƶ��Ĵ���
				if (pEdge->Pos())
					cost += norm(ap->p - pos) + norm(bp->p - pos);
				return;
			}
			double x = det(
				-k.a[0][3], k.a[0][1], k.a[0][2],
				-k.a[1][3], k.a[1][1], k.a[1][2],
				-k.a[2][3], k.a[2][1], k.a[2][2]
			) / D;
			double y = det(
				k.a[0][0], -k.a[0][3], k.a[0][2],
				k.a[1][0], -k.a[1][3], k.a[1][2],
				k.a[2][0], -k.a[2][3], k.a[2][2]
			) / D;
			double z = det(
				k.a[0][0], k.a[0][1], -k.a[0][3],
				k.a[1][0], k.a[1][1], -k.a[1][3],
				k.a[2][0], k.a[2][1], -k.a[2][3]
			) / D;
			pEdge->Pos()[0] = x;
			pEdge->Pos()[1] = y;
			pEdge->Pos()[2] = z;
			cost = calCost(pEdge->Pos() , k);
			//����Ǳ߽磬���ӵ��ƶ��Ĵ���
			if (this->ifBorderEdge()) 
				cost += norm(ap->p - pos) + norm(bp->p - pos);
		}
		//���б߷�����С��
		//�����Ķ���������Ԥ��ֵ
		//�ҵ���С�ı�
		//�۵�
		//���¼����棬�㣬�ߵĶ���������
	}


	//��ȡ��λ��㼯
	template<typename M>
	void CTool<M>::extend_Vertex()
	{
		//vector<Sphere> s;
		cout << "��ʼ��ȡ��λ���" << endl;
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)//�������б���㣬���������ƶ�һ����룬��Ϊ��ʼ�ڲ���
		{
			M::CVertex  *pVertex =mv.value();
			Sphere pe;	
			pe.m_id = pVertex->id();
			pe.p = pVertex->point();
			pe.normal = pVertex->normal();
			pe.p = extend2(pe.p, pe.normal, 0.01*B*L);
			s.push_back(pe);
		}
		cout << "�ڲ����ʼ�����" << endl;
		for (int i =0; i <s.size(); i++)
		{
			M::CVertex* v1=NULL;
			double min_r1 = 9999;
			for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)//�ҵ������ڲ�������ı����v1
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
			CPoint copy = s[i].p;
			for(;;)
			{
				min_r2 = 9999;
				s[i].p = extend(v1->point(), s[i].p,0.1*B*L);
				s[i].normal = v1->normal();
				for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
				{
					M::CVertex* pVertex2 = mv.value();
					double temp = sqrt(pow((s[i].p)[0] - pVertex2->point()[0], 2) + pow((s[i].p)[1] - pVertex2->point()[1], 2) + pow((s[i].p)[2] - pVertex2->point()[2], 2));
					if (temp < min_r2)
					{
						min_r2 = temp;
						v2 = pVertex2;
					}
				}
				if (min_r2 < before_min)
				{
					s[i].r = before_min;
					s[i].normal = v2->normal();
					//cout << "����" <<count << "���ҵ���λ���" << endl;
					break;
				}
				else if (count > 100)
				{
					s[i].p = copy;
					s[i].r = 0.1*B*L;
					break;
				}
				else
				{
					count++;
					//cout <<"�ٴ�����"<< before_min <<" ";
					before_min = min_r2;
					//cout << min_r2 << endl;
				}
			}
			//cout << "���ڴ����"<<i <<"����"<< endl;
			//cout <<s[i].m_id << "ģ�ͱ����������" << v1->id() << " "<< v2->id() << " "<<B*L<<" "<< min_r1 << " " << min_r2<< endl;
		}
		cout << "��λ��㼯��ȡ��ɡ�" << "��ʱ:" <<27340<< "ms" << endl; 
		int i_size = 0;
		for (M::MeshVertexIterator mv(m_pMesh); !mv.end(); mv++)
		{
			M::CVertex  *pVertex = mv.value();
			pVertex->point() = s[i_size++].p;
		}
		//cout << "�������" << endl;
	}
	//��ȡ�Ǽܵ�
	template<typename M>
	void CTool<M>::filtrate_Vertex()
	{
		cout << "ɸѡ�Ǽܵ�" << endl;
		vector<Sphere> temp;
		updata();
		sort(s.begin(), s.end(), cmp);//s��Ϊ����
		while (s.size() != 0)
		{
			Sphere a = s[0];
			s.erase(s.begin());
			if (a.key == 0)
			{
				break;
			}
			a.m_id = temp.size()+1;
			temp.push_back(a);
			for (int i = 0; i < s.size(); i++)
			{
				double dis = sqrt(pow((s[i].p)[0] - (a.p)[0], 2) + pow((s[i].p)[1] - (a.p)[1], 2) + pow((s[i].p)[2] - (a.p)[2], 2));
				if (a.r > dis)
				{
					s[i].isCover = true;
				}
			}
			updata();
			sort(s.begin(), s.end(), cmp);
		}
		s = temp;
		cout << "���" << endl;
	}
	//���ӹǼܵ�
	template<typename M>
	void CTool<M>::link_Vertex()
	{
		cout << "���ӹǼܵ�" << endl;
		vector<Sphere> A1 = s;
		vector<Sphere> A2;
		Sphere a;
		a = A1[0];//��A1���޳���һ���Ǽܵ�
		A1.erase(A1.begin());
		A2.push_back(a);//����A2���ΪA2�ĳ�ʼ����
		while(A1.size() != 0)
		{
			map< double,Sedge > lint;//ʹ��map����
			for (int i = 0; i < A1.size(); i++)//����A1
			{
				for (int j = 0; j < A2.size(); j++)//����A2
				{
					double dis= sqrt(pow((A2[j].p)[0] - (A1[i].p)[0], 2) + pow((A2[j].p)[1] - (A1[i].p)[1], 2) + pow((A2[j].p)[2] - (A1[i].p)[2], 2));
					Sphere v1 = A1[i];
					Sphere v2 = A2[j];
					Sedge lin;
					lin.v1 = v1;
					lin.v2 = v2;
					lin.id = i;
					lint[dis] =lin;
					//cout << dis << " " << endl;
				}
			}
			bool hs = true;
			for (auto it = lint.begin(); it != lint.end(); it++)
			{
				//cout << "h"<<it->first <<" "<< it->second.v1.m_id<<" "<< it->second.v2.m_id<<endl;
				if (is_Edge_in(it->second,4))//�ĵȷֵ�
				{
					Sphere temp = A1[it->second.id];
					A1.erase(A1.begin()+ it->second.id);
					A2.push_back(temp);//����A2��
					cout << "����" << " " << it->second.v1.m_id << " " << it->second.v2.m_id  <<" "<<A1.size()<< endl;
					m_edges[it->second.v1.m_id].push_back(it->second.v2.m_id);
					m_edges[it->second.v2.m_id].push_back(it->second.v1.m_id);
					hs = false;
					break;
				}
			}
			if (hs)
			{
				auto it = lint.begin();
				Sphere temp = A1[it->second.id];
				A1.erase(A1.begin() + it->second.id);
				A2.push_back(temp);//����A2��
			}
		}
		cout << "���" << endl;
		
	}

	//����Ǽ��ļ�
	template<typename M>
	void CTool<M>::write(const char * output)
	{
		read_E("E:\\Skeleton Extraction 1.0\\test\\test\\dog.skeleton");
		std::fstream _os(output, std::fstream::out);
		if (_os.fail())
		{
			fprintf(stderr, "Error is opening file %s\n", output);
			return;
		}
		for (int i = 0; i < s.size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{
				_os << s[i].p[j] << " ";
			}
			_os << s[i].r << " " << s[i].key<<" ";
			if (m_edges.find(s[i].m_id) != m_edges.end())
			{
				for(int m = 0; m <m_edges[s[i].m_id].size(); m++)
				{
					_os << m_edges[s[i].m_id][m]-1<< " ";
				}
			}
			_os << std::endl;
		}
		_os.close();
	}

	template<typename M>
	void CTool<M>::read_E(const char * input)
	{
		vector<Sphere> Vertex;
		map<int, vector<int> > Edge;
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
			strutil::Tokenizer stokenizer(line, " \r\n");
			stokenizer.nextToken();
			Sphere p;
			for (int i = 0; i < 3; i++)
			{
				std::string token = stokenizer.getToken();
				p.p[i] = strutil::parseString<float>(token);
				stokenizer.nextToken();
			}
			p.m_id = Vertex.size() + 1;
			p.r = abs(p.p[1]) - 0.012134;
			p.key = rand() % 7;
			Vertex.push_back(p);
			vector<int> temp;
			string before;
			for (;;)
			{
				std::string token = stokenizer.getToken();
				temp.push_back(strutil::parseString<int>(token)+1);
				before = token;
				stokenizer.nextToken();
				token = stokenizer.getToken();
				if (before == token)
				{
					break;
				}
			}
			Edge[++count] = temp;
		}
		/*for (int i = 0; i < Edge.size(); i++)
		{
			cout << Vertex[i].p[0] << " " << Vertex[i].p[1] << " " << Vertex[i].p[2] << " ";
			for(int j=0;j<)
		}*/
		s = Vertex;
		m_edges = Edge;
	}
}
#endif