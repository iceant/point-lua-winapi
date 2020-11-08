local winapi = require('winapi');
local CS_HREDRAW = 0x0002
local CS_VREDRAW = 0x0001
local IDI_APPLICATION = 32512
local IDC_ARROW=32512
local COLOR_WINDOW=5
local WS_OVERLAPPEDWINDOW=13565952
local SW_NORMAL=1
local WM_DESTROY=0x0002
local style =  CS_HREDRAW|CS_VREDRAW
print("CS_HREDRAW|CS_VREDRAW", style)

winapi.RegisterClass{
    style=style,
    lpfnWndProc=function(hwnd, msg, wParam, lParam)
        if(msg==WM_DESTROY) then
            winapi.PostQuitMessage(0)
        end
    end,
    cbClsExtra=0,
    cbWndExtra=0,
    hInstance=winapi.GetModuleHandle(),
    hIcon=winapi.LoadIcon(nil, IDI_APPLICATION),
    hCursor=winapi.LoadCursor(nil, IDC_ARROW),
    hbrBackground=(COLOR_WINDOW+1),
    lpszClassName="test-window"
}

local hwnd = winapi.CreateWindow({
    lpClassName="test-window",
    lpWindowName="Test",
    dwStyle=WS_OVERLAPPEDWINDOW,
    x=10,
    y=10,
    nWidth=400,
    nHeight=500,
    hInstance=winapi.GetModuleHandle(),
    lpParam=nil
})

winapi.ShowWindow(hwnd, SW_NORMAL)
winapi.UpdateWindow(hwnd)

winapi.MessageLoop()

