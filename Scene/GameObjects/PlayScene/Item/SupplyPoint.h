#pragma once
#include"Item.h"
class SupplyPoint : public Item
{
private:

	//�G�̃|�W�V����
	int m_replenishmentFuel;
public:		


public:
	SupplyPoint();
	~SupplyPoint();


	void Initialize() override;

	//�J�����̃|�W�V����
	void Update() override;

	void Recovery(Player* player) override;


	//
	//void CreateDeviceDependentResources(ID3D11Device1* device, wchar_t const* fileName);



};
