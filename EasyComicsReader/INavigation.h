#include "pch.h"

class INavigation
{
public:
	INavigation(winrt::Windows::Data::Json::JsonObject const& json);
	uint32_t Total();
	void Total(uint32_t value);
	uint32_t Index();
	void Index(uint32_t value);
	winrt::hstring Title();
	void Title(winrt::hstring const& value);
	winrt::hstring ID();
	void ID(winrt::hstring const& value);
private:
	winrt::hstring m_id = L"";
	uint32_t m_total = 0;
	uint32_t m_index = 0;
	winrt::hstring m_title = L"";
};
