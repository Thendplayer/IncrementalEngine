#include "ProfileView.h"

#include <MainEngine.h>

namespace MagicIdle 
{
	void ProfileView::Init()
	{
		Sprite::Init();
		SetTexture(Engine::Get()->Resources()->GetTexture("ProfileBackground"));

		_totalEarnedText = Engine::Get()->Scene()->Create<Text>(this);

		_totalEarnedText->SetFont(L"Edo SZ");
		_totalEarnedText->SetPosition(-47, -227);
		_totalEarnedText->SetTextColor(255, 255, 255);
		_totalEarnedText->SetFontSize(72);
		_totalEarnedText->SetFontAlignment(Text::CENTER_LEFT);
		_totalEarnedText->SetText(L"999.99W");

		_totalSpentText = Engine::Get()->Scene()->Create<Text>(this);

		_totalSpentText->SetFont(L"Edo SZ");
		_totalSpentText->SetPosition(-77, -67);
		_totalSpentText->SetTextColor(255, 255, 255);
		_totalSpentText->SetFontSize(72);
		_totalSpentText->SetFontAlignment(Text::CENTER_LEFT);
		_totalSpentText->SetText(L"999.99W");

		_totalTapsText = Engine::Get()->Scene()->Create<Text>(this);

		_totalTapsText->SetFont(L"Edo SZ");
		_totalTapsText->SetPosition(-117, 87);
		_totalTapsText->SetTextColor(255, 255, 255);
		_totalTapsText->SetFontSize(72);
		_totalTapsText->SetFontAlignment(Text::CENTER_LEFT);
		_totalTapsText->SetText(L"999.99W");

		_creditsButton = Engine::Get()->Scene()->Create<Button>(this);
		_creditsButton->SetTexture(Engine::Get()->Resources()->GetTexture("ProfileCreditsButton"));
		_creditsButton->SetPosition(-250, 350);

		_exitButton = Engine::Get()->Scene()->Create<Button>(this);
		_exitButton->SetTexture(Engine::Get()->Resources()->GetTexture("ProfileExitButton"));
		_exitButton->SetPosition(185, 350);

		_creditsSprite = Engine::Get()->Scene()->Create<Sprite>(this);
		_creditsSprite->SetTexture(Engine::Get()->Resources()->GetTexture("CreditsScreen"));
		_creditsSprite->SetPosition(0, 0);
		_creditsSprite->SetActive(false);

		_closeButton = Engine::Get()->Scene()->Create<Button>(this);
		_closeButton->SetTexture(Engine::Get()->Resources()->GetTexture("ProfileCrossButton"));
		_closeButton->SetPosition(535, -450);
	}
	
	void ProfileView::Update(float dt)
	{
		Sprite::Update(dt);

		if (_creditsButton->Pressed())
		{
			_creditsSprite->SetActive(true);
		}

		else if (_exitButton->Pressed())
		{
			Engine::Get()->Close();
		}

		else if (_closeButton->Pressed())
		{
			if (_creditsSprite->IsActive())
			{
				_creditsSprite->SetActive(false);
			}
			else 
			{
				GetParent()->SetActive(false);
			}
		}
	}
	
	void ProfileView::SetValues(
		std::wstring totalEarned, 
		std::wstring totalSpent, 
		std::wstring totalTaps
	)
	{
		_totalEarnedText->SetText(totalEarned);
		_totalSpentText->SetText(totalSpent);
		_totalTapsText->SetText(totalTaps);
	}
}