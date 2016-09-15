//
// Created by jerry on 14.09.16.
//

#include <assert.h>
#include "actor.hpp"
#include "action.hpp"
#include "action_data.hpp"

namespace utility_ai {
	actor::actor(std::shared_ptr<utility_ai::decider> actor_ai):decider_(actor_ai) {
		assert(actor_ai);
	}

	void actor::update() {
		auto action_ = decider_->chose(*this);
		if(action_ != current_action_){
			current_action_ = action_;
			action_->start(*this);
		}
		action_ ->execute(*this);
	}

	action_data &actor::get_action_data() const {
		return *action_data_.get();
	}
}
