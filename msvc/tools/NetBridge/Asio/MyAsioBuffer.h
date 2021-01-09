#pragma once

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "MyAsioDef.h"

namespace MyAsio{
	
	struct PacketHeader
	{
#pragma pack(1)
		int		Size;
		unsigned char	SystemID;
		unsigned char	CheckSum;
#pragma pack()
	};


	class NetAsioSendBuffer
	{
		int	 _size;
		char _data[ _BASE_PACKET_MAX_SIZE_ ];

	public:
		NetAsioSendBuffer()
		{
			Clear();
		}

		inline bool	Add( int size , void* data )
		{
			if( size + _size > _BASE_PACKET_MAX_SIZE_ )
				return false;
			memcpy( _data+_size , data , size );
			_size += size;
			return true;
		}
		inline void	Clear( )
		{
			_size = 0;
		}
		inline int	Size( )
		{
			return _size;
		}
		inline void* Data( )
		{
			return _data;
		}

	};

	class NetAsioRevBuffer
	{
		
		int						_buff_size;
		char*					_rec_buff;
		char					_rec_base_buff[_BASE_PACKET_MAX_SIZE_*2];
		//�ثeŪ���쪺��m
		int						_rec_pos;
		int						_unread_pos;
	public:
		NetAsioRevBuffer()
		{
			_rec_buff = _rec_base_buff;
			_rec_pos = 0;
			_unread_pos = 0;
			_buff_size = sizeof(_rec_base_buff);
		}
		~NetAsioRevBuffer()
		{
			if( _rec_buff != _rec_base_buff  )
				delete _rec_buff;
		}

		//Ū������m
		inline void*	GetReadBuff()
		{
			return _rec_buff+_rec_pos;
			
		}
		inline void		GetReadBuffSize( int& size , int& size_at_least )
		{
			//�ѤU�Ŷ�
			size = _buff_size - _rec_pos;
			if( _rec_buff != _rec_base_buff )
			{
				size_at_least = size;
			}
			else
			{
				//�wŪ���o�j�p
				int read_size = _rec_pos - _unread_pos;
				if( read_size < sizeof(PacketHeader) )
				{
					size_at_least = sizeof(PacketHeader) - read_size;
				}
				else
				{
					int next_pg_size = *(int*)(_rec_buff+_unread_pos);
					size_at_least = next_pg_size + _unread_pos - _rec_pos + sizeof(PacketHeader);
				}
			}
		}
		//���o����ʥ]
		inline bool		GetPacket( PacketHeader& pHeader , void** data )
		{
			if( _rec_pos - _unread_pos < sizeof(PacketHeader) )
				return false;
			pHeader = *(PacketHeader*)(_rec_buff+_unread_pos);

			if( _rec_pos - _unread_pos < pHeader.Size + sizeof(PacketHeader) )
				return false;
			*data = _rec_buff+_unread_pos+sizeof(PacketHeader);

			_unread_pos = _unread_pos + sizeof(PacketHeader)+ pHeader.Size;

			return true;
		}
		//�q��Ū�������
		inline void		ReadData( int size )
		{
			_rec_pos += size;
		}

		//��z�O����(�@�w�n���槹 GetPacket ��Ҧ�������ʥ]�B�z��)
		inline void		ResetBuff()
		{
			int	datasize = _rec_pos - _unread_pos;

			if( datasize == 0 )
			{
				//�p�G�O�j�ʥ],buff�Onew�X��,Ū���|��n�j�p
				if( _rec_buff != _rec_base_buff )
				{
					delete _rec_buff;
					_rec_buff = _rec_base_buff;
					_buff_size = sizeof( _rec_base_buff );
				}

				_rec_pos = 0;
				_unread_pos = 0;
				return;
			}

			//Ū��Size ��������ܫʥ]����
			if( datasize < sizeof(PacketHeader) )
			{
				if( _unread_pos != 0 )
				{
					memcpy( _rec_buff, _rec_buff + _unread_pos , datasize );
					_unread_pos = 0;
					_rec_pos = datasize;
				}
				return;
			}

			int next_pg_size = *(int*)(_rec_buff+_unread_pos);
			int need_buff_size = next_pg_size + sizeof(PacketHeader);
			//Ū���p�G�O�j�ʥ]
			if( need_buff_size > sizeof( _rec_base_buff ) )
			{
				_rec_buff = new char[need_buff_size];
				_buff_size = need_buff_size;

				memcpy( _rec_buff, _rec_base_buff + _unread_pos , datasize );
				_unread_pos = 0;
				_rec_pos = datasize;
			}
			else if( need_buff_size > _buff_size - _unread_pos )
			{
				memcpy( _rec_buff , _rec_buff + _unread_pos , datasize );
				_unread_pos = 0;
				_rec_pos = datasize;
			}
		}
	};


}// namespace MyAsio
