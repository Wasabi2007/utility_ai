//
// Created by jerry on 14.09.16.
//

#pragma once

#include "decider.hpp"

namespace utility_ai {
	struct action_data;
	class actor {
	private:
		std::shared_ptr<decider> decider_;
		std::shared_ptr<action> current_action_;
		std::unique_ptr<action_data> action_data_;
	public:
		actor(std::shared_ptr<decider> actor_ai);
		action_data& get_action_data() const;
		void set_action_data(std::unique_ptr<action_data>&& data);

		virtual void update();
	};
}



