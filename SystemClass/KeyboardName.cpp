#include "pch.h"
#include "KeyboardName.h"
#include <codecvt>
using namespace DirectX;
std::unique_ptr<KeyboardName> KeyboardName::m_KeyboardName = nullptr;
bool keyPressed[256] = { false }; // キーボードの各キーの押下状態を保持する配列
float keyPressTime[256] = { 0 }; // キーが押された時間を保持する配列
const float repeatDelay = 0.5f; // 連続入力の遅延時間（ミリ秒）
KeyboardName::KeyboardName()
{
}

void KeyboardName::Update()
{
	m_KeyboardTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	m_Keyboard = Keyboard::Get().GetState();
}

void KeyboardName::SetName(std::wstring& name)
{

    for (int i = 0; i < 256; i++)
    {
        if (GetAsyncKeyState(i) & 0x8000 && !keyPressed[i])
        {
            keyPressed[i] = true;
            // キーが押されたときの処理
            if (i >= 'A' && i <= 'Z')
            {
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                {
                    name += (wchar_t)i;
                }
                else
                {
                    name += (wchar_t)(i + 32);
                }
            }
            else if (i >= '0' && i <= '9')
            {
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                {
                    switch (i)
                    {
                    case '1': name += L"!"; break;
                    case '2': name += L"\""; break;
                    case '3': name += L"#"; break;
                    case '4': name += L"$"; break;
                    case '5': name += L"%"; break;
                    case '6': name += L"&"; break;
                    case '7': name += L"'"; break;
                    case '8': name += L"("; break;
                    case '9': name += L")"; break;
                    }
                }
                else
                {
                    name += (wchar_t)i;
                }
            }
            else if (i == VK_BACK)
            {
                // バックスペースキーが押されたときの処理
                if (!name.empty())
                {
                    name.erase(name.size() - 1);
                }
            }
            else
            {
                // 特殊文字や記号などの処理
                if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
                {
                    switch (i)
                    {
                    case VK_OEM_MINUS:      name += L"="; break;
                    case VK_OEM_PLUS:       name += L"+"; break;
                    case VK_OEM_1:          name += L"*"; break;
                    case VK_OEM_2:          name += L"?"; break;
                    case VK_OEM_3:          name += L"`"; break;
                    case VK_OEM_4:          name += L"{"; break;
                    case VK_OEM_5:          name += L"|"; break;
                    case VK_OEM_6:          name += L"}"; break;
                    case VK_OEM_7:          name += L"~"; break;
                    case VK_OEM_COMMA:      name += L"<"; break;
                    case VK_OEM_PERIOD:     name += L">"; break;
                    case VK_OEM_102:        name += L"_"; break;
                    case VK_SPACE:          name += L" "; break;
                    }
                }
                else
                {
                    switch (i)
                    {
                    case VK_OEM_MINUS:      name += L"-"; break;
                    case VK_OEM_PLUS:       name += L";"; break;
                    case VK_OEM_1:          name += L":"; break;
                    case VK_OEM_2:          name += L"/"; break;
                    case VK_OEM_3:          name += L"@"; break;
                    case VK_OEM_4:          name += L"["; break;
                    case VK_OEM_5:          name += L"\\"; break;
                    case VK_OEM_6:          name += L"]"; break;
                    case VK_OEM_7:          name += L"^"; break;
                    case VK_OEM_COMMA:      name += L","; break;
                    case VK_OEM_PERIOD:     name += L"."; break;
                    case VK_OEM_102:        name += L"\\"; break;
                    case VK_SPACE:          name += L" "; break;
                    }
                }
            }
        }
        else if (GetAsyncKeyState(i) & 0x8000 && keyPressed[i])
        {
            keyPressTime[i] += 0.016666f;
            if (keyPressTime[i] > repeatDelay)
            {
                // 一定時間以上経過したら連続入力
                keyPressed[i] = false;
                // キーが押されたときの処理（連続入力）
                // （省略：同じ処理を繰り返す）
            }
        }
        else
        {
            keyPressed[i] = false;
            // キーが離されたときの処理
            keyPressTime[i] = 0;
        }
    }
}
void KeyboardName::SetName(std::string& name)
{
    // ワイド文字列への変換
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(name);
    SetName(wide);

    name = converter.to_bytes(wide);

}
KeyboardName* KeyboardName::GetInstance()
{
	//すでに生成されてるかチェック
	if (m_KeyboardName == nullptr)
	{
		//画像のインスタンスを生成する
		m_KeyboardName = std::make_unique<KeyboardName>();
	}
	//画像のインスタンスを返す
	return m_KeyboardName.get();
}

