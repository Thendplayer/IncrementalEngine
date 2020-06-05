#include "DisplayPanelMediator.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	DisplayPanelMediator::~DisplayPanelMediator()
	{
		delete _model;
	}
	
	void DisplayPanelMediator::Init()
	{
		_view = Engine::Get()->Scene()->Create<DisplayPanelView>();
		_view->SetPosition(-332, -275);
		_view->SetScale(.66f, .66f);

		_model = new DisplayPanelModel();
	}
	
	void DisplayPanelMediator::Update()
	{
		auto currency = _model->GetCurrency()->ToString();
		auto currencyPerSecond = _model->GetCurrencyPerSecond()->ToString();

		_view->SetCurrency(currency);
		_view->SetCurrencyPerSecond(currencyPerSecond);
	}
	
	DisplayPanelModel* DisplayPanelMediator::GetModel()
	{
		return _model;
	}
}