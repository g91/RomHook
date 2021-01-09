/*
----------------------------------------------------------------------
	filename: 	Encrypt.h
    created:	2005/12/29
	author:		Xun
	
	purpose:	?


----------------------------------------------------------------------
*/





#pragma once

#include <windows.h>



//========================================================================
//�[�K
//========================================================================
class CEncrypt
{
public:
	CEncrypt(void);
	virtual ~CEncrypt(void);
public:

	//�[�ѱK
	//�`�N pResult buffer ������ pSource �j
	//pSource	�n�[�ѱK���ӷ�
	//pResult	�[�ѱK�᪺���G
	//dwSize    �ӷ��ؼФj�p byte
	//dwCipher	�[�ѱK�������ޭ�					
	static void Encrypt( LPVOID pDestination , LPCVOID pSource , DWORD dwSize , DWORD dwCipher );
	
	static DWORD* GetCipher();
protected:

private:
	static DWORD m_dwCipher[];
};

//========================================================================
//��ƥ[�K
//�`�N�����ȳ��O4BYTE
//========================================================================
class CEncryptData
{
public:
	CEncryptData( LONG nOffset );
	virtual ~CEncryptData(void);

public:

protected:
   LONG m_nOffset ;

private:

};

//========================================================================
//�[�K LONG
//========================================================================
class CEncryptLONG : public CEncryptData
{
public:
	CEncryptLONG( LONG lData = 0 , LONG nOffset = -1 );
	virtual ~CEncryptLONG(void);

public:

	//CEncryptLONG = CEncryptLONG
	inline LONG operator = ( const CEncryptLONG& r ) 
	{
		LONG l = r;
		*this = l;
		return l;
	}

	//CEncryptLONG += LONG
	inline LONG operator += ( LONG lVal )
	{
		LONG temp = *this + lVal;
		*this = temp;
		return temp;
	}

	//CEncryptLONG -= LONG
	inline LONG operator -= ( LONG lVal )
	{
		LONG temp = *this - lVal;
		*this = temp;
		return temp;
	}
 
  	//CEncryptLONG = LONG
	inline LONG operator = ( LONG lVal )
	{
		m_lValue = ( lVal ^ CEncrypt::GetCipher()[m_nOffset] );
		return lVal;
	}

	//LONG = CEncryptLONG
	inline operator LONG() const
	{
		return ( m_lValue ^ CEncrypt::GetCipher()[m_nOffset] );
	}
 
protected:
	LONG m_lValue;
private:

};


//========================================================================
//�[�K FLOAT
//========================================================================
class CEncryptFLOAT : public CEncryptData
{
public:
	CEncryptFLOAT( FLOAT fData = 0.0f , LONG nOffset = -1 );
	virtual ~CEncryptFLOAT(void);

public:
	//CEncryptFLOAT = CEncryptFLOAT
	inline FLOAT operator = ( const CEncryptFLOAT& r ) 
	{
		FLOAT f = r;
		*this = f;
		return f;
	}

	//CEncryptFLOAT += FLOAT
	inline FLOAT operator += ( FLOAT fVal )
	{
		FLOAT temp = *this + fVal;
		*this = temp;
		return temp;
	}

	//CEncryptFLOAT -= FLOAT
	inline FLOAT operator -= ( FLOAT fVal )
	{
		FLOAT temp = *this - fVal;
		*this = temp;
		return temp;
	}

	//CEncryptFLOAT = FLOAT
	inline FLOAT operator = ( FLOAT fVal )
	{
		//m_dwData = ( FtoDW(fVal) ^ CEncrypt::GetCipher()[m_nOffset] );
		m_dwData = ( *((DWORD*)&fVal ) ^ CEncrypt::GetCipher()[m_nOffset] );
		return fVal;
	}

	//FLOAT = CEncryptFLOAT
	inline operator FLOAT() const
	{
		//return DWtoF( m_dwData ^ CEncrypt::GetCipher()[m_nOffset] );
		DWORD temp = m_dwData ^ CEncrypt::GetCipher()[m_nOffset];
		return *((FLOAT*)&temp);
	}
protected:
 	DWORD m_dwData;
	
private:

};


//========================================================================
//CEncryptDouble
//========================================================================
class CEncryptDouble : public CEncryptData
{
public:
	CEncryptDouble( double Val = 0.0f , LONG nOffset = -1 );
	virtual ~CEncryptDouble(void);

public:
	//CEncryptDouble = CEncryptFLOAT
	inline double operator = ( const CEncryptFLOAT& r ) 
	{
		double val = r;
		*this = val;
		return val;
	}

	//CEncryptDouble += double
	inline double operator += ( double val )
	{
		double temp = *this + val;
		*this = temp;
		return temp;
	}

	//CEncryptDouble -= double
	inline double operator -= ( double val )
	{
		double temp = *this - val;
		*this = temp;
		return temp;
	}

	//CEncryptDouble = double
	inline double operator = ( double val )
	{
 		CEncrypt::Encrypt( &m_Value , &val , sizeof( double ) , m_nOffset );
		return val;
	}

	//FLOAT = CEncryptDouble
	inline operator double() const
	{
		double temp;
		CEncrypt::Encrypt( &temp , &m_Value , sizeof( double ) , m_nOffset );
		return temp;
	}
protected:

	double m_Value;
 
private:

};