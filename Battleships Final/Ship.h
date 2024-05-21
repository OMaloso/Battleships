/***********************************************************************

File Name : Ship.h
Description : Ship header file

**************************************************************************/

#pragma once

#include <string>


#ifndef __SHIP_H
#define __SHIP_H

class CShip  // TF: Class
{

public: // TF: Access Specifier
	CShip();  // TF: Default Constructor
	CShip(std::string _sName, char _cLetterId, int _iSize, int _iPlayerHealth, int _iEnemyHealth, bool _bPlacement = false);
	~CShip(); // TF: Destructor

	CShip(const CShip& std); // TF: Copy Constructor

	void SetName(std::string _sName);
	std::string GetName() const; // TF: Constant

	void SetLetterId(char _cLetterId);
	char GetLetterId() const;

	void SetSize(int _iSize);
	int GetSize() const;

	void SetPlayerHealth(int _iPlayerHealth);
	int GetPlayerHealth() const;

	void SetEnemyHealth(int _iEnemyHealth);
	int GetEnemyHealth() const;

	void SetPlacement(bool _bPlacement);
	bool GetPlacement() const;

private: // TF: Access Specifier
	std::string m_sName;
	char m_cLetterId;
	int m_iSize;
	int m_iPlayerHealth;
	int m_iEnemyHealth;
	bool m_bPlacement;
};

#endif // !__SHIP_H