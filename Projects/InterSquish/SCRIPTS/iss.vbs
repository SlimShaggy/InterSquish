option explicit
'
'CheckIpAddress
'������ �㭪�� �����頥� true, �᫨ � 㪠������� � REMOTE_IP IP-����
'ࠧ�襭� ᮥ�������� � �ࢥ஬ � false, � ��⨢��� ��砥.
function CheckIpAddress(SERVICENAME,REMOTE_IP)
    if (InStr(1,REMOTE_IP,"192.168.0.",1)=1) or (InStr(1,REMOTE_IP,"127.",1)=1) then
        CheckIpAddress=true
    else
        CheckIpAddress=false
    
    end if
end function

'------------------------------------------------------------------------------
' ����᫥���饥 ����� �ᯮ�짮���� ��� ���஢����, ��᪮�����஢�� �
' ����᪠� �ਯ� �� ��������� ��ப�:
'------------------------------------------------------------------------------

' WScript.Echo CheckIpAddress("NNTP","10.1.1.0")
' WScript.Echo CheckIpAddress("NNTP","192.168.0.1")
' WScript.Echo CheckIpAddress("NNTP","127.0.0.1")