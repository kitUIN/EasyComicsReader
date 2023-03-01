#pragma once
#include "Episode.h"

class Comic :public INavigation
{
public:
	Comic(winrt::Windows::Data::Json::JsonObject const& json, winrt::hstring const& path);
	winrt::hstring Author();
	void Author(winrt::hstring const& value);
	winrt::hstring Path();
	void Path(winrt::hstring const& value);
	winrt::hstring ChineseTeam();
	void ChineseTeam(winrt::hstring const& value);
	winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Thumb();
	void Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
	winrt::hstring ThumbPath();
	void ThumbPath(winrt::hstring const& value);
	std::vector<Episode> m_episodes;
	winrt::Windows::Data::Json::JsonObject Json();
private:
	winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_img = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{L"https://files.catbox.moe/lx8fu2.png"} };
	winrt::hstring m_auther = L"";
	winrt::hstring m_chineseTeam = L"";
	winrt::hstring m_path = L"";
	winrt::hstring m_thumbPath = L"";
};
