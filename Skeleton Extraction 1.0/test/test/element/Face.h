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
	����
*/
class CFace
{
public:
	/*!	
	�޲ι�����
	*/
	CFace(){ m_halfedge = NULL; };
	/*!
	��������
	*/
	~CFace(){};
	/*!
	�����ڵ�ǰ���һ�����
	*/
	CHalfEdge    *		& halfedge() { return m_halfedge; };
	/*!
		��ǰ��id
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
	/*��ķ�����*/
	CPoint & normal() { return m_normal; };
	/*���ƽ���ܳ�*/
	double& Size() { return size; };
	/*������*/
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
	double size;//�߳�֮��
	double square;//���
	/*!
		String of the current face.
	*/
    std::string        m_string;
};


}//name space MeshLib

#endif //_MESHLIB_FACE_H_ defined