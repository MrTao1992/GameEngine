#include "AssetLoadManager.h"

using namespace Phantom;
using namespace std;
int AssetLoadManager::Initialize()
{
    return 0;
}

void AssetLoadManager::Finalize()
{
    m_strSearchPath.clear();
}

void AssetLoadManager::Tick()
{
}
bool AssetLoadManager::AddSearchPath(const char *path)
{
    std::vector<std::string>::iterator src = m_strSearchPath.begin();
    while (src != m_strSearchPath.end())
    {
        if (!(*src).compare(path))
            return true;
        src++;
    }
    m_strSearchPath.push_back(path);
    return true;
}

bool AssetLoadManager::RemoveSearchPath(const char *path)
{
    std::vector<std::string>::iterator src = m_strSearchPath.begin();

    while (src != m_strSearchPath.end())
    {
        if (!(*src).compare(path))
        {
            m_strSearchPath.erase(src);
            return true;
        }
        src++;
    }

    return true;
}

bool AssetLoadManager::FileExists(const char *filePath)
{
    AssetFilePtr fp = OpenFile(filePath, PH_OPEN_BINARY);
    if (fp != nullptr)
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

AssetLoadManager::AssetFilePtr AssetLoadManager::OpenFile(const char *name, AssetOpenMode mode)
{
    FILE *fp = nullptr;
    // loop N times up the hierarchy, testing at each level
#ifdef __psp2__
    std::string upPath = "app0:/";
#elseif __ORBIS__
    std::string upPath = "/app0/";
#else
    std::string upPath;
#endif
    std::string fullPath;
    for (int32_t i = 0; i < 10; i++)
    {
        std::vector<std::string>::iterator src = m_strSearchPath.begin();
        bool looping = true;
        while (looping)
        {
            fullPath.assign(upPath); // reset to current upPath.
            if (src != m_strSearchPath.end())
            {
                fullPath.append(*src);
                fullPath.append("/Assets/");
                src++;
            }
            else
            {
                fullPath.append("Assets/");
                looping = false;
            }
            fullPath.append(name);
            fprintf(stderr, "Trying to open %s\n", fullPath.c_str());

            switch (mode)
            {
            case PH_OPEN_TEXT:
                fp = fopen(fullPath.c_str(), "r");
                break;
            case PH_OPEN_BINARY:
                fp = fopen(fullPath.c_str(), "rb");
                break;
            }

            if (fp)
                return (AssetFilePtr)fp;
        }

        upPath.append("../");
    }

    return nullptr;
}

Buffer AssetLoadManager::SyncOpenAndReadText(const char *filePath)
{
    AssetFilePtr fp = OpenFile(filePath, PH_OPEN_TEXT);
    Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetSize(fp);

        pBuff = new Buffer(length + 1);
        length = fread(pBuff->GetData(), 1, length, static_cast<FILE *>(fp));
#ifdef DEBUG
        fprintf(stderr, "Read file '%s', %zu bytes\n", filePath, length);
#endif

        pBuff->GetData()[length] = '\0';

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

    return *pBuff;
}

Buffer AssetLoadManager::SyncOpenAndReadBinary(const char *filePath)
{
    AssetFilePtr fp = OpenFile(filePath, PH_OPEN_BINARY);
    Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetSize(fp);

        pBuff = new Buffer(length);
        fread(pBuff->GetData(), length, 1, static_cast<FILE *>(fp));
#ifdef DEBUG
        fprintf(stderr, "Read file '%s', %zu bytes\n", filePath, length);
#endif

        CloseFile(fp);
    }
    else
    {
        fprintf(stderr, "Error opening file '%s'\n", filePath);
        pBuff = new Buffer();
    }

    return *pBuff;
}

void AssetLoadManager::CloseFile(AssetFilePtr &fp)
{
    fclose((FILE *)fp);
    fp = nullptr;
}

size_t AssetLoadManager::GetSize(const AssetFilePtr &fp)
{
    FILE *_fp = static_cast<FILE *>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

size_t AssetLoadManager::SyncRead(const AssetFilePtr &fp, Buffer &buf)
{
    size_t sz;

    if (!fp)
    {
        fprintf(stderr, "null file discriptor\n");
        return 0;
    }

    sz = fread(buf.GetData(), buf.GetDataSize(), 1, static_cast<FILE *>(fp));

    return sz;
}

int32_t AssetLoadManager::Seek(AssetFilePtr fp, long offset, AssetSeekBase where)
{
    return fseek(static_cast<FILE *>(fp), offset, static_cast<int>(where));
}