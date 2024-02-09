#pragma once

#include "resource.h"
#include <iostream>

class AddServers {
public:
	static void SaveButtonClicked(HWND hWnd);
	static bool AddServerToList(const std::wstring&, HWND);
	static int GetNumberOfServers(const std::wstring&);
	static bool IsEmpty(const WCHAR* str) {
		return str[0] == L'\0';
	}
};