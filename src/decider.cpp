//
// Created by jerry on 14.09.16.
//

#include <assert.h>
#include "decider.hpp"

namespace utility_ai{
	std::shared_ptr<utility_ai::action> decider::chose(const utility_ai::actor &actor1) {
		if(actions.size() <= 0)
			return nullptr;

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

	decider::decider() {
	}

	bool decider::execute(actor &a) {
		auto act = chose(a);
		return act->execute(a);
	}

	std::shared_ptr<action> decider::action_at(size_t index) const {
		return actions.at(index);
	}

	size_t decider::action_size() {
		return actions.size();
	}
}