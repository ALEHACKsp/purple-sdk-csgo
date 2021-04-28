#include "menu.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static int active_profile = 0;

void menu::tab(const char* label, ImVec2 size, int id)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
	if (active_profile == id)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImGuiCtx::rgba_to_imvec4(218, 66, 245, 255));
		if (ImGui::Button(label, size))
			active_profile = id;
		ImGui::PopStyleColor();
	}
	else {
		if (ImGui::Button(label, size))
			active_profile = id;
	}
	ImGui::PopStyleVar();
}

void menu::render() {
	ImVec4 menucol = ImGuiCtx::rgba_to_imvec4(218, 66, 245, 255);

	setup_style();
	ImGui::SetNextWindowSize(menu_size);
	ImGui::Begin(skCrypt("purple-sdk"), nullptr, ImGuiWindowFlags_NoDecoration);
	{
		ImVec2 window_size = ImGui::GetWindowSize();

		ImGuiCtx::draw_line(skCrypt("##topline"), ImVec2(window_size.x, 1), ImVec2(0, 1), menucol);

		ImGui::SetCursorPos(ImVec2(0, 2));
		ImGui::BeginChild(skCrypt("##tabs"), ImVec2(window_size.x, 25));
		{
			int button_width = 100;

			ImGui::PushFont(tab_font);
			tab(skCrypt("Legitbot"), ImVec2(button_width, 25), 0);
			ImGui::SameLine();
			tab(skCrypt("ESP"), ImVec2(button_width, 25), 1);
			ImGui::SameLine();
			tab(skCrypt("Misc"), ImVec2(button_width, 25), 2);
			ImGui::PopFont();
		} ImGui::EndChild();

		if (active_profile == 0)
		{
			ImGuiCtx::BeginGroup(skCrypt("Aimbot"), ImVec2(200, 200), ImVec2(15, 27 + 15));
			{
				ImGui::Checkbox(skCrypt("Enabled"), &vars::legitbot::enabled);
				ImGui::SliderFloat(skCrypt("FOV"), &vars::legitbot::fov, 0.f, 10.f);
				ImGui::SliderFloat(skCrypt("Smooth"), &vars::legitbot::smooth, 0.1f, 5.f);
				ImGui::Checkbox(skCrypt("Visible only"), &vars::legitbot::visiblecheck);
			} ImGuiCtx::EndGroup(skCrypt("Aimbot"), ImVec2(15, 27 + 15));
		}
		if (active_profile == 1)
		{
			ImGuiCtx::BeginGroup(skCrypt("Enemy"), ImVec2(200, 200), ImVec2(15, 27 + 15));
			{
				ImGui::Checkbox(skCrypt("Box"), &vars::esp::box_enemy);
				ImGui::Checkbox(skCrypt("Health"), &vars::esp::health_enemy);
				ImGui::Checkbox(skCrypt("Armor"), &vars::esp::armor_enemy);
				ImGui::Checkbox(skCrypt("Bone"), &vars::esp::bone_enemy);
				ImGui::Checkbox(skCrypt("Name"), &vars::esp::name_enemy);
			} ImGuiCtx::EndGroup(skCrypt("Enemy"), ImVec2(15, 27 + 15));

			ImGuiCtx::BeginGroup(skCrypt("Team"), ImVec2(200, 200), ImVec2(230, 27 + 15));
			{
				ImGui::Checkbox(skCrypt("Box"), &vars::esp::box_team);
				ImGui::Checkbox(skCrypt("Health"), &vars::esp::health_team);
				ImGui::Checkbox(skCrypt("Armor"), &vars::esp::armor_team);
				ImGui::Checkbox(skCrypt("Bone"), &vars::esp::bone_team);
				ImGui::Checkbox(skCrypt("Name"), &vars::esp::name_team);
			} ImGuiCtx::EndGroup(skCrypt("Team"), ImVec2(230, 27 + 15));
		}
		if (active_profile == 2)
		{
			ImGuiCtx::BeginGroup(skCrypt("Misc"), ImVec2(200, 200), ImVec2(15, 27 + 15));
			{
				ImGui::Checkbox(skCrypt("Bunnyhop"), &vars::misc::bunnyhop);
				if (vars::misc::bunnyhop)
					ImGui::Checkbox(skCrypt("Air-duck"), &vars::misc::airduck);
				//ImGui::Checkbox(skCrypt("Auto-strafe"), &vars::misc::autostrafe);
				ImGui::Checkbox(skCrypt("Clantag"), &vars::misc::clantag);
				ImGui::Checkbox(skCrypt("Fake duck"), &vars::misc::fakeduck);
			} ImGuiCtx::EndGroup(skCrypt("Misc"), ImVec2(15, 27 + 15));
		}
	} ImGui::End();
}

void menu::setup_style() {
	ImGuiStyle* style = &ImGui::GetStyle();

	// Windows settings
	style->WindowRounding = 0;
	style->WindowBorderSize = 1;
	style->FrameBorderSize = 1;
	style->WindowPadding = { 0, 0 };

	// Window colors
	style->Colors[ImGuiCol_WindowBg] = ImGuiCtx::rgba_to_imvec4(23, 23, 23, 255);
	style->Colors[ImGuiCol_ChildBg] = ImGuiCtx::rgba_to_imvec4(31, 31, 31, 255);
	style->Colors[ImGuiCol_Border] = ImGuiCtx::rgba_to_imvec4(14, 14, 14, 255);
	style->Colors[ImGuiCol_FrameBg] = ImGuiCtx::rgba_to_imvec4(22, 22, 22, 255);
	style->Colors[ImGuiCol_FrameBgHovered] = ImGuiCtx::rgba_to_imvec4(25, 25, 25, 255);
	style->Colors[ImGuiCol_FrameBgActive] = ImGuiCtx::rgba_to_imvec4(25, 25, 25, 255);
	
	// Elements
	style->Colors[ImGuiCol_Text] = ImGuiCtx::rgba_to_imvec4(177, 177, 177, 255);
	style->Colors[ImGuiCol_CheckMark] = ImGuiCtx::rgba_to_imvec4(218, 66, 245, 255);
	style->Colors[ImGuiCol_Button] = ImGuiCtx::rgba_to_imvec4(31, 31, 31, 255);
	style->Colors[ImGuiCol_ButtonHovered] = ImGuiCtx::rgba_to_imvec4(39, 39, 39, 255);
	style->Colors[ImGuiCol_ButtonActive] = ImGuiCtx::rgba_to_imvec4(39, 39, 39, 255);
}

bool menu::initialize(IDirect3DDevice9* device) {
	hwnd = FindWindow("Valve001", "Counter-Strike: Global Offensive");
	original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	main_font = io.Fonts->AddFontFromMemoryCompressedTTF(verdana_compressed_data, verdana_compressed_size, 12.f);
	tab_font = io.Fonts->AddFontFromMemoryCompressedTTF(verdana_compressed_data, verdana_compressed_size, 13.5f);
	ImGui::StyleColorsClassic();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(device);

	initialized = true;
	return true;
}

void menu::release() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(original_wndproc));
}

LRESULT WINAPI menu::wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (opened && ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProc(original_wndproc, hWnd, msg, wParam, lParam);
}
