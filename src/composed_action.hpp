//
// Created by jerry on 16.09.16.
//

#pragma once

#include "action.hpp"

namespace utility_ai {
	class composed_action : public action{
	private:
		std::vector<std::shared_ptr<action>> actions;
	public:
		virtual bool execute(actor &a) override;
		template <typename T,typename ... ARGS>
		composed_action& add_action(ARGS&&... args){
			auto act = std::make_shared<T>(args...);
			actions.push_back(act);
			return *this;
		};

		const action &action_at(size_t index) const;

		size_t action_size();
	};
}



