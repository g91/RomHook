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
		//目前讀取到的位置
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

		//讀取的位置
		inline void*	GetReadBuff()
		{
			return _rec_buff+_rec_pos;
			
		}
		inline void		GetReadBuffSize( int& size , int& size_at_least )
		{
			//剩下空間
			size = _buff_size - _rec_pos;
			if( _rec_buff != _rec_base_buff )
			{
				size_at_least = size;
			}
			else
			{
				//已讀取得大小
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
		//取得完整封包
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
		//通知讀取完資料
		inline void		ReadData( int size )
		{
			_rec_pos += size;
		}

		//整理記憶體(一定要執行完 GetPacket 把所有的完整封包處理掉)
		inline void		ResetBuff()
		{
			int	datasize = _rec_pos - _unread_pos;

			if( datasize == 0 )
			{
				//如果是大封包,buff是new出來,讀取會剛好大小
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

			//讀取Size 不足夠表示封包長度
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
			//讀取如果是大封包
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
