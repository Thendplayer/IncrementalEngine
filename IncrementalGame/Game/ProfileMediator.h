#pragma once

#include <Actor.h>
#include "ProfileView.h"
#include "ProfileModel.h"

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class ProfileMediator : public Actor
	{
	public:
		virtual ~ProfileMediator();

		virtual void Init() override;
		virtual void Update(float dt) override;

		ProfileModel* GetModel();

	private:
		ProfileView* _view;
		ProfileModel* _model;
	};
}