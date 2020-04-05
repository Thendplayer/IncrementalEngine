#ifndef _ACTOR_H
#define _ACTOR_H

#include<vector>

using namespace std;

namespace MyEngine
{
	class Actor
	{
	public:
		Actor();
		~Actor();

	private:
		Actor* _parent;
		vector<Actor*> _children;
	};
}

#endif