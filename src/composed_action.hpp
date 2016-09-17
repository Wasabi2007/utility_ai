//
// Created by jerry on 16.09.16.
//

#pragma once

#include "action.hpp"

namespace utility_ai {
	class composed_action : public action{
	private:
		std::vector<std::unique_ptr<action>> actions;
	public:
		virtual bool execute(actor &a) override;
		void add_action(std::unique_ptr<action>&& act){
			actions.emplace_back(std::move(act));
		};

		const action* action_at(size_t index) const;

		size_t action_size();
	};
}



