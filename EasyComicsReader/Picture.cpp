#include "pch.h"
#include "Picture.h"



Picture::Picture(winrt::hstring const& localPath, winrt::hstring const& title)
{
	LocalPath(localPath);
	OriginalName(title);
	//Order(atoi(winrt::to_string(title).c_str()));
}

winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Picture::Img()
{
	return m_img;
}

void Picture::Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value)
{
	m_img = value;
}

winrt::hstring Picture::LocalPath()
{
	return m_localPath;
}

void Picture::LocalPath(winrt::hstring const& value)
{
	m_localPath = value;
	Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{m_localPath} });
}

winrt::hstring Picture::OriginalName()
{
	return m_originalName;
}

void Picture::OriginalName(winrt::hstring const& value)
{
	m_originalName = value;
}

winrt::hstring Picture::Url()
{
	return m_url;
}

void Picture::Url(winrt::hstring const& value)
{
	m_url = value;
	Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{m_url} });
}

uint32_t Picture::Order()
{
	return m_order;
}

void Picture::Order(uint32_t const& value)
{
	m_order = value;
}
