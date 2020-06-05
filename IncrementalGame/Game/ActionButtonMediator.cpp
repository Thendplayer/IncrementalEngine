#include "ActionButtonMediator.h"
#include <MainEngine.h>

namespace MagicIdle
{
	ActionButtonMediator::~ActionButtonMediator()
	{
		delete _model;
	}
	
	void ActionButtonMediator::Init()
	{
		_view = Engine::Get()->Scene()->Create<ActionButtonView>();
		_view->SetPosition(355, -7);

		_model = new ActionButtonModel();
	}
	
	void ActionButtonMediator::Update(float dt)
	{
		if (_view->Pressed()) 
		{
			auto tapValue = _model->Tap();
			_displayPanelModel->AddCurrency(tapValue);
		}
	}
	
	void ActionButtonMediator::SetDisplayPanelModel(DisplayPanelModel* displayPanelModel)
	{
		_displayPanelModel = displayPanelModel;
	}
	
	KmbNumber* ActionButtonMediator::GetTapValue()
	{
		return _model->GetTapValue();
	}
}