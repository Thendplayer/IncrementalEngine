#pragma once

#include <Actor.h>
#include "DisplayPanelModel.h"
#include "ActionButtonView.h"
#include "ActionButtonModel.h"

using namespace IncrementalEngine;

namespace MagicIdle
{
	class ActionButtonMediator : public Actor
	{
	public:
		virtual ~ActionButtonMediator() override;

		virtual void Init() override;
		virtual void Update(float dt) override;

		void SetDisplayPanelModel(DisplayPanelModel* displayPanelModel);
		KmbNumber* GetTapValue();

		ActionButtonModel* GetModel();
		void SetCurrencyPtrs(KmbNumber* currencyPtr, KmbNumber* totalEarnedPtr);

	private:
		ActionButtonModel* _model;
		ActionButtonView* _view;
		DisplayPanelModel* _displayPanelModel;

		KmbNumber* _totalEarnedPtr;
		KmbNumber* _currencyPtr;
	};
}