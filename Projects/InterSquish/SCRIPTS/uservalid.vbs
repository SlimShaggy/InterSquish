option explicit
'
' CheckUser
' ������ �㭪�� _������_ �������� ��ப� ����:
' "FTNAddress,ReplyAddr,ReplyTo,Groups,ROGroups" � ��砥 㤠筮� ��⥭�䨪�樨
' ��� ������ ��ப� - "" - � ��砥 ��㤠筮�
function CheckUser (SERVICENAME, ACC_NAME, ACC_PASSWORD)
dim sReturnString
    sReturnString=""
    ACC_NAME=UCase(ACC_NAME) '��ॢ���� ������ ���짮��⥫� � ���孨� ॣ����.
'    if(SERVICENAME="NNTP") then
        Select Case ACC_NAME
           Case "PUPKIN"
                if ACC_PASSWORD="PupkinPassword" then
                    sReturnString="2:5055/114.999,,,ABCDEF,ABF"
                end if
           Case "INETUSER"  
                if ACC_PASSWORD="pass1" then
                    sReturnString="2:5055/114.500,user@online.nsk.su,2:5020/400 UUCP,ABCDEF,ABF"
                end if
           Case "IVUS"
                if ACC_PASSWORD="1" then
                    sReturnString="2:5055/114.3,ivus@tele-kom.ru,2:50/128 UUCP,*,AZ"
                end if
                
      End Select
'     end if
    CheckUser=sReturnString
end function
'------------------------------------------------------------------------------
'WScript.echo CheckUser ("NNTP", "Pupkin", "PupkinPassword")
'WScript.echo CheckUser ("NNTP", "ivus", "1")