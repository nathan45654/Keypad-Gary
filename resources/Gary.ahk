#Requires AutoHotkey v2.0

ActivateOrLaunch(exeName, launchPath)
{
    hwnd := WinExist("ahk_exe " exeName)

    if hwnd
    {
        WinActivate(hwnd)
    }
    else
    {
        Run(launchPath)
    }
}


F14::Send "This is a custom macro triggered by F14."
F15::Run "notepad.exe"

orca_exe := "orca-slicer.exe"
orca_path := "C:\Program Files\OrcaSlicer\" orca_exe
^F16::
{
    ActivateOrLaunch(
        orca_exe,
        orca_path
    )
}

F13::MsgBox("F13")
+F13::MsgBox("Shift+F13")
^F13::MsgBox("Ctrl+F13")
