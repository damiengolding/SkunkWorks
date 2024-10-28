########## Static libraries ##########
Write-Host "Deploying PtngDataVisualization static libraries and headers"

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc" -ItemType Directory
}

##### Libraries #####
if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\release\libparser.lib" ){
    Write-Host "Copying release (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\release\libparser.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
}
else{
    Write-Host "Omitting release (static) build library; library does not exist"
}

if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\debug\libparserd.lib" ){
    Write-Host "Copying debug (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\StaticOutput\libparser\debug\libparserd.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static"
}
else{
    Write-Host "Omitting debug (static) build library; library does not exist"
}

##### Headers #####
###### Create directories ######
if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc" ) ){ # This is for libparser_global.hpp and similar structural files
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\data" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\data" -ItemType Directory
}

###### Copy headers ######
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\inc\libparser_global.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\inc"

Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngenums.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngstylesheet.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\utils"

Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\abstractptnginput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\abstractptngoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngdgmloutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngdotoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngidentifier.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputarpscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputdnsrecon.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputhost.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnbtscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnessus.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnmapaxfr.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnmapenumeration.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnslookuplin.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnslookupwin.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputsslscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngnamicsoftoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"

########## Copy shared libraries ##########
Write-Host "Deploying PtngDataVisualization shared libraries and headers"

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc" -ItemType Directory
}

##### Headers #####
###### Create directories ######
if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\inc" ) ){ # This is for libparser_global.hpp and similar structural files
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\inc" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\utils" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\utils" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io" -ItemType Directory
}

if( -not( Test-Path -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\data" ) ){
    New-Item -Path "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\data" -ItemType Directory
}

##### Libraries #####
if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\release\libparser.lib" ){
    Write-Host "Copying release (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\release\libparser.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\release\libparser.dll" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
}
else{
    Write-Host "Omitting release (static) build library; library does not exist"
}

if( Test-Path -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\debug\libparserd.lib" ){
    Write-Host "Copying debug (static) build library to C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\debug\libparserd.lib" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
    Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\SharedOutput\libparser\debug\libparserd.dll" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared"
}
else{
    Write-Host "Omitting debug (static) build library; library does not exist"
}

###### Copy headers ######
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\inc\libparser_global.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\inc"

Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngenums.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\utils"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\utils\ptngstylesheet.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\utils"

Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\abstractptnginput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\abstractptngoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Static\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngdgmloutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngdotoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngidentifier.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputarpscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputdnsrecon.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputhost.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnbtscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnessus.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnmapaxfr.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnmapenumeration.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnslookuplin.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputnslookupwin.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptnginputsslscan.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"
Copy-Item -Path "C:\Users\damie\source\repos\SkunkWorks\PtngDataVisualization\PtngDataVisualizationV2\libparser\io\ptngnamicsoftoutput.hpp" -Destination "C:\Tools\GoldingsGymLibraries\PtngDataVisualization\Shared\inc\io"