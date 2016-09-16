//
// Created by jerry on 14.09.16.
//

#include <assert.h>
#include <algorithm>
#include "decider.hpp"

namespace utility_ai{
	std::shared_ptr<utility_ai::action> decider::chose(const utility_ai::actor &actor1) {
		if(actions.size() <= 0)
			return nullptr;

		auto max_elem = std::max_element (actions.begin(),actions.end(),[&actor1](auto& action1,auto& action2){
			return action1->score(actor1)<action2->score(actor1);
		});
		return *max_elem;
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