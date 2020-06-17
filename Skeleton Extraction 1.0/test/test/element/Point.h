/*!
*       Point.h
*      实现了Cpoint类
*/

#ifndef _MESHLIB_POINT_H_
#define _MESHLIB_POINT_H_

#include <assert.h>
#include <math.h>
#include <string>
#include <sstream>


namespace MeshLib{

/*
可以表示三维点，也可以表示三维向量
重载了大多数操作符，实现点和向量的基本运算
*/
class CPoint{

public:
	/*!
	 * 有参构造器，（x,y,z）
	 */
	CPoint( double x, double y, double z ){ v[0] = x; v[1] = y; v[2] = z;};
	/*!
	*	无参构造器，默认坐标为（0，0，0）
	*/
	CPoint() { v[0] = v[1] = v[2] = 0; };
	/*!
	*	析构函数
	*/
	~CPoint(){};

	/*!
	*	重载运算符[]
	*   实现下标访问功能
	*/
	double & operator[]( int i)		  { assert( 0<=i && i<3 ); return v[i]; };
	/*!
	*	重载运算符()
	*   实现下标访问功能
	*/
	double   operator()( int i) const { assert( 0<=i && i<3 ); return v[i]; };
	/*!
	*	重载运算符[]
	*   实现下标访问功能
	*/
	double   operator[]( int i) const { assert( 0<=i && i<3 ); return v[i]; };

	/*!
	 *	返回点到原点的距离或向量的长度
	 */
	double norm() const { return sqrt( fabs( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] ) ); };

	/*!
	 *	重载运算符+=
	*   实现向量相加功能
	 */
	CPoint  & operator += ( const CPoint & p) { v[0] += p(0); v[1] += p(1); v[2] += p(2); return *this; }; 
	/*!
	 *	重载运算符-=
	*   实现向量相减功能
	 */
	CPoint  & operator -= ( const CPoint & p)  { v[0] -= p(0); v[1] -= p(1); v[2] -= p(2); return *this; };
	/*!
	 *	重载运算符*=
	*   实现向量乘以常数功能
	 */
	
	CPoint  & operator *= ( const double  s) { v[0] *= s   ; v[1] *=    s; v[2] *=    s; return *this; };
	/*!
	 *	重载运算符+=
	*   实现向量除以常数功能
	 */
	CPoint  & operator /= ( const double  s) { v[0] /= s   ; v[1] /=    s; v[2] /=    s; return *this; };

	/*!
	 *	重载运算符*
	*   实现向量点乘功能
	 */

	double   operator*( const CPoint & p ) const 
	{
		return v[0] * p[0] + v[1] * p[1] + v[2] * p[2]; 
	};

	/*!
	 *	重载运算符+
	*   实现向量相加功能
	 */
	CPoint   operator+( const CPoint & p  ) const
	{
		CPoint r( v[0] + p[0], v[1] + p[1], v[2] + p[2] );
		return r;
	};
	/*!
	 *	重载运算符-
	*   实现向量相减功能
	 */
	CPoint   operator-( const CPoint & p  ) const
	{
		CPoint r( v[0] - p[0], v[1] - p[1], v[2] - p[2] );
		return r;
	};
	/*!
	 *	重载运算符*
	*   实现向量乘以常数功能
	 */
	CPoint   operator*( const double s  ) const
	{
		CPoint r( v[0] * s, v[1] * s, v[2] * s );
		return r;
	};
	/*!
	  *	重载运算符/
	*   实现向量乘以常数功能
	 */
	CPoint   operator/( const double s  ) const
	{
		CPoint r( v[0] / s, v[1] / s, v[2] / s );
		return r;
	};

	/*!
	  *	重载运算符^
	*   实现向量叉乘功能
	 */
	CPoint operator^( const CPoint & p2) const
	{
		CPoint r( v[1] * p2[2] - v[2] * p2[1],
			      v[2] * p2[0] - v[0] * p2[2],
		           v[0] * p2[1] - v[1] * p2[0]);
		return r;
	};

	/*!
	 *	重载运算符-
	*   实现向量取反功能
	 */
	CPoint operator-() const
	{
		CPoint p(-v[0],-v[1],-v[2]);
		return p;
	};

protected:
	/*!
	* 存储x,y,z三点的坐标
	*/
	double v[3];
};

/*!
 *	用string来实例化Cpoint
 * string的格式为(x,y,z)
 */
inline void operator>>(const std::string & str, CPoint &p )
{
	std::string t = str;
	t.erase(0, t.find_first_not_of("()") );//去掉括号之前的内容（包括括号）
	t.erase(t.find_last_not_of("()") + 1);////去掉括号之后的内容（包括括号）
	std::istringstream iss( t );//从流里读数据
	iss >> p[0] >> p[1] >> p[2];
}
}//name space MeshLib

#endif //_MESHLIB_POINT_H_ defined