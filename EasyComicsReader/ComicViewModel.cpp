#include "pch.h"
#include "ComicViewModel.h"
using namespace winrt;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::Storage::Streams;

ComicViewModel::ComicViewModel()
{
}
/**
 * д�뻺��.
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
 * ��ȡ�ļ�.
 *
 * \param file ��ȡ���ļ�
 * \return �ļ�����
 */
Windows::Foundation::IAsyncOperation<winrt::hstring> ComicViewModel::ReadFile(StorageFile const& file)
{
    //���ȣ����� FileIO.ReadBufferAsync �������뻺����
    IBuffer buffer{ co_await FileIO::ReadBufferAsync(file) };
    //Ȼ��ʹ�� DataReader �����ȶ�ȡ�������ĳ���
    DataReader dataReader{ DataReader::FromBuffer(buffer) };
    //Ȼ���ȡ�����ݲ����ظ��ַ�����
    co_return dataReader.ReadString(buffer.Length());
}

/**
 * ��ȡĿ¼��������.
 *
 * \param folder Ŀ¼
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
                })) MessageBox(NULL, L"�����ظ�����:������ͬ��������!", L"Error", NULL);


            co_return;
        }
    }
    MessageBox(NULL, L"�������:δ�ҵ���������!", L"Error", NULL);
}

/**
 * ����.
 *
 */
winrt::Windows::Foundation::IAsyncAction ComicViewModel::Reload()
{
    m_comics.clear();
    co_await LoadCache();
}

/**
 * ɾ������.
 *
 * \param Id ����ID
 * \return �Ƿ�ɹ�
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
 * �������.
 *
 * \param co ����ʵ��
 * \return �Ƿ�ɹ�
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
 * ��ȡ����.
 *
 * \param Id ����ID
 * \return ����ʵ��
 */
Comic ComicViewModel::GetComic(winrt::hstring const& Id)
{
    for(Comic x: m_comics)
    {
        if (x.ID() == Id) return x;
    }
}

