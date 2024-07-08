#pragma once
#include"IStateTutorialUI.h"

class TutorialUI;
/// <summary>
/// アイテムの基底クラスを定義する
/// </summary>
class NiceLetter : public IStateTutorialUI
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	NiceLetter(TutorialUI* tutorialUI);

	/// <summary>
	/// 初期化する
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="elapsedTime">1フレーム時間</param>
	void Update(const float& elapsedTime) override;

	/// <summary>
	/// 描画する
	/// </summary>
	void Render() override;

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize() override;

	/// <summary>
	/// リセット
	/// </summary>
	void Reset() override;

private:
	TutorialUI* m_pTutorialUI;
};
