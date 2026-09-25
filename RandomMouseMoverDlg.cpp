#include "pch.h"
#include "framework.h"
#include "RandomMouseMover.h"
#include "RandomMouseMoverDlg.h"

#include <windows.h>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRandomMouseMoverDlg::CRandomMouseMoverDlg(CWnd* pParent)
    : CDialogEx(IDD_RANDOMMOUSEMOVER_DIALOG, pParent)
{
}

void CRandomMouseMoverDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRandomMouseMoverDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ON, &CRandomMouseMoverDlg::OnBnClickedButtonOn)
    ON_BN_CLICKED(IDC_BUTTON_OFF, &CRandomMouseMoverDlg::OnBnClickedButtonOff)
    ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CRandomMouseMoverDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    UpdateStatus(_T("Status: Off"));
    GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(FALSE);

    return TRUE;
}

void CRandomMouseMoverDlg::StartMover()
{
    if (m_isRunning)
        return;

    m_isRunning = true;
    SetDisplayAwake(true);

    // Move once immediately, then continue every 30 seconds.
    MoveMouseRandomly();
    SetTimer(TIMER_MOUSE_MOVE, m_intervalMs, nullptr);

    GetDlgItem(IDC_BUTTON_ON)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(TRUE);
    UpdateStatus(_T("Status: On"));
}

void CRandomMouseMoverDlg::StopMover()
{
    if (!m_isRunning)
        return;

    KillTimer(TIMER_MOUSE_MOVE);
    m_isRunning = false;
    SetDisplayAwake(false);

    GetDlgItem(IDC_BUTTON_ON)->EnableWindow(TRUE);
    GetDlgItem(IDC_BUTTON_OFF)->EnableWindow(FALSE);
    UpdateStatus(_T("Status: Off"));
}

void CRandomMouseMoverDlg::SetDisplayAwake(bool awake)
{
    if (awake)
    {
        // Keep the system and display awake while the mover is active.
        SetThreadExecutionState(
            ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_DISPLAY_REQUIRED);
    }
    else
    {
        // Remove the application's keep-awake request.
        SetThreadExecutionState(ES_CONTINUOUS);
    }
}

void CRandomMouseMoverDlg::MoveMouseRandomly()
{
    RECT workArea{};
    if (!SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0))
        return;

    const int width = workArea.right - workArea.left;
    const int height = workArea.bottom - workArea.top;

    if (width <= 0 || height <= 0)
        return;

    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::uniform_int_distribution<int> xDistribution(
        workArea.left, workArea.right - 1);

    std::uniform_int_distribution<int> yDistribution(
        workArea.top, workArea.bottom - 1);

    const int x = xDistribution(generator);
    const int y = yDistribution(generator);

    SetCursorPos(x, y);
}

void CRandomMouseMoverDlg::UpdateStatus(LPCTSTR text)
{
    CWnd* status = GetDlgItem(IDC_STATIC_STATUS);
    if (status != nullptr)
        status->SetWindowText(text);
}

void CRandomMouseMoverDlg::OnBnClickedButtonOn()
{
    StartMover();
}

void CRandomMouseMoverDlg::OnBnClickedButtonOff()
{
    StopMover();
}

void CRandomMouseMoverDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == TIMER_MOUSE_MOVE && m_isRunning)
        MoveMouseRandomly();

    CDialogEx::OnTimer(nIDEvent);
}

void CRandomMouseMoverDlg::OnCancel()
{
    StopMover();
    CDialogEx::OnCancel();
}
