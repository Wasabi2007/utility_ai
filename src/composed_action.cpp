//
// Created by jerry on 16.09.16.
//

#include "composed_action.hpp"

namespace utility_ai {
	bool composed_action::execute(utility_ai::actor &a) {
		bool result = true;
		for(auto& act : actions){
			result &= act->execute(a);
		}
		return result;
	}

	const action &composed_action::action_at(size_t index) const {
		return *actions.at(index);
	}

	size_t composed_action::action_size() {
		return actions.size();
	}
}