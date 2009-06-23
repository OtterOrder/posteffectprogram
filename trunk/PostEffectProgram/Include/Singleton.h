#pragma once

#include <stdlib.h>


template< typename T >
class Singleton
{
public:

	static T* GetSingleton( void )
	{
		if( !m_Instance )
			m_Instance = new T;

		return m_Instance;
	}

	static void Destroy( void )
	{
		if( m_Instance )
		{
			delete m_Instance;
			m_Instance = NULL;
		}
	}


protected:

	Singleton			( void ){}		
	virtual ~Singleton	( void ){}	


private:

	static T	*m_Instance;		

};

template< typename T >
T* Singleton< T >::m_Instance = NULL;


