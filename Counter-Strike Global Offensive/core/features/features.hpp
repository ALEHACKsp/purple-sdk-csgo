#pragma once
#include "../../dependencies/utilities/csgo.hpp"
#include "../menu/variables.hpp"

namespace features {
	namespace legitbot {
		player_t* GetBestTarget(c_usercmd* cmd);
		void aimbot(c_usercmd* cmd);
		inline int hitbox_id;
	}

	namespace esp {
		void run();
		void box(player_t* entity);
		void health();
		void armor();
		void name();
		void bone();
	}

	namespace visuals {
		void glow();
	}

	namespace misc {
		void bunny_hop(c_usercmd* cmd);
		void strafe(c_usercmd* cmd);
		void fakeduck(c_usercmd* cmd);
		void clantag();

		void rank_reveal(c_usercmd* cmd);
		void radar();
	}
}