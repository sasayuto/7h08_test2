#pragma 
#include <combaseapi.h>

class StatePlaySceneCamera;
class PlaySceneCamera;
/// <summary>
/// IStatePlayerFactory�C���^�[�t�F�C�X�̃N���X���`����
/// </summary>
interface IPlayerCameraFactory
{
	/// <summary>
	/// �ʏ�̃J�����𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�ʏ�̃J�����̃|�C���^</returns>
	virtual std::unique_ptr<StatePlaySceneCamera> CreateNormalCamera(
		const PlaySceneCamera* parent
	) = 0;

	/// <summary>
	/// �f�X�̃J�����𐶐�
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <returns>�f�X�̃J�����̃|�C���^</returns>
	virtual std::unique_ptr<StatePlaySceneCamera> CreateDeathCamera(
		const PlaySceneCamera* parent
	) = 0;

};

