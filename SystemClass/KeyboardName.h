#pragma once
/// <summary>
/// KeyboardNameクラスを定義する
/// </summary>
class KeyboardName
{
public:
	/// <summary>
	/// 描画クラスのインスタンスを取得する
	/// </summary>
	/// <returns>描画クラスのインスタンス</returns>
	static KeyboardName*  GetInstance();

	/// <summary>
	/// コンストラクタ
	/// </summary>
	KeyboardName();

	void Update();
	void SetName(std::wstring& name);
	void SetName(std::string& name);

private:
	// 描画のインスタンスへのポインタ
	static std::unique_ptr<KeyboardName> m_KeyboardName;

	// 描画のインスタンスへのポインタ
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// 描画のインスタンスへのポインタ
	DirectX::Keyboard::State m_Keyboard;
};


