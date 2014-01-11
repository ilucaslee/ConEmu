﻿
/*
Copyright (c) 2011-2014 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#define SHOWDEBUGSTR

#include "Header.h"

#define GUI_MACRO_VERSION 2

class CRealConsole;

struct GuiMacro;
struct GuiMacroArg;

enum GuiMacroArgType
{
	gmt_Int,
	gmt_Hex,
	gmt_Str,
	gmt_VStr,
	gmt_Fn, // Reserved
};

struct GuiMacroArg
{
	GuiMacroArgType Type;

	#ifdef _WIN64
	DWORD Pad;
	#endif

	union
	{
		int Int;
		LPWSTR Str;
		GuiMacro* Macro;
	};
};

struct GuiMacro
{
	size_t  cbSize;
	LPCWSTR szFunc;
	wchar_t chFuncTerm; // L'(', L':', L' ' - delimiter between func name and arguments

	size_t  argc;
	GuiMacroArg* argv; // No need to release mem, buffer allocated for the full GuiMacro data

	wchar_t* AsString();
	bool GetIntArg(size_t idx, int& val);
	bool GetStrArg(size_t idx, LPWSTR& val);
	bool IsIntArg(size_t idx);
	bool IsStrArg(size_t idx);
};


namespace ConEmuMacro
{
	// Общая функция, для обработки любого известного макроса
	LPWSTR ExecuteMacro(LPWSTR asMacro, CRealConsole* apRCon, bool abFromPlugin = false);
	// Конвертация из "старого" в "новый" формат
	LPWSTR ConvertMacro(LPCWSTR asMacro, BYTE FromVersion, bool bShowErrorTip = true);
};
