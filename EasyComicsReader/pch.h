#include "framework.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/windows.ui.xaml.controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.input.h>
#include <winrt/Windows.UI.input.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Storage.h>
#include <Shobjidl.h>
#include <winrt/Windows.Storage.Pickers.h>

#include <winrt/Windows.UI.Text.h>



#define ECR_TYPE_JSON L".json"
#define ECR_TYPE_JPG L".jpg"
#define ECR_FILE_CACHE L"Comics.cache"
