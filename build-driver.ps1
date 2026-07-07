Param(
    [string]$Configuration = 'Release',
    [string]$Platform = 'x64'
)

$solutionPath = Join-Path $PSScriptRoot 'src\KmRootkit.sln'
Write-Host "Building solution: $solutionPath"
Write-Host "Configuration: $Configuration, Platform: $Platform"

$checkScript = Join-Path $PSScriptRoot 'check-wdk.ps1'
if (-not (Test-Path $checkScript)) {
    Write-Error "Missing check-wdk.ps1 script."
    exit 1
}

Write-Host 'Checking WDK installation...'
& $checkScript
if ($LASTEXITCODE -ne 0) {
    Write-Error 'WDK check failed. Aborting build.'
    exit $LASTEXITCODE
}

$msbuild = Get-Command msbuild.exe -ErrorAction SilentlyContinue
if (-not $msbuild) {
    Write-Error 'MSBuild was not found. Install Visual Studio with MSBuild.'
    exit 1
}

Write-Host "Using MSBuild: $($msbuild.Path)"
$buildArgs = @(
    $solutionPath,
    "/p:Configuration=$Configuration",
    "/p:Platform=$Platform",
    '/m'
)

& $msbuild @buildArgs
if ($LASTEXITCODE -ne 0) {
    Write-Error 'MSBuild reported errors.'
    exit $LASTEXITCODE
}

$sysFolder = Join-Path $PSScriptRoot "src\KmRootkit\x64\$Configuration"
if (-not (Test-Path $sysFolder)) {
    Write-Error "Build completed but output folder not found: $sysFolder"
    exit 1
}

$sysFiles = Get-ChildItem -Path $sysFolder -Filter '*.sys' -ErrorAction SilentlyContinue
if (-not $sysFiles) {
    Write-Error "No .sys files were found in $sysFolder"
    exit 1
}

Write-Host 'Build succeeded. .sys file(s) found:'
$sysFiles | ForEach-Object { Write-Host "  $($_.FullName)" }
exit 0
