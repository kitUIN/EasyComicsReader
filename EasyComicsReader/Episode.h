#pragma once
#include "pch.h"
#include "INavigation.h"
#include "Picture.h"

class Episode :public INavigation
{
public:
	Episode(winrt::Windows::Data::Json::JsonObject const& json);

	std::vector<Picture> m_pictures;


};
