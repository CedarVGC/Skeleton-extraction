#ifndef _TOOL_MESH_H_
#define _TOOL_MESH_H_

#include<map>
#include<vector>

#include "../element/BaseMesh.h"
#include "../element/Vertex.h"
#include "../element/HalfEdge.h"
#include "../element/Edge.h"
#include "../element/Face.h"
#include "../element/boundary.h"
#include "../element/iterators.h"
#include "../utils/parser.h"
#include "../element/Point.h"
#include "../element/Point2.H"

using namespace std;

namespace MeshLib
{
	class ArgMatrix
	{
		double a[4][4];

		ArgMatrix& operator+=(const ArgMatrix &b)
		{
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					a[i][j] += b.a[i][j];
				}
			}
			return *this;
		}
		ArgMatrix& operator-=(const ArgMatrix &b)
		{
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					a[i][j] -= b.a[i][j];
				}
			}
			return *this;
		}
		void clear()
		{
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					a[i][j] = 0;
				}
			}
		}
	};
	class CToolVertex : public CVertex
	{
	public:
		CToolVertex(){

			m_fixed = false;

		};
		~CToolVertex(){};
		void _to_string();
		void _from_string();

		bool & fixed() { return m_fixed; };
		CPoint & rgb() { return m_rgb; };
		ArgMatrix & argMatrix(){ return k; };
	protected:
		ArgMatrix k;//该点参数矩阵
		bool m_fixed;
		CPoint m_rgb;
	};

	inline void CToolVertex::_from_string()
	{
		CParser parser(m_string);

		for (std::list<CToken*>::iterator iter = parser.tokens().begin(); iter != parser.tokens().end(); ++iter)
		{
			CToken * token = *iter;
			/*if (token->m_key == "uv")
			{
				double u, v;
				sscanf(token->m_value.c_str(), "(%lf %lf)", &u, &v);
				m_huv[0] = u;
				m_huv[1] = v;
			}*/
		}
	}

	inline void CToolVertex::_to_string()
	{
		std::string a;
		m_string = a;

		if (1)
		{
			CParser parser3(m_string);
			parser3._removeToken("rgb");
			parser3._toString(m_string);
			std::stringstream iss3;
			iss3 << "rgb=(" << m_rgb[0] << " " << m_rgb[1] << " " << m_rgb[2] << ")";
			if (m_string.length() > 0)
			{
				m_string += " ";
			}
			m_string += iss3.str();
		}
	}

	class CToolEdge:public CEdge
	{
	public:
		CToolEdge(){
		};
		~CToolEdge(){};
		void _to_string();
		void _from_string();
		double & Cost() { return cost; };
		CPoint & Pos() { return pos; };
	protected:
		double cost;//二次误差代价
		CPoint pos;//新点的位置
	};

	inline void CToolEdge::_to_string()
	{
		std::string a;
		m_string = a;

	/*	CParser parser(m_string);
		parser._removeToken("sharp");
		parser._toString(m_string);
		stringstream iss;
		iss << "sharp";
		if (m_string.length() > 0)
		{
			m_string += " ";
		}
		if (m_sharp == true)
		{
			m_string += iss.str();
		}*/
	}

	inline void CToolEdge::_from_string()
	{
		CParser parser(m_string);

		for (std::list<CToken*>::iterator iter = parser.tokens().begin(); iter != parser.tokens().end(); ++iter)
		{
			CToken * token = *iter;
			/*if (token->m_key == "uv")
			{
			double u, v;
			sscanf(token->m_value.c_str(), "(%lf %lf)", &u, &v);
			m_huv[0] = u;
			m_huv[1] = v;
			}*/
		}
	}

	class CToolFace : public CFace
	{
	public:
		CToolFace(){};
		~CToolFace(){};
		void _to_string();
		ArgMatrix & argMatrix() { return k; };
	protected:
		ArgMatrix k;
	};

	inline void CToolFace::_to_string()
	{
		std::string a;
		m_string = a;
	}

	class CToolHalfEdge : public CHalfEdge
	{
	public:
		CToolHalfEdge(){};
		~CToolHalfEdge(){};
		double & angle(){ return m_angle; };
		void _to_string();
	protected:
		double m_angle;
	};

	inline void CToolHalfEdge::_to_string()
	{
		//std::string a;
		//m_string = a;
	}

	template<typename V,typename E,typename F,typename H>
	class CToolMesh : public CBaseMesh<V, E, F, H>
	{
	public:
		typedef V CVertex;
		typedef E CEdge;
		typedef F CFace;
		typedef H CHalfEdge;

		typedef CBoundary<V, E, F, H> CBoundary;
		typedef CLoop<V, E, F, H> CLoop;

		typedef MeshVertexIterator<V, E, F, H> MeshVertexIterator;
		typedef MeshEdgeIterator<V, E, F, H> MeshEdgeIterator;
		typedef VertexVertexIterator<V, E, F, H> VertexVertexIterator;
		typedef VertexEdgeIterator<V, E, F, H> VertexEdgeIterator;
		typedef MeshFaceIterator<V, E, F, H> MeshFaceIterator;
		typedef FaceVertexIterator<V, E, F, H> FaceVertexIterator;
		typedef VertexFaceIterator<V, E, F, H> VertexFaceIterator;
		typedef FaceHalfedgeIterator<V, E, F, H> FaceHalfedgeIterator;
		typedef VertexOutHalfedgeIterator<V, E, F, H> VertexOutHalfedgeIterator;
		typedef VertexInHalfedgeIterator<V, E, F, H> VertexInHalfedgeIterator;
		typedef FaceEdgeIterator<V, E, F, H> FaceEdgeIterator;
	};

	typedef CToolMesh<CToolVertex, CToolEdge, CToolFace, CToolHalfEdge> CTMesh;


}


























#endif