# Checks if NNTP service is alive, restarts if not
# Add to Win7 scheduler: schtasks /Create /TN "InterSquish Watchdog" /TR "powershell -NoProfile -ExecutionPolicy Bypass -File \"c:\watchdog.ps1\"" /SC MINUTE /MO 10 /RL HIGHEST /RU SYSTEM /F

$Port    = 119
$Service = "ISsNNTP"
$Timeout = 10000  # ms to wait for the banner

$bannerOk = $false

try {
    $tcp = New-Object Net.Sockets.TcpClient
    $tcp.Connect("localhost", $Port)
    $stream = $tcp.GetStream()
    $stream.ReadTimeout = $Timeout
    $reader = New-Object IO.StreamReader($stream)
    $line = $reader.ReadLine()
    $tcp.Close()

    if ($line -ne $null -and $line.StartsWith("200")) {
        $bannerOk = $true
    } else {
        Write-Warning "Unexpected banner: '$line'"
    }
} catch {
    Write-Warning "Connection failed: $_"
}

if ($bannerOk) {
    Write-Host "OK: Port $Port responded with a 200 banner. No action needed."
    exit 0
}

Write-Warning "Port $Port did not return a 200 banner. Restarting service '$Service'..."

try {
    Stop-Service -Name $Service -Force -ErrorAction SilentlyContinue
    Start-Sleep -Seconds 3
    Start-Service -Name $Service -ErrorAction Stop
    Write-Host "OK: Service '$Service' restarted successfully."
} catch {
    Write-Error "Failed to restart service '$Service': $_"
    exit 1
}