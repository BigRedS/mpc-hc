/*
 * (C) 2014-2015 see Authors.txt
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
#include "CmdLineHelpDlg.h"

CmdLineHelpDlg::CmdLineHelpDlg(const CString& cmdLine /*= _T("")*/)
    : CMPCDialog(CmdLineHelpDlg::IDD)
    , m_cmdLine(cmdLine)
{
}

CmdLineHelpDlg::~CmdLineHelpDlg()
{
}

void CmdLineHelpDlg::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC1, m_icon);
    DDX_Text(pDX, IDC_EDIT1, m_text);
}


BEGIN_MESSAGE_MAP(CmdLineHelpDlg, CMPCDialog)
END_MESSAGE_MAP()

BOOL CmdLineHelpDlg::OnInitDialog()
{
    __super::OnInitDialog();

    m_icon.SetIcon(LoadIcon(nullptr, IDI_INFORMATION));

    if (!m_cmdLine.IsEmpty()) {
        m_text = ResStr(IDS_UNKNOWN_SWITCH);
        m_text.AppendFormat(_T("%s\n\n"), m_cmdLine);
    }
    m_text.Append(ResStr(IDS_USAGE));
    m_text.Replace(_T("\n"), _T("\r\n"));

    UpdateData(FALSE);

    GetDlgItem(IDOK)->SetFocus(); // Force the focus on the OK button

    EnableSaveRestore(IDS_R_DLG_CMD_LINE_HELP);

    return FALSE;
}
