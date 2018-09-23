option explicit
'
' CheckUser
' Данная функция _должна_ возвратить строку вида:
' "FTNAddress,ReplyAddr,ReplyTo,Groups,ROGroups" в случае удачной аутентификации
' или пустую строку - "" - в случае неудачной
function CheckUser (SERVICENAME, ACC_NAME, ACC_PASSWORD)
dim sReturnString
    sReturnString=""
    ACC_NAME=UCase(ACC_NAME) 'Переводим аккоунт пользователя в верхний регистр.
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