/*!
*      \file Face.h
*      \brief Base class of face
*
*/

#ifndef _MESHLIB_FACE_H_
#define _MESHLIB_FACE_H_

#include <assert.h>
#include <string>
#include "Point.h"

namespace MeshLib{


class CHalfEdge;

/*!
	面类
*/
class CFace
{
public:
	/*!	
	无参构造器
	*/
	CFace(){ m_halfedge = NULL; };
	/*!
	析构函数
	*/
	~CFace(){};
	/*!
	依附于当前面的一条半边
	*/
	CHalfEdge    *		& halfedge() { return m_halfedge; };
	/*!
		当前面id
	*/
	int		            & id()          { return m_id;      };
	/*!
		The value of the current face id.
	*/
	const int             id() const { return m_id;      };
	/*!
		The string of the current face.
	*/
	std::string			& string()     { return m_string; };
	/*!
		Convert face traits to the string.
	*/
	void                  _to_string()   {};
	/*!
		read face traits from the string.
	*/
	void                  _from_string() {};
	/*面的法向量*/
	CPoint & normal() { return m_normal; };
	/*面的平均周长*/
	double& Size() { return size; };
	/*面的面积*/
	double& Square() { return square; };
protected:
	/*!
		id of the current face
	*/
	int			       m_id;
	/*!
		One halfedge  attaching to the current face.
	*/
	CHalfEdge        * m_halfedge;
	CPoint m_normal;
	double size;//边长之和
	double square;//面积
	/*!
		String of the current face.
	*/
    std::string        m_string;
};


}//name space MeshLib

#endif //_MESHLIB_FACE_H_ defined