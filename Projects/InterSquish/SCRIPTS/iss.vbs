option explicit
'
'CheckIpAddress
'Данная функция возвращает true, если с указанного в REMOTE_IP IP-адреса
'разрешено соединяться с сервером и false, в противном случае.
function CheckIpAddress(SERVICENAME,REMOTE_IP)
    if (InStr(1,REMOTE_IP,"192.168.0.",1)=1) or (InStr(1,REMOTE_IP,"127.",1)=1) then
        CheckIpAddress=true
    else
        CheckIpAddress=false
    
    end if
end function

'------------------------------------------------------------------------------
' Нижеследующее можно использовать для тестирования, расскомментировав и
' запуская скрипт из командной строки:
'------------------------------------------------------------------------------

' WScript.Echo CheckIpAddress("NNTP","10.1.1.0")
' WScript.Echo CheckIpAddress("NNTP","192.168.0.1")
' WScript.Echo CheckIpAddress("NNTP","127.0.0.1")