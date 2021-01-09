#include "IMyAsio.h"
#include "MyAsioBase.h"

namespace MyAsio{


INetAsio*	CreateMyAsio		( )
{
	return (INetAsio*)( new NetAsioBase );
}
void		DeleteNetBridge		( INetAsio* net_asio )
{
	delete net_asio;
}

unsigned	ConvertIP( const char* pszIP )
{
	u_long IP_ADDRESS;

	if( pszIP != NULL )
	{
		if( strlen( pszIP ) != 0 )
		{

			//���տ�J��IP�OIP Address �άO DNS

			//�ഫ IP
			IP_ADDRESS = inet_addr( pszIP ); 

			//������X���G, �Y�Ǧ^ INADDR_NONE ����, ��� IP �i��O DNS
			if ( IP_ADDRESS == INADDR_NONE ) 
			{
				// Host isn't an IP address, try using DNS
				hostent* HE = gethostbyname( pszIP );

				if ( HE == 0 )
				{
					//Error can't check DNS
					return 0;
				}

				IP_ADDRESS = *((u_long*)HE->h_addr_list[0]);
			}
		}
	}

	char* IP_Addr_Point = (char*)&IP_ADDRESS;
	swap( IP_Addr_Point[0] , IP_Addr_Point[3] );
	swap( IP_Addr_Point[1] , IP_Addr_Point[2] );
	return IP_ADDRESS;
}

}// namespace MyAsio