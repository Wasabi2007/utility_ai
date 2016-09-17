//
// Created by jerry on 14.09.16.
//

#include "actor.hpp"
#include "action_data.hpp"

namespace utility_ai {
	actor::actor() {
	}

	void actor::update() {
		for(size_t i = 0; i < decider_.size();i++) {
			if(decider_action_.at(i) == nullptr || decider_action_.at(i)->execute(*this)){
				decider_action_[i] = decider_.at(i)->chose(*this);
			}
		}
	}

	action_data &actor::get_action_data() const {
		return *action_data_.get();
	}

	void actor::set_action_data(std::unique_ptr<action_data>&& data) {
		action_data_ = std::move(data);
	}

	decider* actor::at(size_t index) {
		return decider_.at(index);
	}

	size_t actor::size() {
		return decider_.size();
	}

	void actor::add_decider(decider* d) {
		decider_.emplace_back(d);
		decider_action_.emplace_back(nullptr);
	}
}
