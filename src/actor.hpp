//
// Created by jerry on 14.09.16.
//

#pragma once

#include "decider.hpp"
#include <unordered_map>

namespace utility_ai {
	struct action_data;
	class actor {
	private:
		std::vector<std::shared_ptr<decider>> decider_;
		std::vector<std::shared_ptr<action>> decider_action_;
		std::unique_ptr<action_data> action_data_;
	public:
		actor();
		action_data& get_action_data() const;
		void set_action_data(std::unique_ptr<action_data>&& data);

		std::shared_ptr<decider> at(size_t index);
		size_t size();
		actor& add_decider(std::shared_ptr<decider>& d);

		virtual void update();
	};
}



