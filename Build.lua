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
   trigger = "with-demo",
   description = "Include the application demo project"
}

newoption {
   trigger = "with-tests",
   description = "Include test suite"
}

-- Include subprojects
group "Core"
	include "Core/Build-Core.lua"
group ""

if _OPTIONS["with-demo"] then
   group "Demo"
      include "Demo/Build-Demo.lua"
   group ""
end

if _OPTIONS["with-tests"] then
   group "Tests"
      include "Tests/Build-Tests.lua"
   group ""
end