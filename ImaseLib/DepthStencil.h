//--------------------------------------------------------------------------------------
// File: DepthStencil.h
//
// 深度ステンシル作成のためのヘルパークラス
// ※MicosoftのRenderTextureクラスを参考に作成
//
// Date: 2023.11.4
// Author: Hideyasu Imase
//-------------------------------------------------------------------------------------

#pragma once

namespace Imase
{
    class DepthStencil
    {
    public:
        explicit DepthStencil(DXGI_FORMAT format) noexcept;

        DepthStencil(DepthStencil&&) = default;
        DepthStencil& operator= (DepthStencil&&) = default;

        DepthStencil(DepthStencil const&) = delete;
        DepthStencil& operator= (DepthStencil const&) = delete;

        void SetDevice(_In_ ID3D11Device* device);

        void SizeResources(size_t width, size_t height);

        void ReleaseDevice() noexcept;

        void SetWindow(const RECT& rect);

        ID3D11Texture2D* GetTexture2D() const noexcept { return m_texture2D.Get(); }
        ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_depthStencilView.Get(); }
        void SetDepthStencilView(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> v) { m_depthStencilView = v; }
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepth() { return m_depthStencilView; };
        DXGI_FORMAT GetFormat() const noexcept { return m_format; }

    private:
        Microsoft::WRL::ComPtr<ID3D11Device>                m_device;
        Microsoft::WRL::ComPtr<ID3D11Texture2D>             m_texture2D;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      m_depthStencilView;

        DXGI_FORMAT                                         m_format;

        size_t                                              m_width;
        size_t                                              m_height;
    };
}
