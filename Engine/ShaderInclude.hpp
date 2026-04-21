#include <fstream>
#include <utility>
#include <cstddef>
#include <wrl.h>
#include <Plugins\DirectX\d3dcommon.h>

class ShaderInclude : public ID3DInclude {
public:
    std::string baseDir{};

    ShaderInclude(std::string base) : baseDir(std::move(base)) {}

    STDMETHOD(Open)(
        D3D_INCLUDE_TYPE,
        LPCSTR fileName,
        LPCVOID,
        LPCVOID* data,
        UINT* bytes
    ) override {
        std::string const fullPath = baseDir + "/" + fileName;

        OutputDebugStringA((std::string("[Shader Compiler]: ") + (fullPath + "\n")).c_str());

        std::ifstream file(fullPath, std::ios::binary);
        if (!file) {
            OutputDebugStringA((std::string("[Shader Compiler]: Error finding:") + (fullPath + "\n")).c_str());
            return E_FAIL;
        }

        file.seekg(0, std::ios::end);
        size_t const size = file.tellg();
        file.seekg(0, std::ios::beg);

        char* buffer = new char[size];
        file.read(buffer, size);

        *data = buffer;
        *bytes = (UINT)size;
        
        return S_OK;
    }

    STDMETHOD(Close)(LPCVOID data) override {
        delete[] reinterpret_cast<const char*>(data);
        return S_OK;
    }
};