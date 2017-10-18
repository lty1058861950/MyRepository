#pragma once


// CCellCombo

class CCellCombo : public CComboBox
{
	DECLARE_DYNAMIC(CCellCombo)

public:
	CCellCombo();
	virtual ~CCellCombo();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


