#include "UIView.h"

using namespace winrt;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI;
using namespace winrt::Windows::UI::Text;
using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::UI::Input;
using namespace winrt::Windows::UI::Xaml::Input;
using namespace winrt::Windows::UI::Xaml::Media;
using namespace winrt::Windows::UI::Xaml::Controls::Primitives;
using namespace winrt::Windows::Foundation;

UIView::UIView()
{

}
/**
 * 打开文件夹选择器.
 *
 * \param hWnd
 * \return
 */
winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> UIView::OpenFolderPicker(HWND hWnd)
{
    winrt::Windows::Storage::Pickers::FolderPicker folderPicker;
    auto initializeWithWindow{ folderPicker.as<::IInitializeWithWindow>() };
    initializeWithWindow->Initialize(hWnd);
    folderPicker.FileTypeFilter().Append(L"*");
    co_return co_await folderPicker.PickSingleFolderAsync();
}
/**
 * 界面初始化.
 *
 * \param sender
 * \param args
 * \return
 */
winrt::Windows::Foundation::IAsyncAction UIView::Init_Loading(winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const& args)
{
    co_await m_comicViewModel.LoadCache();
    for (auto x : m_comicViewModel.m_comics)
    {
        LoadComicBorder(x);
    }
}
/**
 * 添加漫画按钮响应.
 *
 * \param sender
 * \param
 * \return
 */
winrt::Windows::Foundation::IAsyncAction UIView::OnAddButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    extern HWND c_hWnd;
    winrt::Windows::Storage::StorageFolder folder = co_await OpenFolderPicker(c_hWnd);
    if (folder != nullptr)
    {
        co_await m_comicViewModel.LoadComic(folder);
        m_comicsList.Children().Clear();
        for (auto x : m_comicViewModel.m_comics)
        {
            LoadComicBorder(x);
        }
    }
    else
    {
        MessageBox(NULL, L"导入错误:未选择漫画文件夹!", L"Error", NULL);
    }
}
/**
 * 删除漫画按钮响应.
 *
 * \param sender
 * \param
 * \return
 */
winrt::Windows::Foundation::IAsyncAction UIView::OnRemoveButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    m_comicViewModel.RemoveComic(sender.as<Button>().Tag().as<hstring>());
    co_await Refresh();
}

/**
 * 刷新按钮响应.
 *
 * \param sender
 * \param
 * \return
 */
winrt::Windows::Foundation::IAsyncAction UIView::OnRefreshButtonClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
{
    co_await Refresh();
}
/**
 * 刷新漫画列表.
 *
 * \param sender
 * \param
 * \return
 */
winrt::Windows::Foundation::IAsyncAction UIView::Refresh()
{
    co_await m_comicViewModel.Reload();
    m_comicsList.Children().Clear();
    for (auto x : m_comicViewModel.m_comics)
    {
        LoadComicBorder(x);
    }
}

/**
 * 界面初始化.
 *
 */
void UIView::ComicsListInit()
{
    m_comicsList = StackPanel();
    m_picsList = StackPanel();
    m_mainStackPanel = StackPanel();
    m_comicsScrollViewer = ScrollViewer();
    m_picsScrollViewer = ScrollViewer();
    StackPanel buttons;
    StackPanel listComics;
    Button importButton;
    Button refreshButton;

    importButton.CornerRadius(CornerRadius{ 5,5,5,5 });
    importButton.Margin( Thickness{5,0,0,5} );
    importButton.Content(box_value(L"导入漫画"));
    importButton.Click({ this,&UIView::OnAddButtonClick });

    refreshButton.CornerRadius(CornerRadius{ 5,5,5,5 });
    refreshButton.Margin(Thickness{ 5,0,0,5 });
    refreshButton.Content(box_value(L"刷新"));
    refreshButton.Click({ this,&UIView::OnRefreshButtonClick });

    buttons.Orientation(Orientation::Horizontal);
    buttons.FlowDirection(FlowDirection::RightToLeft);
    buttons.Children().Append(importButton);
    buttons.Children().Append(refreshButton);

    m_comicsList.Width(380);

    m_comicsScrollViewer.Content(m_comicsList);
    m_picsScrollViewer.Content(m_picsList);

    m_picsScrollViewer.Height(600);
    m_comicsScrollViewer.Height(500);
    m_picsScrollViewer.Margin(Thickness{ 10,0,0,0 });

    m_mainStackPanel.Width(1200);

    m_mainStackPanel.Orientation(Orientation::Horizontal);
    listComics.Children().Append(buttons);
    listComics.Children().Append(m_comicsScrollViewer);
    m_mainStackPanel.Children().Append(listComics);
    m_mainStackPanel.Children().Append(m_picsScrollViewer);

    m_comicsList.Loading({ this, &UIView::Init_Loading });
}
/**
 * 加载一个漫画UI.
 *
 * \param co
 */
void UIView::LoadComicBorder(Comic co)
{
    Image image;
    ScrollViewer epsScrollViewer;
    TextBlock comicTitle;
    TextBlock comicAuthor;
    TextBlock comicChineseTeam;
    StackPanel docsStackPanel;
    StackPanel epsStackPanel;
    StackPanel comicStackPanel;
    Border comicBorder;
    Button deleteButton;

    image.Width(100);
    image.VerticalAlignment(VerticalAlignment::Top);

    comicTitle.FontSize(20);
    comicTitle.FontWeight(::FontWeights::Bold());
    comicTitle.Margin(Thickness{ 5,0,0,0 });
    comicTitle.FontSize(17);

    comicAuthor.Margin(Thickness{ 5,0,0,0 });
    comicAuthor.Foreground(SolidColorBrush{ Colors::LightSkyBlue() });

    comicChineseTeam.Margin(Thickness{ 5,0,0,0 });
    comicChineseTeam.Foreground(SolidColorBrush{ Colors::LightPink() });

    epsStackPanel.Orientation(Orientation::Horizontal);

    epsScrollViewer.Width(300);
    epsScrollViewer.Margin(Thickness{ 0,5,0,0 });
    epsScrollViewer.Content(epsStackPanel);

    deleteButton.Margin(Thickness{ 5,0,0,0 });
    deleteButton.CornerRadius(CornerRadius{ 5,5,5,5 });
    deleteButton.Margin(Thickness{ 5,5,0,0 });
    deleteButton.Content(box_value(L"删除"));
    deleteButton.Tag(box_value(co.ID()));
    deleteButton.Click({ this, &UIView::OnRemoveButtonClick });

    docsStackPanel.Children().Append(comicTitle);
    docsStackPanel.Children().Append(comicAuthor);
    docsStackPanel.Children().Append(comicChineseTeam);
    docsStackPanel.Children().Append(epsScrollViewer);
    docsStackPanel.Children().Append(deleteButton);

    comicStackPanel.Orientation(Orientation::Horizontal);
    comicStackPanel.VerticalAlignment(VerticalAlignment::Center);
    comicStackPanel.Children().Append(image);
    comicStackPanel.Children().Append(docsStackPanel);

    image.Source(co.Thumb());
    comicTitle.Text(co.Title());
    comicAuthor.Text(co.Author());
    comicChineseTeam.Text(co.ChineseTeam());
    for (auto x : co.m_episodes)
    {
        Button ep;
        ep.Margin(Thickness{ 5,0,0,0 });
        ep.CornerRadius(CornerRadius{ 5,5,5,5 });
        ep.Content(box_value(x.Title()));
        ep.Tag(box_value(co.ID()));
        ep.Click([this](IInspectable const&  sender , RoutedEventArgs const& /* args */)
            {
                hstring id = sender.as<Button>().Tag().as<hstring>();
                hstring title = sender.as<Button>().Content().as<hstring>();
                for (auto x : m_comicViewModel.m_comics)
                {
                    if (x.ID() == id)
                    {
                        for (auto y : x.m_episodes)
                        {
                            if (y.Title() == title)
                            {
                                m_picsList.Children().Clear();
                                for (auto z : y.m_pictures)
                                {
                                    Image image;
                                    image.Width(730);
                                    image.Source(z.Img());
                                    m_picsList.Children().Append(image);
                                }
                            }
                        }
                    }
                }
            }
        );
        /*MenuFlyout menuFlyout;
        MenuFlyoutItem menuFlyoutItem;
        menuFlyoutItem.Text(L"删除");
        menuFlyout.Items().Append(menuFlyoutItem);
        ep.ContextFlyout(menuFlyout);
        ep.PointerPressed([this](IInspectable const& sender, PointerRoutedEventArgs const& e)
            {
                PointerPoint currentPoint = e.GetCurrentPoint(NULL);
                PointerPointProperties props = currentPoint.Properties();
                if (props.IsRightButtonPressed())
                {
                    auto flyout = FlyoutBase::GetAttachedFlyout(sender.as<FrameworkElement>());
                    auto options = FlyoutShowOptions();
                    flyout.ShowAt(sender.as<FrameworkElement>(), options);
                }
            }
        );*/

        epsStackPanel.Children().Append(ep);
    }
    comicBorder.Margin(Thickness{ 0,5,0,0 });
    comicBorder.CornerRadius(CornerRadius{ 5,5,5,5 });
    comicBorder.Height(138);
    comicBorder.BorderThickness(Thickness{ 1.5,1.5,1.5,1.5 });
    comicBorder.BorderBrush(SolidColorBrush{ Colors::LightPink() });
    comicBorder.Child(comicStackPanel);

    m_comicsList.Children().Append(comicBorder);

    m_mainStackPanel.UpdateLayout();
}


