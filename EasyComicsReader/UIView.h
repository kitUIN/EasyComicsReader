#pragma once
#include "pch.h"
#include "ComicViewModel.h"

class UIView
{
public:
	UIView();

	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> OpenFolderPicker(HWND hWnd);
	winrt::Windows::Foundation::IAsyncAction OnAddButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&);
	winrt::Windows::Foundation::IAsyncAction OnRemoveButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&);
	winrt::Windows::Foundation::IAsyncAction OnRefreshButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&);
	// void OnEpisodeButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&);
	winrt::Windows::Foundation::IAsyncAction Init_Loading(winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args);
	winrt::Windows::Foundation::IAsyncAction Refresh();
	void ComicsListInit();
	ComicViewModel m_comicViewModel;
	void LoadComicBorder(Comic co);
	winrt::Windows::UI::Xaml::Controls::StackPanel m_comicsList{ nullptr };
	winrt::Windows::UI::Xaml::Controls::StackPanel m_picsList{ nullptr };
	winrt::Windows::UI::Xaml::Controls::StackPanel m_mainStackPanel{ nullptr };

private:
	winrt::Windows::UI::Xaml::Controls::ScrollViewer m_comicsScrollViewer{ nullptr };
	winrt::Windows::UI::Xaml::Controls::ScrollViewer m_picsScrollViewer{ nullptr };
};
