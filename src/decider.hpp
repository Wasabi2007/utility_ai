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
		std::vector<std::shared_ptr<action>> actions;
	public:
		decider();
		std::shared_ptr<action> chose(const actor& actor1);
		template <typename T,typename ... ARGS>
		decider& add_action(ARGS&&... args){
			auto act = std::make_shared<T>(args...);
			actions.push_back(act);
			return *this;
		};

		virtual bool execute(actor &a) override;
		std::shared_ptr<action> action_at(size_t index) const ;
		size_t action_size();

		void add_action(std::shared_ptr<action> act){
			actions.push_back(act);
		};
	};
}



