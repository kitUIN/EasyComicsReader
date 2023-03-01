#include "pch.h"
#include "Comic.h"


Comic::Comic(winrt::Windows::Data::Json::JsonObject const& json, winrt::hstring const& path): INavigation(json)
{
	if (json.HasKey(L"eps"))
	{
		for (auto ep : json.GetNamedArray(L"eps"))
		{
			m_episodes.push_back(Episode{ ep.GetObjectW() });
		}
	}
	if (json.HasKey(L"author")) Author(json.GetNamedString(L"author"));
	if (json.HasKey(L"chineseTeam")) ChineseTeam(json.GetNamedString(L"chineseTeam"));
	if (json.HasKey(L"thumb")) ThumbPath(json.GetNamedString(L"thumb"));
	Path(path);

}

winrt::hstring Comic::Author()
{
	return m_auther;
}

void Comic::Author(winrt::hstring const& value)
{
	m_auther = value;
}
winrt::hstring Comic::Path()
{
	return m_path;
}

void Comic::Path(winrt::hstring const& value)
{
	m_path = value;
}

winrt::hstring Comic::ChineseTeam()
{
	return m_chineseTeam;
}

void Comic::ChineseTeam(winrt::hstring const& value)
{
	m_chineseTeam = value;
}

winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Comic::Thumb()
{
	return m_img;
}

void Comic::Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
{
	m_img = value;
}
winrt::hstring Comic::ThumbPath()
{
	return m_thumbPath;
}

void Comic::ThumbPath(winrt::hstring const& value)
{
	m_thumbPath = value;
	Thumb(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{m_thumbPath} });
}
winrt::Windows::Data::Json::JsonObject Comic::Json()
{
	winrt::Windows::Data::Json::JsonObject json;
	winrt::Windows::Data::Json::JsonArray jsonArray;
	json.Insert(L"_id", winrt::Windows::Data::Json::JsonValue::CreateStringValue(ID()));
	json.Insert(L"title", winrt::Windows::Data::Json::JsonValue::CreateStringValue(Title()));
	json.Insert(L"total", winrt::Windows::Data::Json::JsonValue::CreateNumberValue(Total()));
	json.Insert(L"author", winrt::Windows::Data::Json::JsonValue::CreateStringValue(Author()));
	json.Insert(L"chineseTeam", winrt::Windows::Data::Json::JsonValue::CreateStringValue(Author()));
	for (auto ep : m_episodes)
	{
		winrt::Windows::Data::Json::JsonObject jsonEp;
		winrt::Windows::Data::Json::JsonArray jsonPics;
		jsonEp.Insert(L"_id", winrt::Windows::Data::Json::JsonValue::CreateStringValue(ep.ID()));
		jsonEp.Insert(L"title", winrt::Windows::Data::Json::JsonValue::CreateStringValue(ep.Title()));
		jsonEp.Insert(L"order", winrt::Windows::Data::Json::JsonValue::CreateNumberValue(ep.Index()));
		jsonEp.Insert(L"total", winrt::Windows::Data::Json::JsonValue::CreateNumberValue(ep.Total()));
		for (auto pic : ep.m_pictures)
		{
			winrt::Windows::Data::Json::JsonObject jsonPic;
			jsonPic.Insert(L"path", winrt::Windows::Data::Json::JsonValue::CreateStringValue(pic.LocalPath()));
			jsonPic.Insert(L"name", winrt::Windows::Data::Json::JsonValue::CreateStringValue(pic.OriginalName()));
			jsonPics.Append(jsonPic);
		}
		jsonEp.Insert(L"pics", jsonPics);
		jsonArray.Append(jsonEp);
	}
	json.Insert(L"eps", jsonArray);
	return json;
}
