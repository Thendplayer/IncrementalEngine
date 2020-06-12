#pragma once

#include<Actor.h>

#include "DisplayPanelModel.h"
#include "DisplayPanelView.h"

using namespace IncrementalEngine;

namespace MagicIdle 
{
	class DisplayPanelMediator : public Actor
	{
	public:
		virtual ~DisplayPanelMediator() override;

		virtual void Init() override;
		virtual void Update(float dt) override;

		DisplayPanelModel* GetModel();
		void SetTotalEarnedPtr(KmbNumber* totalEarnedPtr);

	private:
		DisplayPanelModel* _model;
		DisplayPanelView* _view;

		KmbNumber* _totalEarnedPtr;
	};
}
