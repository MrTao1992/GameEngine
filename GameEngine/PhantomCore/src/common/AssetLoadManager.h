#pragma once
#include <string>
#include <vector>
#include "IRuntimeModule.h"
#include "Buffer.h"
namespace Phantom
{
    class AssetLoadManager : public IRuntimeModule
    {
    public:
        virtual ~AssetLoadManager(){};

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        enum AssetOpenMode
        {
            PH_OPEN_TEXT = 0,   /// 以文本形式打开
            PH_OPEN_BINARY = 1, /// 以字节形式打开
        };
        enum AssetSeekBase
        {
            PH_SEEK_SET = 0,
            PH_SEEK_CUR = 1,
            PH_SEEK_END = 2
        };

        typedef void *AssetFilePtr;

        //增加搜索路径
        bool AddSearchPath(const char *path);
        //移除搜索路径
        bool RemoveSearchPath(const char *path);

        virtual bool FileExists(const char *filePath);

        virtual AssetFilePtr OpenFile(const char *name, AssetOpenMode mode);

        virtual Buffer SyncOpenAndReadText(const char *filePath);

        virtual Buffer SyncOpenAndReadBinary(const char *filePath);

        virtual size_t SyncRead(const AssetFilePtr &fp, Buffer &buf);

        virtual void CloseFile(AssetFilePtr &fp);

        virtual size_t GetSize(const AssetFilePtr &fp);

        virtual int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);

        inline std::string SyncOpenAndReadTextFileToString(const char *fileName)
        {
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            if (buffer.GetDataSize())
            {
                char *content = reinterpret_cast<char *>(buffer.GetData());

                if (content)
                {
                    result = std::string(std::move(content));
                }
            }

            return result;
        }

    private:
        std::vector<std::string> m_strSearchPath;
    };
    extern AssetLoadManager *g_pAssetLoader;
}