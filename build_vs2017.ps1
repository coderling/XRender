$isrebuild = $args[0] -eq "-r"

$build_type = "Debug"

if($args[1] -eq "-release")
{
    $build_type = "Release"
}



Write-Output $isrebuild

if($isrebuild)
{
    if(Test-Path .\build\win)
    {
        Remove-Item -Path .\build\win -Force -Recurse
    }
}


if(-not (Test-Path .\build))
{
    mkdir .\build
}

if(-not (Test-Path .\build\win))
{
    mkdir .\build\win
}

Set-Location -Path .\build\win
cmake -G "Visual Studio 16 2019" ../../
# devenv XTiny.sln /Build Debug /Project ALL_BUILD /ProjectConfig $build_type
# devenv XTiny.sln /Build Debug /Project INSTALL /ProjectConfig D$build_type
Set-Location -Path ..\..\
