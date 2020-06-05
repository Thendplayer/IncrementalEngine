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
		auto currencyPerSecond = *_model->GetCurrencyPerSecond();

		auto currencyPerSecondString = currencyPerSecond.ToString();
		auto currencyString = _model->GetCurrency()->ToString();

		_view->SetCurrency(currencyString);
		_view->SetCurrencyPerSecond(currencyPerSecondString);
	}
	
	DisplayPanelModel* DisplayPanelMediator::GetModel()
	{
		return _model;
	}
}