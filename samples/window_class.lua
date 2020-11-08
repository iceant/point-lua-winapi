package.path= package.path..";".."../samples/?.lua"
local winapi = require('winapi')
require("print_table")

local ret, info=winapi.GetClassInfo("BUTTON")
print_r(info)

print("ISNULL(hInstance)", winapi.ISNULL(info.hInstance))
print("ISNULL(hCursor)", winapi.ISNULL(info.hCursor))

local ret, infoEx=winapi.GetClassInfoEx("BUTTON")
print_r(infoEx)

--print(winapi.GetClassLong(-26)) --GCL_STYLE
--print("Last Error:", winapi.GetLastError())
--print(winapi.GetLastErrorMsg("GetClassLong(GCL_STYLE)"))

local window = winapi.FindWindow(nil, "Windows PowerShell")
print("WindowTestLength for "..tostring(window), winapi.GetWindowTextLength(window))
print("Window Text for "..tostring(window), winapi.GetWindowText(window))

print("GetClassName for "..tostring(window), winapi.GetClassName(window))
print(winapi.GetLastErrorMsg("GetClassName(...)"))