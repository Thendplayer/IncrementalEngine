#include "ProfileMediator.h"

#include <MainEngine.h>

namespace MagicIdle 
{
	ProfileMediator::~ProfileMediator()
	{
		CHECKED_DELETE(_model);
	}
	
	void ProfileMediator::Init()
	{
		_view = Engine::Get()->Scene()->Create<ProfileView>(this);
		_model = new ProfileModel();
	}
	
	void ProfileMediator::Update(float dt)
	{
		_view->SetValues(
			_model->GetTotalEarned()->ToString(), 
			_model->GetTotalSpent()->ToString(),
			_model->GetTotalTaps()->ToString()
		);
	}
	
	ProfileModel* ProfileMediator::GetModel()
	{
		return _model;
	}
}