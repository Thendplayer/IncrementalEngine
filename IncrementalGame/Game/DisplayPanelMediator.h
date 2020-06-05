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
		virtual void Update() override;

		DisplayPanelModel* GetModel();

	private:
		DisplayPanelModel* _model;
		DisplayPanelView* _view;
	};
}
