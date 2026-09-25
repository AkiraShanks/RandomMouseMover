# Random Mouse Mover - MFC

A Windows 10 dialog-based MFC application that:
- Starts/stops random mouse movement.
- Requests that Windows keep the display awake while enabled.
- Uses a 30-second movement interval.
- Uses the primary monitor work area.

## Build
1. Install Visual Studio 2022 with **Desktop development with C++** and **MFC/ATL support**.
2. Create a new **MFC App** project named `RandomMouseMover`.
3. Choose **Dialog based**.
4. Replace the generated dialog header/source content with the logic from `RandomMouseMoverDlg.h` and `RandomMouseMoverDlg.cpp`.
5. Add two buttons to the dialog:
   - Button ID: `IDC_BUTTON_ON`, text: `Turn On`
   - Button ID: `IDC_BUTTON_OFF`, text: `Turn Off`
6. Add a static text control with ID `IDC_STATIC_STATUS`.
7. Connect the button handlers as shown in the source file.

The app intentionally does not hide itself or run automatically at startup.
