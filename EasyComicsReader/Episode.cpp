#include "Episode.h"

Episode::Episode(winrt::Windows::Data::Json::JsonObject const& json): INavigation(json)
{
	if (json.HasKey(L"pics"))
	{
		for (auto x : json.GetNamedArray(L"pics"))
		{
			m_pictures.push_back(
				Picture{
					x.GetObjectW().GetNamedString(L"path"),
					x.GetObjectW().GetNamedString(L"name")
				});
		}

	}
}


