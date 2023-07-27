################################################################################
# Bluetooth - SoC Interoperability Test GBL generator
#
# This script generates the GBL files needed for SoC Interoperability Test.
# These files are used for the OTA-DFU tests.
#
# Prerequisites
# - Windows PowerShell 2.0 or higher
# - PATH_SCMD and PATH_GCCARM environment variables to be set. See readme.md
# for more information.
# - The Bluetooth - SoC Interoperability Test example generated either with
# the "Link SDK and copy project sources" or the "Copy contents" option.
# - The project is built with success.
#
# Usage
# - Run this script.
# - Copy the generated gbl files onto the storage of the phone.
# - In the EFR Connect app, open the Interoperability Test demo tile.
# - Start the test. When prompted to choose a gbl file for OTA-DFU, select the
# ota-dfu_ack.gbl file. When prompted again, select ota-dfu_non_ack.gbl.
#
# For a more detailed guide see the readme.md file of the example.
################################################################################

$App1 = "ota-dfu_non_ack"
$App2 = "ota-dfu_ack"
$DeviceName1 = "IOP_Test_1"
$DeviceName2 = "IOP_Test_2"

$OtaApploName = "apploader"
$OtaAppliName = "application"
$UartdfuFullName = "full"

################################################################################
# Functions
################################################################################
# Checks the presence of a string in a binary.
function Search-Str-In-Bin {
    Param
    (
        [Parameter(Mandatory=$true, Position=0)]
        [string] $Str,
        [Parameter(Mandatory=$true, Position=1)]
        [string] $File
    )

    Write-Output "Searching for $Str in $File"
    $result = Select-String -Path $File -Pattern $Str -CaseSensitive
    if ($null -eq $result) {
        Write-Error "Error: $Str cannot be found in $File"
        Write-Output "Press any key to continue..."
        [void][Console]::ReadKey()
        Exit(1)
    } else {
        Write-Output "Found: $result"
    }
}

################################################################################
# Entry point
################################################################################
if ($null -eq $PSScriptRoot) {
    # Backward compatibility. $PSScriptRoot is only supported since PowerShell 3.0
    $PSScriptRoot = Split-Path -Parent -Path $MyInvocation.MyCommand.Definition
}

Write-Output "**********************************************************************"
Write-Output "This script produce the GBL images from the already built project" 
Write-Output "artifacts that are necessary for the IOP testing:"
Write-Output "[1.] Executes the GBL generator script to generate the original app" 
Write-Output "[2.] Modifies the device name in the .out file"
Write-Output "[3.] Executes the GBL generator again to make the updated app"
Write-Output "This way the tester can easily check that the application update has"
Write-Output "been successful or not."
Write-Output "**********************************************************************"

$PathGbl = Join-Path $PSScriptRoot 'output_gbl'

# Locate the out file
$PathOut = (Get-ChildItem -Path $PSScriptRoot -Include ('*.axf', '*.out') -Recurse | ForEach-Object { $_.FullName })
if ($null -eq $PathOut) {
    Write-Output "Error: neither .axf nor .out file was found."
    Write-Output "Was the project compiled and linked successfully?"
    Write-Output "Press any key to continue..."
    [void][Console]::ReadKey()
    Exit(1)
}

if($PathOut -is [array]) {
  Write-Output "Multiple build artifacts found!"
  Write-Output "Getting the first element as the target that is:"
  Write-Output $PathOut[0] 
  $PathOut = $PathOut[0]
}

# Locate the create_bl_files.bat script
$CreateBlFiles = Join-Path $PSScriptRoot 'create_bl_files.bat'
if (-not (Test-Path -Path $CreateBlFiles)) {
    Write-Output "Error: $CreateBlFiles was not found."
    Write-Output "Was the project generated with the copy option?"
    Write-Output "Press any key to continue..."
    [void][Console]::ReadKey()
    Exit(1)
}

Write-Output "**********************************************************************"
Write-Output "Generating gbl file for the default application."
Write-Output "**********************************************************************"
Write-Output ""

Start-Process -FilePath $CreateBlFiles -Wait
Move-Item -Path (Join-Path $PathGbl "$OtaAppliName.gbl") -Destination (Join-Path $PathGbl "$App1.gbl") -Force

# Check device name
Search-Str-In-Bin -Str $DeviceName1 -File (Join-Path $PathGbl "$App1.gbl")

Write-Output "**********************************************************************"
Write-Output "Generating gbl file for the updated application."
Write-Output "**********************************************************************"
Write-Output ""

# Make a copy of the out file if its not empty
$OutFileName = Split-Path -Path $PathOut -Leaf
if ((Get-Item $PathOut).Length -gt 0) { 
  Write-Output ("Make backup from: " + $OutFileName + " -> " + $OutFileName + "_backup")
  Copy-Item -Path $PathOut -Destination ($PathOut + "_backup")
} else {
  Write-Output "Error: $OutFileName exists but it is empty."
  Write-Output "Rebuild the project, and run this script again!"
  Write-Output "Press any key to continue..."
  [void][Console]::ReadKey()
  Exit(1)
}


# Change the device name by manipulating the out file
if ($PSVersionTable.PSVersion.Major -ge 6) {
    $ByteArg = @{ AsByteStream = $true }
} else {
    $ByteArg = @{ Encoding = 'Byte' }
}

$OutFileData = [BitConverter]::ToString((Get-Content $PathOut -ReadCount 0 @ByteArg))
$OutFileData = $OutFileData.Replace([BitConverter]::ToString([Text.Encoding]::UTF8.GetBytes($DeviceName1)),
                                    [BitConverter]::ToString([Text.Encoding]::UTF8.GetBytes($DeviceName2)))
$OutFileData = [byte[]] ($OutFileData -split '-' -replace '^', '0x') # Convert the modified "hex string" back to a byte[] array.
Set-Content $PathOut @ByteArg -Value $OutFileData

Start-Process -FilePath $CreateBlFiles -Wait
Move-Item -Path (Join-Path $PathGbl "$OtaAppliName.gbl") -Destination (Join-Path $PathGbl "$App2.gbl") -Force

# Clean up
# Restore the original out file
Move-Item -Path ($PathOut + "_backup") -Destination $PathOut -Force
# Only keep the necessary gbl files
Remove-Item (Join-Path $PathGbl "$OtaApploName*")
Remove-Item (Join-Path $PathGbl "$OtaAppliName*")
Remove-Item (Join-Path $PathGbl "$UartdfuFullName*")

# Check device name
Search-Str-In-Bin -Str $DeviceName2 -File (Join-Path $PathGbl "$App2.gbl")
Exit(0)
