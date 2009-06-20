#include "Types.h"

//******************************************************************************************************************************
#define SAFE_DELETE(p)		\
{							\
	if (p)					\
	{						\
		delete p;			\
		p = NULL;			\
	}						\
}

//******************************************************************************************************************************
#define SAFE_RELEASE(p)		\
{							\
	if (p)					\
	{						\
		p->Release();		\
		p = NULL;			\
	}						\
}

//******************************************************************************************************************************
#define SAFE_NEW(p, type)	\
{							\
	if (!p)					\
	{						\
		p = new type;		\
	}						\
}

//******************************************************************************************************************************
#include <vector>

#define DefineVectorIterator(type, name)	typedef std::vector< type* >::iterator name

//******************************************************************************************************************************
bool Warning(bool _test, cStr _str);


#define WarningReturn(test, msg)	\
{									\
	if (Warning(test, msg))			\
	{								\
		return;						\
	}								\
}
