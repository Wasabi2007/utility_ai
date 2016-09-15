//
// Created by jerry on 14.09.16.
//

#pragma once

#include <vector>
#include <memory>

namespace utility_ai{
	class actor;
	class scorer;
	class action{
	private:
		std::vector<std::unique_ptr<scorer>> scorers;
	public:
		int score(const actor& a) const ;
		virtual bool execute(actor& a) = 0;
		virtual bool start(actor& a) = 0;
		template <typename T,typename ... ARGS>
		void add_scorer(ARGS&&... args){
			scorers.push_back(std::make_unique<T>(std::forward(args)...));
		};
	};
}