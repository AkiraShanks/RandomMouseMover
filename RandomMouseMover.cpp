#include <afxwin.h>
#include <windows.h>
#include <random>
#include "resource.h"
#define ID_TIMER_MOVE 1001
class CMainDlg : public CDialogEx {
public: CMainDlg() : CDialogEx(IDD_MAIN), running(false) {}
protected: bool running;
void Awake(bool on) { SetThreadExecutionState(on ? (ES_CONTINUOUS|ES_SYSTEM_REQUIRED|ES_DISPLAY_REQUIRED) : ES_CONTINUOUS); }
void MoveRandomly() { RECT r{}; if (!SystemParametersInfoW(SPI_GETWORKAREA,0,&r,0)) return; static std::mt19937 g{std::random_device{}()}; std::uniform_int_distribution<int>x(r.left,r.right-1),y(r.top,r.bottom-1); SetCursorPos(x(g),y(g)); }
void Start() { if(running)return; running=true; Awake(true); MoveRandomly(); SetTimer(ID_TIMER_MOVE,30000,nullptr); }
void Stop() { if(!running)return; KillTimer(ID_TIMER_MOVE); running=false; Awake(false); }
afx_msg void OnTimer(UINT_PTR id){if(id==ID_TIMER_MOVE&&running)MoveRandomly(); CDialogEx::OnTimer(id);}
afx_msg void OnOn(){Start();} afx_msg void OnOff(){Stop();}
void OnCancel() override {Stop(); CDialogEx::OnCancel();} DECLARE_MESSAGE_MAP()
};
BEGIN_MESSAGE_MAP(CMainDlg,CDialogEx)
ON_WM_TIMER() ON_COMMAND(ID_BUTTON_ON,&CMainDlg::OnOn) ON_COMMAND(ID_BUTTON_OFF,&CMainDlg::OnOff)
END_MESSAGE_MAP()
class CApp:public CWinApp{public:BOOL InitInstance() override{CWinApp::InitInstance();CMainDlg d;m_pMainWnd=&d;d.DoModal();return FALSE;}}; CApp theApp;
