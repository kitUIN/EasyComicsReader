#include "pch.h"
#include "ComicViewModel.h"
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

ComicViewModel::ComicViewModel()
{
}
/**
 * 写入缓存.
 *
 * \return
 */
winrt::Windows::Foundation::IAsyncAction ComicViewModel::SetCache()
{
    winrt::Windows::Data::Json::JsonObject json;
    winrt::Windows::Data::Json::JsonArray jsonArrary;
    for (auto x : m_comics)
    {
        winrt::Windows::Data::Json::JsonObject _json;
        _json.Insert(L"path", winrt::Windows::Data::Json::JsonValue::CreateStringValue(x.Path()));
        _json.Insert(L"_id", winrt::Windows::Data::Json::JsonValue::CreateStringValue(x.ID()));
        jsonArrary.Append(_json);
    }
    json.Insert(L"cache", jsonArrary);
    winrt::Windows::Storage::StorageFolder storageFolder{ winrt::Windows::Storage::ApplicationData::Current().LocalFolder() };
    auto sampleFile = co_await storageFolder.CreateFileAsync(ECR_FILE_CACHE, winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting);
    winrt::Windows::Storage::Streams::IBuffer buffer{
        winrt::Windows::Security::Cryptography::CryptographicBuffer::ConvertStringToBinary(
            json.Stringify(),
            winrt::Windows::Security::Cryptography::BinaryStringEncoding::Utf8) };
    co_await winrt::Windows::Storage::FileIO::WriteBufferAsync(sampleFile, buffer);
}

winrt::Windows::Foundation::IAsyncAction ComicViewModel::LoadCache()
{
    winrt::Windows::Storage::StorageFolder folder{ winrt::Windows::Storage::ApplicationData::Current().LocalFolder() };
    for (auto const& file : co_await folder.GetFilesAsync())
    {
        if (file.Name() == ECR_FILE_CACHE)
        {
            auto json = winrt::Windows::Data::Json::JsonObject::Parse(co_await winrt::Windows::Storage::FileIO::ReadTextAsync(file));
            if (json.HasKey(L"cache"))
            {
                for (auto x : json.GetNamedArray(L"cache"))
                {
                    co_await LoadComic(co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(x.GetObjectW().GetNamedString(L"path")));
                }
            }
        }
    }
}

/**
 * 读取文件.
 *
 * \param file 读取的文件
 * \return 文件内容
 */
Windows::Foundation::IAsyncOperation<winrt::hstring> ComicViewModel::ReadFile(StorageFile const& file)
{
    //首先，调用 FileIO.ReadBufferAsync 方法载入缓冲区
    IBuffer buffer{ co_await FileIO::ReadBufferAsync(file) };
    //然后，使用 DataReader 对象先读取缓冲区的长度
    DataReader dataReader{ DataReader::FromBuffer(buffer) };
    //然后读取其内容并返回该字符串。
    co_return dataReader.ReadString(buffer.Length());
}

/**
 * 读取目录漫画数据.
 *
 * \param folder 目录
 * \return
 */
winrt::Windows::Foundation::IAsyncAction ComicViewModel::LoadComic(winrt::Windows::Storage::StorageFolder const& folder)
{
    for (auto const& file : co_await folder.GetFilesAsync())
    {
        if (file.FileType() == ECR_TYPE_JSON)
        {
            if(!AddComic(
                Comic{
                    winrt::Windows::Data::Json::JsonObject::Parse(co_await ReadFile(file)),
                    folder.Path()
                })) MessageBox(NULL, L"请勿重复导入:存在相同漫画数据!", L"Error", NULL);


            co_return;
        }
    }
    MessageBox(NULL, L"导入错误:未找到漫画数据!", L"Error", NULL);
}

/**
 * 重载.
 *
 */
winrt::Windows::Foundation::IAsyncAction ComicViewModel::Reload()
{
    m_comics.clear();
    co_await LoadCache();
}

/**
 * 删除漫画.
 *
 * \param Id 漫画ID
 * \return 是否成功
 */
bool ComicViewModel::RemoveComic(winrt::hstring const& Id)
{
    for (std::vector<Comic>::iterator i = m_comics.begin(); i != m_comics.end(); i++)
    {
        if((*i).ID() == Id)
        {
            i = m_comics.erase(i);
            SetCache();
            return true;
        }
    }
    return false;
}
/**
 * 添加漫画.
 *
 * \param co 漫画实例
 * \return 是否成功
 */
bool ComicViewModel::AddComic(Comic co)
{
    for (Comic x : m_comics)
    {
        if (x.ID() == co.ID()) return false;
    }
    m_comics.push_back(co);
    SetCache();
    return true;
}
/**
 * 获取漫画.
 *
 * \param Id 漫画ID
 * \return 漫画实例
 */
Comic ComicViewModel::GetComic(winrt::hstring const& Id)
{
    for(Comic x: m_comics)
    {
        if (x.ID() == Id) return x;
    }
}

