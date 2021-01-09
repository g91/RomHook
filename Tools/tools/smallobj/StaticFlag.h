#pragma once


template < int S >
struct StaticFlag
{
    char	Flag[ (S-1) / 8 + 1 ];

    StaticFlag()
    {
        ReSet();
    }

	int		Size(){ return S; };
	void	ReSet()			{ memset( Flag , 0 , sizeof(Flag) ); }

    bool	GetFlag(int Pos)
    {
        const unsigned	char F[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
        if( (unsigned)Pos>=S )
            return false;

        if( (Flag[Pos>>3] &F[Pos & 0x7])!=0)
            return true;
        return false;
    }

    bool	SetFlagOn(int Pos)
    {
        const unsigned	char F[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
        if((unsigned)Pos >= S )
            return false;
        //¦PCardArr[Pos/8] &= Flag[Pos % 8]; 
        Flag[Pos>>3] |= F[Pos& 0x7]; // Pos & 7 == Pos %8
        return true;
    }

    bool	SetFlagOff(int Pos)
    {
        const unsigned	char F[8]={0xff-0x01,0xff-0x02,0xff-0x04,0xff-0x08,0xff-0x10,0xff-0x20,0xff-0x40,0xff-0x80};
        if((unsigned)Pos >= S )
            return false;
        //¦PCardArr[Pos/8] &= Flag[Pos % 8]; 
        Flag[Pos>>3] &= F[Pos & 0x7]; 	
        return true;
    }

    int GetFlagValue( int Pos , int Count )
    {
        int RetVal = 0;
        for( int i = 0 ; i < Count ; i++ )
        {
            RetVal <<= 1;
            if( GetFlag( i + Pos ) != false )
                RetVal |= 1;
        }
        return RetVal;
    }

    void SetFlagValue( int Pos , int Count , int Value )
    {
        for( int i = Count-1 ; i >= 0 ; i-- , Value /= 2 )
        {
            if( Value % 2 == 1 )
            {
               SetFlagOn( i + Pos );
            }
            else 
            {
                SetFlagOff( i + Pos );
            }
        }        
    }
};