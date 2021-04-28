#pragma once

namespace vars {
	namespace ragebot {
		inline bool enabled = false;
	}

	namespace legitbot {
		inline bool enabled = false;
		inline bool drawfov = false;
		inline float fov = 0.f;
		inline float smooth = 0.1f;
		inline int bone;
		inline bool visiblecheck = true;
	}

	namespace esp {
		// enemy
		inline bool box_enemy = false;
		inline bool health_enemy = false;
		inline bool armor_enemy = false;
		inline bool name_enemy = false;
		inline bool bone_enemy = false;

		// team
		inline bool box_team = false;
		inline bool health_team = false;
		inline bool armor_team = false;
		inline bool name_team = false;
		inline bool bone_team = false;
	}

	namespace visuals {
		inline bool glow_enemy = false;
		inline bool glow_team = false;
		inline bool glow_bomb = false;
		inline float glow_enemy_color[4] = { 1.f, 0.f, 0.f, 1.f };
		inline float glow_team_color[4] = { 0.f, 0.f, 1.f, 1.f };
		inline float glow_bomb_color[4] = { 1.f, 0.5f, 0.f, 1.f };
	}

	namespace misc {
		inline bool bunnyhop = false;
		inline bool airduck = false;
		inline bool autostrafe = false;
		inline bool fakeduck = false;
		inline bool clantag = false;

		inline bool rank_reveal = false;
		inline bool radar = false;
	}
}