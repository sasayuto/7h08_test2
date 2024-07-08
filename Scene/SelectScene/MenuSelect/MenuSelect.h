#pragma once
#include"StateManuScene/StateMenuScene.h"

class TitleScene;

/// <summary>
/// メニュー画面の種類（順番になる）
/// </summary>
const enum Menu
{
	STAGE_SELECT,
	OPTION,
	TITLE,
	MENU_COUNT
};

/// <summary>
/// StageSelectのクラスを定義する
/// </summary>
class MenuSelect
{
public:
		//UIの縦幅
		static const int WIDTH = 90;


	//選択している番号のゲッター、セッター
	int GetSelectNum() const{ return m_selectNum; }
	void SetSelectNum(const int& selectNum) { m_selectNum = selectNum; }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MenuSelect();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MenuSelect();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="titleScene"></param>
	void Initialize(TitleScene* titleScene);

	/// <summary>
	/// 更新する
	/// </summary>
	/// <param name="selectFlag"></param>
	void Update(const bool& selectFlag, const bool& selectStartFlag);

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
	std::unique_ptr<StateMenuScene> m_select[Menu::MENU_COUNT];

	// 現在の状態のポインタ
	StateMenuScene* m_pCurrentState;

	//タイトルシーンのポインタ
	TitleScene* m_titleScene;

	//選択している番号
	int m_selectNum;
private:
	//背景の惑星
	std::unique_ptr <StageSelectLetter> m_object[Menu::MENU_COUNT];

	//回る惑星
	std::unique_ptr <UnderBar> m_underBar;
	MenuSelect* m_pMenuSelect;



};

