/*
* (C) 2015 see Authors.txt
*
* This file is part of MPC-HC.
*
* MPC-HC is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* MPC-HC is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/


#pragma once

#include "../CmdUI/CmdUI.h"

class CMPCDialog : public CCmdUIDialog
{
public:
    static constexpr int UNLIMITED = -1;

    CMPCDialog(UINT nIDTemplate, CWnd* pParent = nullptr);
    virtual ~CMPCDialog() = default;

    void EnableSaveRestore(LPCTSTR pszSection);
    void SetMaxTrackSize(int cx, int cy);

private:
    bool m_bEnableSaveRestore = false;
    CPoint m_minTrackSize;
    CPoint m_maxTrackSize = { UNLIMITED, UNLIMITED };

    CString m_settingsSection;
    bool SaveWindowRect() const;
    bool LoadWindowRect();

protected:
    virtual void DoDataExchange(CDataExchange* pDX) override;

    DECLARE_MESSAGE_MAP()

    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
