
// BigNumber.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CBigNumberApp:
// See BigNumber.cpp for the implementation of this class
//

class CBigNumberApp : public CWinApp
{
public:
	CBigNumberApp();

// Overrides
public:
	virtual BOOL InitInstance();
	
	void OnAppExit();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CBigNumberApp theApp;
