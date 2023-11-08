#include "stdafx.h"
#include "State_Character_Damaged_AirBorn.h"
#include "GameInstance.h"
#include "Model.h"
#include "Character.h"
#include "RigidBody.h"


CState_Character_Damaged_AirBorn::CState_Character_Damaged_AirBorn(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CStateMachine* pStateMachine)
	: CState(pStateMachine)
{

}

HRESULT CState_Character_Damaged_AirBorn::Initialize(const list<wstring>& AnimationList)
{
	m_pModelCom = m_pStateMachineCom->Get_Owner()->Get_Component<CModel>(L"Com_Model");
	if (nullptr == m_pModelCom)
		return E_FAIL;


	m_pTransformCom = m_pStateMachineCom->Get_Owner()->Get_Component<CTransform>(L"Com_Transform");
	if (nullptr == m_pTransformCom)
		return E_FAIL;

	m_pRigidBodyCom = m_pStateMachineCom->Get_Owner()->Get_Component<CRigidBody>(L"Com_RigidBody");
	if (nullptr == m_pRigidBodyCom)
		return E_FAIL;

	m_pOwnerCharacter = dynamic_cast<CCharacter*>(m_pStateMachineCom->Get_Owner());
	if (nullptr == m_pOwnerCharacter)
		return E_FAIL;

	Safe_AddRef(m_pOwnerCharacter);
	Safe_AddRef(m_pRigidBodyCom);
	Safe_AddRef(m_pModelCom);
	Safe_AddRef(m_pTransformCom);

	for (auto strAnimName : AnimationList)
	{
		_int iAnimIndex = m_pModelCom->Find_AnimationIndex(strAnimName);
		if (-1 != iAnimIndex)
			m_AnimationIndices.push_back(iAnimIndex);
		else		
			return E_FAIL;
	}
	
	return S_OK;
}

void CState_Character_Damaged_AirBorn::Enter_State(void* pArg)
{
	m_iCurrAnimIndex = 0;
	m_fAccRecovery = 0.f;
	m_pModelCom->Set_AnimIndex(m_AnimationIndices[m_iCurrAnimIndex]);
	m_pStateMachineCom->Get_Owner()->Set_ActiveColliders(CCollider::DETECTION_TYPE::ATTACK, false);
	
	_vector vPosition = XMVectorSetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION), XMVectorGetY(m_pTransformCom->Get_State(CTransform::STATE_POSITION)) + .5f);
	m_pTransformCom->Set_State(CTransform::STATE_POSITION, vPosition);
	m_pRigidBodyCom->Set_Ground(false);
	_vector vUp = m_pTransformCom->Get_State(CTransform::STATE_UP);
	_vector vAirBornDir = (vUp);
	m_pRigidBodyCom->Add_Velocity(XMVector3Normalize(vAirBornDir), 4.5f);
}

void CState_Character_Damaged_AirBorn::Tick_State(_float fTimeDelta)
{
	if (m_pModelCom->Is_Animation_Finished(m_AnimationIndices[0]))
	{
		m_pModelCom->Set_AnimIndex(m_AnimationIndices[1]);
	}

	if (m_pRigidBodyCom->Is_Ground())
	{
		if (!m_bFirstGround)
		{
			m_bFirstGround = true;
			m_pModelCom->Set_AnimIndex(m_AnimationIndices[2]);
		}
			
		m_fAccRecovery += fTimeDelta;
		if(m_fAccRecovery >= m_fRecoveryTime)
		{
			m_pStateMachineCom->Change_State(CCharacter::BATTLE_IDLE);
		}
	}
}

void CState_Character_Damaged_AirBorn::Exit_State()
{
	m_iCurrAnimIndex = 0;
	m_fAccRecovery = 0.f;
	m_bFirstGround = false;

	m_pStateMachineCom->Get_Owner()->Set_ActiveColliders(CCollider::DETECTION_TYPE::ATTACK, false);
	m_pOwnerCharacter->Set_Infinite(0.5f, false);
}

CState_Character_Damaged_AirBorn* CState_Character_Damaged_AirBorn::Create(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, CStateMachine* pStateMachine,const list<wstring>& AnimationList)
{
	CState_Character_Damaged_AirBorn* pInstance =  new CState_Character_Damaged_AirBorn(pDevice, pContext, pStateMachine);
	if (FAILED(pInstance->Initialize(AnimationList)))
	{
		Safe_Release(pInstance);
		MSG_BOX("Failed Create : CState_Character_Damaged_AirBorn");
		return nullptr;
	}
		
	return pInstance;
}

void CState_Character_Damaged_AirBorn::Free()
{
	__super::Free();
	Safe_Release(m_pRigidBodyCom);
	Safe_Release(m_pOwnerCharacter);
}
