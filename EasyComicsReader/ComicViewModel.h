#include "Comic.h"
#include "pch.h"
class ComicViewModel
{
public:
	ComicViewModel();
	winrt::Windows::Foundation::IAsyncAction Reload();
	bool RemoveComic(winrt::hstring const& Id);
	Comic GetComic(winrt::hstring const& Id);
	winrt::Windows::Foundation::IAsyncAction LoadComic(winrt::Windows::Storage::StorageFolder const& folder);
	std::vector<Comic> m_comics;
	winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> ReadFile(winrt::Windows::Storage::StorageFile const& file);
	winrt::Windows::Foundation::IAsyncAction LoadCache();
private:
	bool AddComic(Comic co);
	winrt::Windows::Foundation::IAsyncAction SetCache();
};
