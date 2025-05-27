workspace "WaveKit"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Demo"

   outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
   
   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
   filter {}

-- Custom build options
newoption {
   trigger = "no-demo",
   description = "Exclude the application demo project"
}

newoption {
   trigger = "no-tests",
   description = "Exclude the test suite"
}

print("[WaveKit Configuration]")
if _OPTIONS["no-demo"] then print(" --Excluding demo project") end
if _OPTIONS["no-tests"] then print(" --Excluding test suite") end
if not _OPTIONS["no-demo"] and not _OPTIONS["no-tests"] then 
    print(" --Including demo")
    print(" --Including test suite")
end
print("")
-- Include subprojects
group "Core"
	include "Core/Build-Core.lua"
group ""

if not _OPTIONS["no-demo"] then
   group "Demo"
      include "Demo/Build-Demo.lua"
   group ""
end

if not _OPTIONS["no-tests"] then
   group "Tests"
      include "Tests/Build-Tests.lua"
   group ""
end