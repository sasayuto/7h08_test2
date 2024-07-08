#pragma once

class StageSelect;
class StageSelectScene;
/// <summary>
/// ISelectPlaySceneインターフェイスを定義する
/// </summary>
class ISelectPlayScene
{
public:
	StageSelect* GetStageSelect() { return m_pStageSelect; };
	StageSelectScene* GetStageSelectScene() { return m_pStageSelectScene; };

	void SetSelectFlag(bool selectFlag) { m_SelectFlag = selectFlag; }
	bool GetSelectFlag() {
		return m_SelectFlag
			;
	}
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ISelectPlayScene();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize(StageSelect* stageSelect, StageSelectScene* stageSelectScene);

	/// <summary>
	/// 処理を実行する
	/// </summary>
	/// <param name="elapsedTime">選択時間</param>
	virtual void Update(const bool& selectFlag,const bool& selectStartFlag) = 0;

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render() = 0;

	/// <summary>
	/// 後始末をする
	/// </summary>
	virtual void Finalize() = 0;

	/// <summary>
	/// 仮想デストラクタ
	/// </summary>
	virtual ~ISelectPlayScene() = default;

private:
	StageSelect* m_pStageSelect;
	StageSelectScene* m_pStageSelectScene;

	bool m_SelectFlag;
};
