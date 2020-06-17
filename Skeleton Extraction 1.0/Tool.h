#ifndef _TOOL_H_
#define _TOOL_H_

#include<vector>
#include<math.h>

#include "ToolMesh.h"

#ifndef PI
#define PI 3.1415926535
#endif

namespace MeshLib
{
	using namespace std;

	template<typename M>
	class CTool
	{
	public:
		CTool(M* pMesh);
		~CTool(){};

		void test();
	protected:
		typename M* m_pMesh;
	};

	template<typename M>
	CTool<M>::CTool(M* pMesh)
	{
		m_pMesh = pMesh;
	}

	template<typename M>
	void CTool<M>::test()
	{
		cout << "mesh vertex num: " << m_pMesh->numVertices() << endl;
	}

	
}
#endif