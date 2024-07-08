/**
 * @file    FiniteStateMachine.h
 * @brief   有限ステートマシン関連のヘッダファイル
 * @author  S.Takaki
 * @date    2023/11/09
 */
#pragma once



//-----------------------------------------------------------------------------
// ヘッダファイルの読み込み
//-----------------------------------------------------------------------------
#include <cassert>
#include <unordered_map>


	/**
	 * @brief 有限ステートマシンクラス
	 */
	template<typename Owner, typename StateID>
	class FiniteStateMachine final
	{
		// 内部クラス
		public:
			class IState;    //!< ステート


		// エイリアス宣言
		protected:
			using StateTable = std::unordered_map<StateID, IState*>;


		// メンバ変数
		private:
			Owner*     m_owner;           //!< 所有者
			StateTable m_stateTable;      //!< 登録ステート
		    IState*    m_currentState;    //!< 現在のステート
		    IState*    m_nextState;       //!< 遷移先のステート


		// コンストラクタ / デストラクタ
		public:
			// コンストラクタ
			FiniteStateMachine(Owner* owner);

			// デストラクタ
			~FiniteStateMachine();


		// 操作
		public:
			// ステートの登録
			void RegisterState(StateID stateID, IState* state);

			// ステートマシンの起動
			void Start(StateID initialStateID);

			// ステートマシンの停止
			void Stop();

			// 遷移を要求
			void RequestTransition(StateID nextStateID);

			// 更新
			void Initialize();
			void Update(const float& elapsedTime);
			void Render();
			void Finalize();


		// 取得／設定
		public:
			Owner* GetOwner() const { return m_owner; }


		// 内部実装
		private:
			// ステートの遷移
			void Transition();
			void Transition(IState* state);

			// 状態が登録されているかどうか
			bool ExistsState(StateID stateID);
	};




//-----------------------------------------------------------------------------
// 内部クラス定義
//-----------------------------------------------------------------------------
	/**
	 * @brief ステートのインタフェース
	 */
	template<typename Owner, typename StateID>
	class FiniteStateMachine<Owner, StateID>::IState
	{
		// コンストラクタ／デストラクタ
		public:
			// デストラクタ
			virtual ~IState() = default;


		// 操作
		public:
			virtual void Initialize() = 0;
			virtual void Update( const float& elapsedTime) = 0;
			virtual void Render() = 0;
			virtual void Finalize() = 0;

			virtual void Enter() = 0;
			virtual void Exit() = 0;

			// デバイスに依存するリソースを作成する関数
			virtual void CreateDeviceDependentResources() = 0;

	};



	//=========================================================================
	// FiniteStateMachine
	//=========================================================================
	/**
	 * @brief コンストラクタ
	 *
	 * @param[in] owner 所有者
	 */
	template<typename Owner, typename StateID>
	FiniteStateMachine<Owner, StateID>::FiniteStateMachine(Owner* owner)
		: m_owner{ owner }
		, m_stateTable{}
		, m_currentState{ nullptr }
		, m_nextState{ nullptr }
	{
	}



	/**
	 * @brief デストラクタ
	 */
	template<typename Owner, typename StateID>
	FiniteStateMachine<Owner, StateID>::~FiniteStateMachine()
	{
	}



	/**
	 * @brief ステートの登録
	 *
	 * @param[in] stateID ステートID
	 * @param[in] state   ステート
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::RegisterState(StateID stateID, IState* state)
	{
		assert(!ExistsState(stateID) && "ステートは登録済みです");
		assert(!m_currentState && "FSMは起動中です");


		// 新規ステートとして登録
		m_stateTable.emplace(stateID, state);
	}



	/**
	 * @brief ステートマシンの起動
	 *
	 * @param[in] initialStateID 開始ステートID
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Start(StateID initialStateID)
	{
		assert(ExistsState(initialStateID) && "開始ステートは未登録です");


		//　開始ステートへ遷移
		Transition(m_stateTable.at(initialStateID));
	}



	/**
	 * @brief ステートマシンの停止
	 *
	 * @param なし
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Stop()
	{
		assert(m_currentState && "現在のステートが存在していません");

		Transition(nullptr);
	}



	/**
	 * @brief 遷移の要求
	 *
	 * @param[in] nextStateID 遷移先のステートID
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::RequestTransition(StateID nextStateID)
	{
		assert(ExistsState(nextStateID) && "遷移先のステートは未登録です");


		// 遷移先ステートの設定
		m_nextState = m_stateTable.at(nextStateID);
	}



	/**
	 * @brief ステートマシンの更新
	 *
	 * @param[in] elapsedTime 経過時間
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Initialize()
	{
		assert(m_currentState && "現在のステートが存在していません");

		// ステートの実行
		m_currentState->Initialize();
	}
	/**
	 * @brief ステートマシンの更新
	 *
	 * @param[in] elapsedTime 経過時間
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Update(const float& elapsedTime)
	{
		assert(m_currentState && "現在のステートが存在していません");


		// 遷移が必要な場合
		if (m_nextState)
		{
			Transition();
		}

		// ステートの実行
		m_currentState->Update(elapsedTime);
	}
	/**
	 * @brief ステートマシンの更新
	 *
	 * @param[in] elapsedTime 経過時間
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Render()
	{
		assert(m_currentState && "現在のステートが存在していません");

		// ステートの実行
		m_currentState->Render();
	}
	/**
	 * @brief ステートマシンの更新
	 *
	 * @param[in] elapsedTime 経過時間
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Finalize()
	{
		assert(m_currentState && "現在のステートが存在していません");

		// ステートの実行
		m_currentState->Finalize();
	}



	/**
	 * @brief 次のステートに遷移する
	 *
	 * @param なし
	 *
	 * @return なし
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Transition()
	{
		// 現在のステートの退場時アクション
		if (m_currentState)
		{
			m_currentState->Exit();
		}


		// 遷移先のステートの入場時アクション
		if (m_nextState)
		{
			m_nextState->Enter();
		}


		// 状態遷移
		m_currentState = m_nextState;
		m_nextState    = nullptr;
	}



	/**
	 * @brief 指定ステートに遷移する
	 *
	 * @param[in] state 遷移先のステート
	 *
	 * @return なし
	 */

	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Transition(IState* state)
	{
		m_nextState = state;
		Transition();
	}



	/**
	 * @brief ステートが登録されているかどうか
	 *
	 * @param[in] stateID 検索対象のステートID
	 *
	 * @retval true  登録済み
	 * @retval false 未登録
	 */
	template<typename Owner, typename StateID>
	bool FiniteStateMachine<Owner, StateID>::ExistsState(StateID stateID)
	{
		return m_stateTable.count(stateID) > 0;
	}
