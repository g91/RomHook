#pragma once

enum DumpTypeENUM
{
	EM_DumpType_MID		,
	EM_DumpType_MAX		,
};

bool	CreateDump( const wchar_t* fileName , DumpTypeENUM type );