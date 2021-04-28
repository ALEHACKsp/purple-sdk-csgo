#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../dependencies/utilities/config/config.h"
#include "../../dependencies/skCrypter.h"
#include "imguictx/imguictx.h"
#include "variables.hpp"
#include "fonts/verdana.h"

namespace menu {
	inline bool opened = false;
	inline bool initialized = false;
	inline HWND hwnd;
	inline WNDPROC original_wndproc;
	inline ImVec2 menu_size = ImVec2(750, 500);

	// Fonts
	inline ImFont* main_font;
	inline ImFont* tab_font;

	void tab(const char* label, ImVec2 size, int id);
	void render();
	void setup_style();

	bool initialize(IDirect3DDevice9* device);
	void release();

	LRESULT WINAPI wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
