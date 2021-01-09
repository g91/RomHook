/******************************************************************************
* Name: LuaWrapper for C++
*
* Author: Yong Lin
* Date: 2004-07-19 17:15
* E-Mail: ly4cn@21cn.com
*
* Copyright (C) 2004 Yong Lin.  All rights reserved.
* HomePage︰第二人生 http://www.d2-life.com
*      http://www.d2-life.com/LBS/blogview.asp?logID=41
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
//#pragma comment(lib, "laux.lib")
//#pragma comment(lib, "lua.lib")

#ifdef __cplusplus
};
#endif