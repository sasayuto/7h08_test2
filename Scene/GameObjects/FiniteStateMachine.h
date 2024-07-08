/**
 * @file    FiniteStateMachine.h
 * @brief   �L���X�e�[�g�}�V���֘A�̃w�b�_�t�@�C��
 * @author  S.Takaki
 * @date    2023/11/09
 */
#pragma once



//-----------------------------------------------------------------------------
// �w�b�_�t�@�C���̓ǂݍ���
//-----------------------------------------------------------------------------
#include <cassert>
#include <unordered_map>


	/**
	 * @brief �L���X�e�[�g�}�V���N���X
	 */
	template<typename Owner, typename StateID>
	class FiniteStateMachine final
	{
		// �����N���X
		public:
			class IState;    //!< �X�e�[�g


		// �G�C���A�X�錾
		protected:
			using StateTable = std::unordered_map<StateID, IState*>;


		// �����o�ϐ�
		private:
			Owner*     m_owner;           //!< ���L��
			StateTable m_stateTable;      //!< �o�^�X�e�[�g
		    IState*    m_currentState;    //!< ���݂̃X�e�[�g
		    IState*    m_nextState;       //!< �J�ڐ�̃X�e�[�g


		// �R���X�g���N�^ / �f�X�g���N�^
		public:
			// �R���X�g���N�^
			FiniteStateMachine(Owner* owner);

			// �f�X�g���N�^
			~FiniteStateMachine();


		// ����
		public:
			// �X�e�[�g�̓o�^
			void RegisterState(StateID stateID, IState* state);

			// �X�e�[�g�}�V���̋N��
			void Start(StateID initialStateID);

			// �X�e�[�g�}�V���̒�~
			void Stop();

			// �J�ڂ�v��
			void RequestTransition(StateID nextStateID);

			// �X�V
			void Initialize();
			void Update(const float& elapsedTime);
			void Render();
			void Finalize();


		// �擾�^�ݒ�
		public:
			Owner* GetOwner() const { return m_owner; }


		// ��������
		private:
			// �X�e�[�g�̑J��
			void Transition();
			void Transition(IState* state);

			// ��Ԃ��o�^����Ă��邩�ǂ���
			bool ExistsState(StateID stateID);
	};




//-----------------------------------------------------------------------------
// �����N���X��`
//-----------------------------------------------------------------------------
	/**
	 * @brief �X�e�[�g�̃C���^�t�F�[�X
	 */
	template<typename Owner, typename StateID>
	class FiniteStateMachine<Owner, StateID>::IState
	{
		// �R���X�g���N�^�^�f�X�g���N�^
		public:
			// �f�X�g���N�^
			virtual ~IState() = default;


		// ����
		public:
			virtual void Initialize() = 0;
			virtual void Update( const float& elapsedTime) = 0;
			virtual void Render() = 0;
			virtual void Finalize() = 0;

			virtual void Enter() = 0;
			virtual void Exit() = 0;

			// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
			virtual void CreateDeviceDependentResources() = 0;

	};



	//=========================================================================
	// FiniteStateMachine
	//=========================================================================
	/**
	 * @brief �R���X�g���N�^
	 *
	 * @param[in] owner ���L��
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
	 * @brief �f�X�g���N�^
	 */
	template<typename Owner, typename StateID>
	FiniteStateMachine<Owner, StateID>::~FiniteStateMachine()
	{
	}



	/**
	 * @brief �X�e�[�g�̓o�^
	 *
	 * @param[in] stateID �X�e�[�gID
	 * @param[in] state   �X�e�[�g
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::RegisterState(StateID stateID, IState* state)
	{
		assert(!ExistsState(stateID) && "�X�e�[�g�͓o�^�ς݂ł�");
		assert(!m_currentState && "FSM�͋N�����ł�");


		// �V�K�X�e�[�g�Ƃ��ēo�^
		m_stateTable.emplace(stateID, state);
	}



	/**
	 * @brief �X�e�[�g�}�V���̋N��
	 *
	 * @param[in] initialStateID �J�n�X�e�[�gID
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Start(StateID initialStateID)
	{
		assert(ExistsState(initialStateID) && "�J�n�X�e�[�g�͖��o�^�ł�");


		//�@�J�n�X�e�[�g�֑J��
		Transition(m_stateTable.at(initialStateID));
	}



	/**
	 * @brief �X�e�[�g�}�V���̒�~
	 *
	 * @param �Ȃ�
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Stop()
	{
		assert(m_currentState && "���݂̃X�e�[�g�����݂��Ă��܂���");

		Transition(nullptr);
	}



	/**
	 * @brief �J�ڂ̗v��
	 *
	 * @param[in] nextStateID �J�ڐ�̃X�e�[�gID
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::RequestTransition(StateID nextStateID)
	{
		assert(ExistsState(nextStateID) && "�J�ڐ�̃X�e�[�g�͖��o�^�ł�");


		// �J�ڐ�X�e�[�g�̐ݒ�
		m_nextState = m_stateTable.at(nextStateID);
	}



	/**
	 * @brief �X�e�[�g�}�V���̍X�V
	 *
	 * @param[in] elapsedTime �o�ߎ���
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Initialize()
	{
		assert(m_currentState && "���݂̃X�e�[�g�����݂��Ă��܂���");

		// �X�e�[�g�̎��s
		m_currentState->Initialize();
	}
	/**
	 * @brief �X�e�[�g�}�V���̍X�V
	 *
	 * @param[in] elapsedTime �o�ߎ���
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Update(const float& elapsedTime)
	{
		assert(m_currentState && "���݂̃X�e�[�g�����݂��Ă��܂���");


		// �J�ڂ��K�v�ȏꍇ
		if (m_nextState)
		{
			Transition();
		}

		// �X�e�[�g�̎��s
		m_currentState->Update(elapsedTime);
	}
	/**
	 * @brief �X�e�[�g�}�V���̍X�V
	 *
	 * @param[in] elapsedTime �o�ߎ���
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Render()
	{
		assert(m_currentState && "���݂̃X�e�[�g�����݂��Ă��܂���");

		// �X�e�[�g�̎��s
		m_currentState->Render();
	}
	/**
	 * @brief �X�e�[�g�}�V���̍X�V
	 *
	 * @param[in] elapsedTime �o�ߎ���
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Finalize()
	{
		assert(m_currentState && "���݂̃X�e�[�g�����݂��Ă��܂���");

		// �X�e�[�g�̎��s
		m_currentState->Finalize();
	}



	/**
	 * @brief ���̃X�e�[�g�ɑJ�ڂ���
	 *
	 * @param �Ȃ�
	 *
	 * @return �Ȃ�
	 */
	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Transition()
	{
		// ���݂̃X�e�[�g�̑ޏꎞ�A�N�V����
		if (m_currentState)
		{
			m_currentState->Exit();
		}


		// �J�ڐ�̃X�e�[�g�̓��ꎞ�A�N�V����
		if (m_nextState)
		{
			m_nextState->Enter();
		}


		// ��ԑJ��
		m_currentState = m_nextState;
		m_nextState    = nullptr;
	}



	/**
	 * @brief �w��X�e�[�g�ɑJ�ڂ���
	 *
	 * @param[in] state �J�ڐ�̃X�e�[�g
	 *
	 * @return �Ȃ�
	 */

	template<typename Owner, typename StateID>
	void FiniteStateMachine<Owner, StateID>::Transition(IState* state)
	{
		m_nextState = state;
		Transition();
	}



	/**
	 * @brief �X�e�[�g���o�^����Ă��邩�ǂ���
	 *
	 * @param[in] stateID �����Ώۂ̃X�e�[�gID
	 *
	 * @retval true  �o�^�ς�
	 * @retval false ���o�^
	 */
	template<typename Owner, typename StateID>
	bool FiniteStateMachine<Owner, StateID>::ExistsState(StateID stateID)
	{
		return m_stateTable.count(stateID) > 0;
	}
