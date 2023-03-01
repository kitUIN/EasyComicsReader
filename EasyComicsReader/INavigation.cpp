#include "INavigation.h"



INavigation::INavigation(winrt::Windows::Data::Json::JsonObject const& json)
{
    if(json.HasKey(L"_id")) ID(json.GetNamedString(L"_id"));
    if(json.HasKey(L"total")) Total(static_cast<uint32_t>(json.GetNamedNumber(L"total")));
    if(json.HasKey(L"title")) Title(json.GetNamedString(L"title"));
    if(json.HasKey(L"order")) Index(static_cast<uint32_t>(json.GetNamedNumber(L"order")));
}

winrt::hstring INavigation::ID()
{
    return m_id;
}

void INavigation::ID(winrt::hstring const& value)
{
    m_id = value;
}

uint32_t INavigation::Total()
{
    return m_total;
}

void INavigation::Total(uint32_t value)
{
    m_total = value;
}

uint32_t INavigation::Index()
{
    return m_index;
}

void INavigation::Index(uint32_t value)
{
    m_index = value;
}
winrt::hstring INavigation::Title()
{
    return m_title;
}

void INavigation::Title(winrt::hstring const& value)
{
    m_title = value;
}