#include "../features.hpp"
#include "box.h"

bool get_playerbox(player_t* ent, _box& in)
{
	vec3_t flb, brt, blb, frt, frb, brb, blt, flt;

	const auto origin = ent->abs_origin();
	const auto min = ent->collideable()->mins() + origin;
	const auto max = ent->collideable()->maxs() + origin;

	vec3_t points[] = {
		vec3_t(min.x, min.y, min.z),
		vec3_t(min.x, max.y, min.z),
		vec3_t(max.x, max.y, min.z),
		vec3_t(max.x, min.y, min.z),
		vec3_t(max.x, max.y, max.z),
		vec3_t(min.x, max.y, max.z),
		vec3_t(min.x, min.y, max.z),
		vec3_t(max.x, min.y, max.z)
	};

	if (!interfaces::debug_overlay->world_to_screen(points[3], flb) || !interfaces::debug_overlay->world_to_screen(points[5], brt)
		|| !interfaces::debug_overlay->world_to_screen(points[0], blb) || !interfaces::debug_overlay->world_to_screen(points[4], frt)
		|| !interfaces::debug_overlay->world_to_screen(points[2], frb) || !interfaces::debug_overlay->world_to_screen(points[1], brb)
		|| !interfaces::debug_overlay->world_to_screen(points[6], blt) || !interfaces::debug_overlay->world_to_screen(points[7], flt))
		return false;

	vec3_t arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 1; i < 8; ++i)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	in.x = static_cast<int>(left);
	in.y = static_cast<int>(top);
	in.w = static_cast<int>(right - left);
	in.h = static_cast<int>(bottom - top);

	return true;
}

const color history{ 255, 255, 255,50 };
const color history_outline{ 0,0,0,60 };

void features::esp::run()
{
	for (int i = 1; i <= interfaces::globals->max_clients; ++i)
	{
		auto* const entity = static_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity || !csgo::local_player || entity == csgo::local_player || entity->health() <= 0) continue;
		if (!vars::esp::box_team && entity->team() == csgo::local_player->team()) continue;
		box(entity);
	}
}

void features::esp::box(player_t* entity)
{
	_box bbox;

	if (!vars::esp::box_enemy || !get_playerbox(entity, bbox)) return;

	render::draw_rect(bbox.x, bbox.y, bbox.w, bbox.h, entity->dormant() ? history : color(255, 255, 255));
	render::draw_rect(bbox.x + 1, bbox.y + 1, bbox.w - 2, bbox.h - 2, entity->dormant() ? history_outline : color(0, 0, 0));
	render::draw_rect(bbox.x - 1, bbox.y - 1, bbox.w + 2, bbox.h + 2, entity->dormant() ? history_outline : color(0, 0, 0));
}

void features::esp::health()
{
	if (!vars::esp::health_enemy)
		return;
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;
	if (!csgo::local_player)
		return;

	for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
	{
		auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
		if (!pCSPlayer)
			continue;
		if (pCSPlayer == csgo::local_player)
			continue;
		if (pCSPlayer->dormant())
			continue;
		if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
			continue;

		vec3_t vecFoot, vecScreen, vecHeadScreen;
		vecFoot = pCSPlayer->origin();
		if (!(math::world_to_screen(vecFoot, vecScreen)))
			continue;

		vecFoot.z += 72.f;
		if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
			continue;

		auto health = pCSPlayer->health();
		int h = vecScreen.y - vecHeadScreen.y;
		//render::draw_text_string(10, 20, render::fonts::watermark_font, std::to_string(h), true, color::red());
		int healthheight = (h * health) / 100;
		int w = 4;
		int y = vecHeadScreen.y;
		int x = vecHeadScreen.x - (h / 4 + 5);
		if (pCSPlayer->team() == csgo::local_player->team() && vars::esp::health_team)
		{
			render::draw_rect(x, y, w, h, color::black());
			render::draw_filled_rect(x + 1, y + 1, w - 1, healthheight - 2, color::green());
		}
		else if (pCSPlayer->team() != csgo::local_player->team())
		{
			render::draw_rect(x, y, w, h, color::black());
			render::draw_filled_rect(x + 1, y + 1, w - 1, healthheight - 2, color::green());
		}
	}
}

void features::esp::armor()
{
	if (!vars::esp::armor_enemy)
		return;
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;
	if (!csgo::local_player)
		return;

	for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
	{
		auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
		if (!pCSPlayer)
			continue;
		if (pCSPlayer == csgo::local_player)
			continue;
		if (pCSPlayer->dormant())
			continue;
		if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
			continue;

		vec3_t vecFoot, vecScreen, vecHeadScreen;
		vecFoot = pCSPlayer->origin();
		if (!(math::world_to_screen(vecFoot, vecScreen)))
			continue;

		vecFoot.z += 72.f;
		if (!(math::world_to_screen(vecFoot, vecHeadScreen)))
			continue;

		auto armor = pCSPlayer->armor();
		int h = vecScreen.y - vecHeadScreen.y;
		int healthheight = (h * armor) / 100;
		int w = 4;
		int y = vecHeadScreen.y;
		int x = vecHeadScreen.x + (h / 4);
		if (pCSPlayer->team() == csgo::local_player->team() && vars::esp::armor_team)
		{
			render::draw_rect(x, y, w, h, color::black());
			render::draw_filled_rect(x + 1, y + 1, w - 1, healthheight - 2, color::blue());
		}
		else if (pCSPlayer->team() != csgo::local_player->team())
		{
			render::draw_rect(x, y, w, h, color::black());
			render::draw_filled_rect(x + 1, y + 1, w - 1, healthheight - 2, color::blue());
		}
	}
}

void features::esp::bone()
{
	if (!vars::esp::bone_enemy)
		return;
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;
	if (!csgo::local_player)
		return;

	for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
	{
		auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
		if (!pCSPlayer)
			continue;
		if (pCSPlayer == csgo::local_player)
			continue;
		if (pCSPlayer->dormant())
			continue;
		if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
			continue;

		auto pStudioModel = interfaces::model_info->get_studio_model(pCSPlayer->model());
		if (!pStudioModel)
			return;

		static matrix_t pBoneToWorldOut[128];
		if (pCSPlayer->setup_bones(pBoneToWorldOut, 128, 256, 0))
		{
			for (int i = 0; i < pStudioModel->bones_count; i++)
			{
				studio_bone_t* pBone = pStudioModel->bone(i);
				if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
					continue;

				vec3_t vBonePos1;
				if (!math::world_to_screen(vec3_t(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
					continue;

				vec3_t vBonePos2;
				if (!math::world_to_screen(vec3_t(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
					continue;
				if (pCSPlayer->team() == csgo::local_player->team() && vars::esp::bone_team)
				{
					render::draw_line(vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, color::white());
				}
				else if (pCSPlayer->team() != csgo::local_player->team())
				{
					render::draw_line(vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, color::white());
				}
			}
		}
	}
}

void features::esp::name()
{
	if (!vars::esp::name_enemy)
		return;
	if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
		return;
	if (!csgo::local_player)
		return;

	for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
	{
		auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
		if (!pCSPlayer)
			continue;
		if (pCSPlayer == csgo::local_player)
			continue;
		if (pCSPlayer->dormant())
			continue;
		if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
			continue;

		vec3_t vecHead, vecHeadScreen;
		vecHead = pCSPlayer->get_bone_position(8);
		vecHead.z += 20.f;
		if (!(math::world_to_screen(vecHead, vecHeadScreen)))
			continue;

		player_info_t playerinfo;
		interfaces::engine->get_player_info(iPlayer, &playerinfo);

		if (pCSPlayer->team() == csgo::local_player->team() && vars::esp::name_team)
		{
			render::text(vecHeadScreen.x, vecHeadScreen.y, render::fonts::watermark_font, playerinfo.name, true, color::blue());
		}
		else if (pCSPlayer->team() != csgo::local_player->team())
		{
			render::text(vecHeadScreen.x, vecHeadScreen.y, render::fonts::watermark_font, playerinfo.name, true, color::red());
		}
	}
}