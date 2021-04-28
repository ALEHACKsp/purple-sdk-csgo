#include "../features.hpp"
#include "../../../dependencies/skCrypter.h"

void features::misc::bunny_hop(c_usercmd* cmd) {
	if (!vars::misc::bunnyhop)
		return;

	static const auto move_type = csgo::local_player->move_type();

	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;

	static auto LastJumped = false;
	static auto ShouldFake = false;

	const auto flags = csgo::local_player->flags();

	if (!LastJumped && ShouldFake) {
		ShouldFake = false;
		cmd->buttons |= in_jump;
	}
	else if (cmd->buttons & in_jump) {

		if (vars::misc::airduck) {
			cmd->buttons |= in_duck;
		}

		if (flags & fl_onground) {
			LastJumped = true;
			ShouldFake = true;
		}
		else {
			cmd->buttons &= ~in_jump;
			LastJumped = false;
		}
	}
	else {
		LastJumped = false;
		ShouldFake = false;
	}
};

void features::misc::strafe(c_usercmd* cmd) {
	if (!vars::misc::autostrafe)
		return;

	static const auto move_type = csgo::local_player->move_type();
	if (move_type == movetype_ladder || move_type == movetype_noclip || move_type == movetype_observer)
		return;

	if (cmd->buttons & in_jump)
	{
		if (cmd->mousedx > 0)
			cmd->sidemove = 450.0f; // strafe right

		if (cmd->mousedy < 0)
			cmd->sidemove = -450.0f; // strafe left
	}
}

void features::misc::rank_reveal(c_usercmd* cmd) {
	if (!vars::misc::rank_reveal) return;

	if (cmd->buttons & in_score)
		interfaces::client->dispatch_user_message(cstrike15_user_message_t::cs_um_serverrankrevealall, NULL, NULL, nullptr);
}

void features::misc::radar() {
	if (!vars::misc::radar) return;
	if (!interfaces::engine->is_in_game()) return;

	for (auto i = 1; i < interfaces::globals->max_clients; i++)
	{
		auto entity = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));

		if (!entity || !entity->is_alive() || entity->dormant()) continue;
		if (entity->team() == csgo::local_player->team()) continue;

		entity->spotted() = true;
	}
}

void features::misc::fakeduck(c_usercmd* cmd) {
	if (!vars::misc::fakeduck)
		return;

	if (!(csgo::local_player->flags() & fl_onground))
		return;

	//Globals::bSendPacket = g_pClientState->iChokedCommands >= 15;

	int ForcedButtons;

	if (interfaces::clientstate->choked_commands <= 7)
		ForcedButtons = cmd->buttons & ~in_duck;
	else
		ForcedButtons = cmd->buttons | in_duck;

	cmd->buttons = ForcedButtons;
}

void features::misc::clantag() {
	static auto pSetClanTag = (int(__fastcall*)(const char*, const char*))utilities::pattern_scan("engine.dll", "53 56 57 8B DA 8B F9 FF 15 ? ? ? ?");

	if (!vars::misc::clantag)
		pSetClanTag(skCrypt(""), skCrypt(""));

	pSetClanTag(skCrypt("purple-sdk"), skCrypt("purple-sdk"));
}