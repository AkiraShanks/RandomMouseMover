#pragma once

#include <afxwin.h>

#define WM_APP_UPDATE_STATUS (WM_APP + 101)

class CRandomMouseMoverDlg : public CDialogEx
{
public:
    CRandomMouseMoverDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_RANDOMMOUSEMOVER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual void OnCancel();

    DECLARE_MESSAGE_MAP()

private:
    enum : UINT_PTR
    {
        TIMER_MOUSE_MOVE = 1
    };

    bool m_isRunning = false;
    UINT m_intervalMs = 30000;

    void StartMover();
    void StopMover();
    void MoveMouseRandomly();
    void UpdateStatus(LPCTSTR text);
    void SetDisplayAwake(bool awake);

    afx_msg void OnBnClickedButtonOn();
    afx_msg void OnBnClickedButtonOff();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};
