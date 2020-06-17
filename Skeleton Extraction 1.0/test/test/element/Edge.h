/*!
*      \file Edge.h
*      \brief Base class of edge
*/


#ifndef _MESHLIB_EDGE_H_
#define _MESHLIB_EDGE_H_

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string>

namespace MeshLib{

class CHalfEdge;
class CVertex;

/*!
\边类
*/
class CEdge
{
public:
	/*!
		无参构造器
	*/
	CEdge(){ m_halfedge[0] = NULL; m_halfedge[1] = NULL; };
	/*!
		析构函数
	*/
	~CEdge(){};
	
	/*!
		当前边的两条半边
	*/
	CHalfEdge * & halfedge( int id ) { assert( 0<=id && id < 2 ); return m_halfedge[id];};
	/*!	
		边是否在边界上（边界边只有一条半边）
	*/
	bool		  boundary() { return (m_halfedge[0] == NULL && m_halfedge[1] != NULL ) || (m_halfedge[0] != NULL && m_halfedge[1] == NULL ); };
	/*!
		查找另一条半边
	*/
	CHalfEdge * & other( CHalfEdge * he ) { return (he != m_halfedge[0] )?m_halfedge[0]:m_halfedge[1]; };
    /*!
		The string of the current edge.
	*/
	std::string & string() { return m_string; };
	/*!
		Read the traits from the string.
	*/
	void _from_string() {};
	/*!
		Save the traits to the string.
	*/
	void _to_string() {};
protected:
	/*!
		Pointers to the two halfedges attached to the current edge.
	*/
	CHalfEdge      * m_halfedge[2];
	/*!
		The string associated to the current edge.
	*/
    std::string      m_string;
};





}//name space MeshLib

#endif //_MESHLIB_EDGE_H_ defined