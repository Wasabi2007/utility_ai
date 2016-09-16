//
// Created by jerry on 14.09.16.
//

#pragma once

#include <vector>
#include <memory>
#include "scorer.hpp"

namespace utility_ai{
	class actor;
	class action : public scorer{
	private:
		std::vector<std::unique_ptr<scorer>> scorers;
	public:
		virtual int score(const actor& a) const override;
		virtual bool execute(actor& a) = 0;
		template <typename T,typename ... ARGS>
		action& add_scorer(ARGS&&... args){
			scorers.push_back(std::make_unique<T>(args...));
			return *this;
		};

		const scorer& at(size_t index) const ;
		size_t size();
	};
}