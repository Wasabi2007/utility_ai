//
// Created by jerry on 14.09.16.
//

#include <assert.h>
#include "decider.hpp"
#include "action.hpp"
#include "scorer.hpp"

namespace utility_ai{
	std::shared_ptr<utility_ai::action> decider::chose(const utility_ai::actor &actor1) {
		int max_score = actions.at(0)->score(actor1);
		auto current_action = actions.at(0);

		for(auto& action1 : actions){
			int score = action1->score(actor1);
			if(score > max_score){
				max_score = score;
				current_action = action1;
			}
		}

		return current_action;
	}

	decider::decider(std::unique_ptr<action>&& start_action) {
		assert(start_action);
		actions.emplace_back(std::move(start_action));
	}
}