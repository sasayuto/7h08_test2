#pragma once
#include"Scene/GameObjects/TutorialScene/TutorialLetter.h"
#include"ImaseLib/OperationUI.h"
/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class IStateTutorialUI
{
public:
	TutorialLetter* GetTextLetter() { return m_textLetter.get(); };

	float GetTimer() { return m_timer; };
	void SetTimer(float timer) { m_timer = timer; };

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	IStateTutorialUI() :
		m_timer(),
		m_textLetter()
	{
		m_textLetter = std::make_unique<TutorialLetter>();
	}
	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~IStateTutorialUI() = default;

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize() = 0;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	virtual void Update(const float& elapsedTime) = 0;

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 後始末
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// リセット
	/// </summary>
	virtual void Reset() = 0;

private:
	std::unique_ptr<TutorialLetter> m_textLetter;

	float m_timer;
};
