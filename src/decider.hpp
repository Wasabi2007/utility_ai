//
// Created by jerry on 14.09.16.
//

#pragma once

#include <vector>
#include <memory>

namespace utility_ai {
	class action;
	class actor;
	class decider {
	private:
		std::vector<std::shared_ptr<action>> actions;
	public:
		decider(std::unique_ptr<action>&& start_action);
		std::shared_ptr<action> chose(const actor& actor1);
		template <typename T,typename ... ARGS>
		std::shared_ptr<T> add_action(ARGS&&... args){
			auto act = std::make_shared<T>(args...);
			actions.push_back(act);
			return act;
		};

		void add_action(std::shared_ptr<action> act){
			actions.push_back(act);
		};
	};
}



