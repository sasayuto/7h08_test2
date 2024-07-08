//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <winsdkver.h>
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif
#include <sdkddkver.h>

// Use the C++ standard templated min/max
#define NOMINMAX

// DirectX apps don't need GDI
#define NODRAWTEXT
#define NOGDI
#define NOBITMAP

// Include <mcx.h> if you need this
#define NOMCX

// Include <winsvc.h> if you need this
#define NOSERVICE

// WinHelp is deprecated
#define NOHELP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <wrl/client.h>

#include <d3d11_1.h>
#include <dxgi1_6.h>

#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <exception>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <tuple>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) noexcept : result(hr) {}

        const char* what() const noexcept override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

// DirectXTK
#include "SimpleMath.h"
#include "CommonStates.h"
#include "SpriteBatch.h"
#include "DDSTextureLoader.h"
#include"Model.h"
#include"Effects.h"
#include"Scene/GameObjects/Models/KeyboardTracker.h"
#include"Scene/GameObjects/Models/SingletonDeviceResources.h"
#include"json/json/json.h"
#include"json/json/allocator.h"
#include"json/json/assertions.h"
#include"json/json/config.h"
#include"json/json/forwards.h"
#include"json/json/json.h"
#include"json/json/json_features.h"
#include"json/json/reader.h"
#include"json/json/value.h"
#include"json/json/version.h"
#include"json/json/writer.h"