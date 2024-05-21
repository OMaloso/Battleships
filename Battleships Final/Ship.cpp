/***********************************************************************

File Name : Ship.cpp
Description : Ship cpp

**************************************************************************/

#include "Ship.h"
#include <string>


//default constructor
CShip::CShip()
{
	m_sName = "Default Ship";
	m_cLetterId = 'Z';
	m_iSize = 0;
	m_iPlayerHealth = 0;
	m_iEnemyHealth = 0;
	m_bPlacement = false;
}

CShip::CShip(std::string _sName, char _cLetterId, int _iSize, int _iPlayerHealth, int _iEnemyHealth, bool _bPlacement)
{
	m_sName = _sName;
	m_cLetterId = _cLetterId;
	m_iSize = _iSize;
	m_iPlayerHealth = _iPlayerHealth;
	m_iEnemyHealth = _iEnemyHealth;
	m_bPlacement = _bPlacement;
}

//destructor
CShip::~CShip()
{}

CShip::CShip(const CShip& std) // TF: Copy Constructor     // TF: Reference
{
	m_sName = std.GetName();
	m_cLetterId = std.GetLetterId();
	m_iSize = std.GetSize();
	m_iPlayerHealth = std.GetPlayerHealth();
	m_iEnemyHealth = std.GetEnemyHealth();
	m_bPlacement = false;
}

//Ship name
void CShip::SetName(std::string _sName)
{
	m_sName = _sName;
}
std::string CShip::GetName() const
{
	return m_sName;
}

//Ship letter Id
void CShip::SetLetterId(char _cLetterId)
{
	m_cLetterId = _cLetterId;
}
char CShip::GetLetterId() const
{
	return m_cLetterId;
}

//Ship size
void CShip::SetSize(int _iSize)
{
	m_iSize = _iSize;
}
int CShip::GetSize() const
{
	return m_iSize;
}

//Player Ship health
void CShip::SetPlayerHealth(int _iPlayerHealth)
{
	m_iPlayerHealth = _iPlayerHealth;
}
int CShip::GetPlayerHealth() const
{
	return m_iPlayerHealth;
}

//AI Ship health
void CShip::SetEnemyHealth(int _iEnemyHealth)
{
	m_iEnemyHealth = _iEnemyHealth;
}
int CShip::GetEnemyHealth() const
{
	return m_iEnemyHealth;
}

//checking whether it has been placed
void CShip::SetPlacement(bool _bPlacement = false) // TF: Default Parameter
{
	m_bPlacement = _bPlacement;
}
bool CShip::GetPlacement() const
{
	return m_bPlacement;
}

