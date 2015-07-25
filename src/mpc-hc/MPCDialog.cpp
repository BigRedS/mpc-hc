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


#include "stdafx.h"
#include "MPCDialog.h"

CMPCDialog::CMPCDialog(UINT nIDTemplate, CWnd* pParent /*= nullptr*/)
    : CCmdUIDialog(nIDTemplate, pParent)
{
}

void CMPCDialog::EnableSaveRestore(LPCTSTR pszSection)
{
    m_settingsSection = pszSection;
    LoadWindowRect();
}

void CMPCDialog::SetMaxTrackSize(int cx, int cy)
{
    m_maxTrackSize.SetPoint(cx, cy);
};


void CMPCDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

#define PLACEMENT_ENT   _T("WindowPlacement")
#define PLACEMENT_FMT   _T("%d,%d,%d,%d,%d,%d")

bool CMPCDialog::SaveWindowRect() const
{
    if (m_settingsSection.IsEmpty()) {
        return false;
    }

    CRect rc;
    GetWindowRect(&rc);

    CString data;
    data.Format(PLACEMENT_FMT, rc.left, rc.top, rc.right, rc.bottom, SW_NORMAL, 0);

    return !!AfxGetApp()->WriteProfileString(m_settingsSection, PLACEMENT_ENT, data);
}

bool CMPCDialog::LoadWindowRect()
{
    ASSERT(!m_settingsSection.IsEmpty());
    CString data = AfxGetApp()->GetProfileString(m_settingsSection, PLACEMENT_ENT);
    if (data.IsEmpty()) {
        return false;
    }

    CRect rc;
    // Read also two not used wp flags for backward compatibility
    WINDOWPLACEMENT wp;
    if (_stscanf_s(data, PLACEMENT_FMT, &rc.left, &rc.top,
                   &rc.right, &rc.bottom, &wp.showCmd, &wp.flags) != 6) {
        return false;
    }

    return !!SetWindowPos(nullptr, rc.left, rc.top, rc.Width(), rc.Height(),
                          SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOREPOSITION);
}

BEGIN_MESSAGE_MAP(CMPCDialog, CCmdUIDialog)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

int CMPCDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (__super::OnCreate(lpCreateStruct) == -1) {
        return -1;
    }

    if (GetStyle() & WS_CHILD) {
        return 0;
    }

    CRect rect;
    GetClientRect(&rect);

    ModifyStyle(DS_MODALFRAME, WS_POPUP | WS_THICKFRAME);
    AdjustWindowRectEx(&rect, GetStyle(), IsMenu(*GetMenu()), GetExStyle());
    SetWindowPos(nullptr, 0, 0, rect.Width(), rect.Height(), SWP_FRAMECHANGED |
                 SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOREPOSITION);

    // set the initial size as the min track size
    m_minTrackSize = rect.Size();

    // set the default size if specified, or not, I dunno yet.

    return 0;
}

void CMPCDialog::OnDestroy()
{
    SaveWindowRect();

    __super::OnDestroy();
}

void CMPCDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
    __super::OnGetMinMaxInfo(lpMMI);

    lpMMI->ptMinTrackSize = m_minTrackSize;

    if (m_maxTrackSize.x != UNLIMITED) {
        lpMMI->ptMaxTrackSize.x = m_maxTrackSize.x;
    }

    if (m_maxTrackSize.y != UNLIMITED) {
        lpMMI->ptMaxTrackSize.y = m_maxTrackSize.y;
    }
}
