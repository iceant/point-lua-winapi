package.path= package.path..";".."../samples/?.lua"
local winapi = require('winapi')
require("print_table")

local CS_HREDRAW = 0x0002
local CS_VREDRAW = 0x0001
local IDI_APPLICATION = 32512
local IDC_ARROW=32512
local COLOR_WINDOW=5
local WS_OVERLAPPEDWINDOW=13565952
local SW_NORMAL=1
local WM_DESTROY=0x0002
local style =  CS_HREDRAW|CS_VREDRAW
local BSF_IGNORECURRENTTASK = 0x00000002
local BSM_APPLICATIONS = 0x00000008
local PM_MYMSG = 1
local WM_CREATE = 0x0001
local BSF_QUERY = 1
local WM_LBUTTONDOWN = 0x0201
local WM_LBUTTONUP = 0x0202
local WM_SYSKEYUP = 0x0105
local WM_SYSKEYDOWN = 0x0104
local WM_CHAR = 0x0102
local WM_PAINT = 0x000F

local function handleSysKey(hwnd, vk, fDown, cRepeat, flags)
    local str = ""
    if(fDown) then
        str = "WM_SYSKEYDOWN ==> "
    else
        str = "WM_SYSKEYUP ==> "
    end
    str= str.. "vk="..tostring(vk).." fDown="..tostring(fDown).." cRepeat="..cRepeat.." flags="..flags
    print(str)
end

winapi.RegisterClass{
    style=style,
    lpfnWndProc=function(hwnd, msg, wParam, lParam)
--        print(hwnd, msg, wParam, string.format("%x", lParam))
        if(msg==WM_CREATE) then
            local ret,mbsInfo = winapi.BroadcastSystemMessageEx(BSF_QUERY, BSM_APPLICATIONS, PM_MYMSG, 0, 0);
            print(ret)
            print_r(mbsInfo)
        elseif(msg==WM_LBUTTONDOWN) then
            local keyFlags = wParam
            local x = winapi.LOWORD(lParam)
            local y = winapi.HIWORD(lParam)
            local str = "WM_LBUTTONDOWN ==> x="..x.." y="..y.." keyFlags="..keyFlags
            print(str)
        elseif(msg==WM_LBUTTONUP) then
            local keyFlags = wParam
            local x = winapi.LOWORD(lParam)
            local y = winapi.HIWORD(lParam)
            local str = "WM_LBUTTONUP ==> x="..x.." y="..y.." keyFlags="..keyFlags
            print(str)
            winapi.SendMessageCallback(hwnd, msg, wParam, lParam, function(hwnd, uint, arg3, result)
                print(hwnd, uint, arg3, result)
            end, 0)
        elseif(msg==WM_SYSKEYUP) then
            local vk = wParam
            local cRepeat = winapi.LOWORD(lParam)
            local flags = winapi.HIWORD(lParam)
            handleSysKey(hwnd, vk, false, cRepeat, flags)
            local point = winapi.GetCursorPos()
            print("GetCursorPos(), ", point)
            print_r(point)
        elseif(msg==WM_SYSKEYDOWN) then
            local vk = wParam
            local cRepeat = winapi.LOWORD(lParam)
            local flags = winapi.HIWORD(lParam)
            handleSysKey(hwnd, vk, true, cRepeat, flags)
        elseif(msg==WM_CHAR) then
            local ch = wParam
            local cRepeat = winapi.LOWORD(lParam)
            local str = "WM_CHAR ==> Ch = "..ch.."("..string.format("%x", ch)..") cRepeat=".. cRepeat
            print(str)
        elseif(msg==WM_PAINT) then
            local point = winapi.GetCursorPos()
            print(point)
            print_r(point)
        elseif(msg==WM_DESTROY) then
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
