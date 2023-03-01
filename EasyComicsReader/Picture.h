
#include "pch.h"


class Picture
{
public:
    Picture(winrt::hstring const& localPath ,winrt::hstring const& title);
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage Img();
    void Img(winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage const& value);
    winrt::hstring LocalPath();
    void LocalPath(winrt::hstring const& value);
    winrt::hstring OriginalName();
    void OriginalName(winrt::hstring const& value);
    winrt::hstring Url();
    void Url(winrt::hstring const& value);
    uint32_t Order();
    void Order(uint32_t const& value);
private:
    winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage m_img = winrt::Windows::UI::Xaml::Media::Imaging::BitmapImage{ winrt::Windows::Foundation::Uri{L"https://files.catbox.moe/lx8fu2.png"} };
    uint32_t m_order = 0;
    winrt::hstring m_localPath = L"";
    winrt::hstring m_url = L"";
    winrt::hstring m_originalName = L"";
};
