#include "UpgradeElementMediator.h"
#include <MainEngine.h>

namespace MagicIdle 
{
	UpgradeElementMediator::~UpgradeElementMediator()
	{
		delete _model;
	}
	
	void UpgradeElementMediator::Init()
	{
		_view = Engine::Get()->Scene()->Create<UpgradeElementView>();
		_model = new UpgradeElementModel();
	}

	void UpgradeElementMediator::Update()
	{
		bool available = _model->IsAvailable(*_currency);
		_view->SetAvailability(available);

		if (_view->Pressed() && available)
		{
			_currency->Subtract(_model->GetCost());
			_valueToUpgrade->Add(_model->GetUpgrade());
			Upgrade();
		}
	}
	
	void UpgradeElementMediator::SetCurrencyPtr(KmbNumber* currency)
	{
		_currency = currency;
	}

	void UpgradeElementMediator::SetValueToUpgradePtr(KmbNumber* value)
	{
		_valueToUpgrade = value;
	}

	void UpgradeElementMediator::Upgrade()
	{
		_model->LevelUp();

		std::wstring cost = _model->GetCost().ToString();
		std::wstring upgrade = _model->GetUpgrade().ToString();

		_view->SetValues(_model->GetLevel(), cost, upgrade);
	}

	void UpgradeElementMediator::SetValues(
		std::wstring& name,
		Formula& costFormula,
		Formula& upgradeFormula
	)
	{
		_model->SetValues(name, costFormula, upgradeFormula);

		std::wstring cost = _model->GetCost().ToString();
		std::wstring upgrade = _model->GetUpgrade().ToString();
		
		_view->SetName(name);
		_view->SetValues(_model->GetLevel(), cost, upgrade);
	}
	
	UpgradeElementView* UpgradeElementMediator::GetView()
	{
		return _view;
	}
}