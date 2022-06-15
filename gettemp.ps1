$data = Get-WmiObject MSAcpi_ThermalZoneTemperature -Namespace "root/wmi"
$temp = @()
$temp = $data.CurrentTemperature
$k = $temp[0] / 10
$kelvin = [math]::round($k, 2)
$c = $kelvin - 273.15
$celsius = [math]::round($c,0)
Write-Output "$celsius"
