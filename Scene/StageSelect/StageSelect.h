#pragma once

#include"ISelectPlayScene.h"
#include"Scene/GameObjects/Background/Background.h"
class StageSelectScene;
#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// 星の種類（順番になる）
/// </summary>
const enum Planet
{
	TUTORIAL,
	TOWN,
	//GRAND_CANYON,
	COUNT,
};

/// <summary>
/// StageSelectのクラスを定義する
/// </summary>
class StageSelect
{
public:
	//選択している番号のゲッター、セッター
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	//ステージの横幅
	static const int WIDTH = 5;

	//背景の惑星
	virtual std::unique_ptr<Background>* GetBackground() { return m_background; }
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~StageSelect();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(StageSelectScene* stageSelectScene);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& selectStartFlag, const bool& retuneSelectStartFlag);

	/// <summary>
	/// 描画する
	/// </summary>
	void Render();

	/// <summary>
	/// 後始末
	/// </summary>
	void Finalize();

	/// <summary>
	/// デバイスに依存するリソースを作成する関数
	/// </summary>
	void CreateDeviceDependentResources();

private:
	//状態のポインタ
	std::unique_ptr<ISelectPlayScene> m_select[Planet::COUNT];

	// 現在の状態のポインタ
	ISelectPlayScene* m_pCurrentState;

	//ホームの文字の当たり判定
	std::unique_ptr <Collider::Box2D> m_Collision[2];


	//選択している番号
	int m_selectNum;

private:
	//背景の惑星
	std::unique_ptr <Background> m_background[COUNT];

	//背景の大きさ
	const int SCALE = 1000;
private:
	//ゲージとベースのポインタ
	std::unique_ptr<tito::MoveUserInterface> m_HorizontalTriangle[2];
	std::unique_ptr<Collider::Box2D> m_HorizontalTrianglecol[2];
	bool m_flag[2];

};

