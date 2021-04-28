#include "../features.hpp"

int aim_bone[] = { 8, 7, 6 };

player_t* features::legitbot::GetBestTarget(c_usercmd* cmd)
{
    float ofov = vars::legitbot::fov;
    float nfov = 0;
    player_t* player = nullptr;

    for (int iPlayer = 0; iPlayer < interfaces::globals->max_clients; iPlayer++)
    {
        auto pCSPlayer = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(iPlayer));
        if (!pCSPlayer)
            continue;
        if (pCSPlayer == csgo::local_player || pCSPlayer->team() == csgo::local_player->team())
            continue;
        if (pCSPlayer->dormant())
            continue;
        if (!(pCSPlayer->is_alive() && pCSPlayer->health() > 0))
            continue;
        if (pCSPlayer->has_gun_game_immunity())
            continue;
        vec3_t eyepos = csgo::local_player->get_eye_pos();
        vec3_t enemyheadpos = pCSPlayer->get_bone_position(8);
        vec3_t angleTo = math::calculate_angle(eyepos, enemyheadpos);
        angleTo.clamp();
        nfov = cmd->viewangles.distance_to(angleTo);

        if (nfov < ofov)
        {
            ofov = nfov;
            player = pCSPlayer;
        }
    }
    return player;
}

void features::legitbot::aimbot(c_usercmd* cmd)
{
    if (!vars::legitbot::enabled)
        return;
    if (!interfaces::engine->is_connected() || !interfaces::engine->is_in_game())
        return;
    if (!csgo::local_player)
        return;
    if (!csgo::local_player->is_alive())
        return;

    const auto weapon_type = csgo::local_player->active_weapon()->get_weapon_data()->weapon_type;

    if (weapon_type == WEAPONTYPE_GRENADE || weapon_type == WEAPONTYPE_C4 || weapon_type == WEAPONTYPE_KNIFE)
        return;

    player_t* target = GetBestTarget(cmd);
    auto weapon = csgo::local_player->active_weapon();
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        if (target)
        {
            //   int bone = 0;
            //   bone = aim_bone[variables::bone];
            vec3_t eyepos = csgo::local_player->get_eye_pos();
            vec3_t targethead = target->get_bone_position(8);
            //  vec3_t targetbone = target->get_bone_position(bone);
            vec3_t viewangles = math::calculate_angle(eyepos, targethead);
            viewangles.clamp();
            vec3_t delta = cmd->viewangles - viewangles;
            delta.clamp();

            vec3_t finalAng = cmd->viewangles - delta / (vars::legitbot::smooth * 20);
            finalAng.clamp();

            if (vars::legitbot::visiblecheck && csgo::local_player->can_see_player_pos(target, target->get_eye_pos()))
            {
                cmd->viewangles = finalAng;
                interfaces::engine->set_view_angles(cmd->viewangles);
            }
            else if (!vars::legitbot::visiblecheck)
            {
                cmd->viewangles = finalAng;
                interfaces::engine->set_view_angles(cmd->viewangles);
            }
        }
    }
}