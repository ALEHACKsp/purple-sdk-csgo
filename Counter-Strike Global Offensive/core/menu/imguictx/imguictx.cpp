#include "imguictx.h"

void ImGuiCtx::draw_line(const char* label, ImVec2 size, ImVec2 pos, ImVec4 color)
{
	ImGui::SetCursorPos(pos);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, color);
	ImGui::BeginChild(label, size); ImGui::EndChild();
	ImGui::PopStyleColor();
}

ImVec4 ImGuiCtx::rgba_to_imvec4(float r, float g, float b, float a)
{
	return ImVec4(r / 255, g / 255, b / 255, a / 255);
}

void ImGuiCtx::BeginGroup(const char* label, ImVec2 size, ImVec2 pos)
{
	// Draw Outline
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyle().Colors[ImGuiCol_Border]);
	ImGui::SetCursorPos(pos);
	const char* hash = skCrypt("##border-");
	std::string buffer = hash;
	buffer += label;
	ImGui::BeginChild(buffer.c_str(), size); ImGui::EndChild();
	ImGui::PopStyleColor();

	// Draw Main box
	const char* hash2 = skCrypt("##");
	std::string buffer2 = hash2;
	buffer2 += label;
	ImGui::SetCursorPos(ImVec2(pos.x + 1, pos.y + 1));
	ImGui::BeginChild(buffer2.c_str(), ImVec2(size.x - 2, size.y - 2));
	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::BeginGroup();
}

void ImGuiCtx::EndGroup(const char* label, ImVec2 pos)
{
	ImGui::EndGroup();
	ImGui::EndChild();

	// Text
	ImGui::SetCursorPos(ImVec2(pos.x + 15, pos.y - 5));
	ImGui::Text(label);
}