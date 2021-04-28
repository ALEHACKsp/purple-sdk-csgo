#pragma once
#include "../../../dependencies/imgui/imgui.h"
#include "../variables.hpp"
#include <iostream>
#include "../../../dependencies/skCrypter.h"

namespace ImGuiCtx {
	void draw_line(const char* label, ImVec2 size, ImVec2 pos, ImVec4 color);
	ImVec4 rgba_to_imvec4(float r, float g, float b, float a);
	void BeginGroup(const char* label, ImVec2 size, ImVec2 pos);
	void EndGroup(const char* label, ImVec2 pos);
}