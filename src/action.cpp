//
// Created by jerry on 14.09.16.
//
#include "action.hpp"
#include "scorer.hpp"
namespace utility_ai{
	int action::score(const actor &a) const {
		int result = 0;
		for(auto& s : scorers){
			result += s->score(a);
		}
		return result;
	}
}