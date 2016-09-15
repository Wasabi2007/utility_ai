//
// Created by jerry on 14.09.16.
//

#pragma once
namespace utility_ai{
	class actor;
	class scorer{
	public:
		virtual int score(const actor& a) const = 0;
	};
}