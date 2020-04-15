$isrebuild = $args[0] -eq "-r"

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
cmake -G "Visual Studio 15 2017 Win64" ../../
devenv XTiny.sln /Build Debug /Project ALL_BUILD /ProjectConfig Debug
Set-Location -Path ..\..\