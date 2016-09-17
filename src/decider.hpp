//
// Created by jerry on 14.09.16.
//

#pragma once

#include <vector>
#include <memory>
#include "action.hpp"

namespace utility_ai {
	class actor;
	class decider : public action{
	private:
		std::vector<std::unique_ptr<action>> actions;
	public:
		decider();
		action* chose(const actor& actor1);

		void add_action(std::unique_ptr<action>&& act){
			actions.emplace_back(std::move(act));
		};

		virtual bool execute(actor &a) override;
		action* action_at(size_t index) const ;
		size_t action_size();
	};
}



