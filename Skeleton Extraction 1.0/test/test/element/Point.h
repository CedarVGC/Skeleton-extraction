/*!
*       Point.h
*      ʵ����Cpoint��
*/

#ifndef _MESHLIB_POINT_H_
#define _MESHLIB_POINT_H_

#include <assert.h>
#include <math.h>
#include <string>
#include <sstream>


namespace MeshLib{

/*
���Ա�ʾ��ά�㣬Ҳ���Ա�ʾ��ά����
�����˴������������ʵ�ֵ�������Ļ�������
*/
class CPoint{

public:
	/*!
	 * �вι���������x,y,z��
	 */
	CPoint( double x, double y, double z ){ v[0] = x; v[1] = y; v[2] = z;};
	/*!
	*	�޲ι�������Ĭ������Ϊ��0��0��0��
	*/
	CPoint() { v[0] = v[1] = v[2] = 0; };
	/*!
	*	��������
	*/
	~CPoint(){};

	/*!
	*	���������[]
	*   ʵ���±���ʹ���
	*/
	double & operator[]( int i)		  { assert( 0<=i && i<3 ); return v[i]; };
	/*!
	*	���������()
	*   ʵ���±���ʹ���
	*/
	double   operator()( int i) const { assert( 0<=i && i<3 ); return v[i]; };
	/*!
	*	���������[]
	*   ʵ���±���ʹ���
	*/
	double   operator[]( int i) const { assert( 0<=i && i<3 ); return v[i]; };

	/*!
	 *	���ص㵽ԭ��ľ���������ĳ���
	 */
	double norm() const { return sqrt( fabs( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] ) ); };

	/*!
	 *	���������+=
	*   ʵ��������ӹ���
	 */
	CPoint  & operator += ( const CPoint & p) { v[0] += p(0); v[1] += p(1); v[2] += p(2); return *this; }; 
	/*!
	 *	���������-=
	*   ʵ�������������
	 */
	CPoint  & operator -= ( const CPoint & p)  { v[0] -= p(0); v[1] -= p(1); v[2] -= p(2); return *this; };
	/*!
	 *	���������*=
	*   ʵ���������Գ�������
	 */
	
	CPoint  & operator *= ( const double  s) { v[0] *= s   ; v[1] *=    s; v[2] *=    s; return *this; };
	/*!
	 *	���������+=
	*   ʵ���������Գ�������
	 */
	CPoint  & operator /= ( const double  s) { v[0] /= s   ; v[1] /=    s; v[2] /=    s; return *this; };

	/*!
	 *	���������*
	*   ʵ��������˹���
	 */

	double   operator*( const CPoint & p ) const 
	{
		return v[0] * p[0] + v[1] * p[1] + v[2] * p[2]; 
	};

	/*!
	 *	���������+
	*   ʵ��������ӹ���
	 */
	CPoint   operator+( const CPoint & p  ) const
	{
		CPoint r( v[0] + p[0], v[1] + p[1], v[2] + p[2] );
		return r;
	};
	/*!
	 *	���������-
	*   ʵ�������������
	 */
	CPoint   operator-( const CPoint & p  ) const
	{
		CPoint r( v[0] - p[0], v[1] - p[1], v[2] - p[2] );
		return r;
	};
	/*!
	 *	���������*
	*   ʵ���������Գ�������
	 */
	CPoint   operator*( const double s  ) const
	{
		CPoint r( v[0] * s, v[1] * s, v[2] * s );
		return r;
	};
	/*!
	  *	���������/
	*   ʵ���������Գ�������
	 */
	CPoint   operator/( const double s  ) const
	{
		CPoint r( v[0] / s, v[1] / s, v[2] / s );
		return r;
	};

	/*!
	  *	���������^
	*   ʵ��������˹���
	 */
	CPoint operator^( const CPoint & p2) const
	{
		CPoint r( v[1] * p2[2] - v[2] * p2[1],
			      v[2] * p2[0] - v[0] * p2[2],
		           v[0] * p2[1] - v[1] * p2[0]);
		return r;
	};

	/*!
	 *	���������-
	*   ʵ������ȡ������
	 */
	CPoint operator-() const
	{
		CPoint p(-v[0],-v[1],-v[2]);
		return p;
	};

protected:
	/*!
	* �洢x,y,z���������
	*/
	double v[3];
};

/*!
 *	��string��ʵ����Cpoint
 * string�ĸ�ʽΪ(x,y,z)
 */
inline void operator>>(const std::string & str, CPoint &p )
{
	std::string t = str;
	t.erase(0, t.find_first_not_of("()") );//ȥ������֮ǰ�����ݣ��������ţ�
	t.erase(t.find_last_not_of("()") + 1);////ȥ������֮������ݣ��������ţ�
	std::istringstream iss( t );//�����������
	iss >> p[0] >> p[1] >> p[2];
}
}//name space MeshLib

#endif //_MESHLIB_POINT_H_ defined