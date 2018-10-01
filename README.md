# InterSquish
## NNTP Server / FTN Gate for Windows
## 1. Назначение
InterSquish предназначен для конвертации эхоконференций, хранимых в формате эхопроцессора Squish, в News-формат. Фактически InterSquish является NNTP-сервером, который хранит сообщения в Squish- или JAM-базе. Основным применением InterSquish является гейтование фидошных конференций в ньюсгруппы и обратно. Так же имеется возможность двустороннего гейтования нетмейла (SMTP->FTN и FTN->POP3).

## 2. Требования к системе
### 2.1 Программное окружение
InterSquish тестировался в операционной системе Windows 2000, в качестве тоссера использовался ParmaTosser 1.06.\
News-клиент - MS Outlook Express, Netscape Messenger.\
Mail-клиент - MS Outlook Express, The Bat!\
Автор допускает возможность работы InterSquish под управлением Windows 95, с другими тоссерами и NNTP-клиентами. Наличие протокола TCP/IP обязательно.

### 2.2 Требования к аппаратуре
InterSquish будет работать на любой машине, на которой функционирует Windows NT/2000 (Windows 95/98)

## 3. Некоторые особенности и ограничения
### 3.1 Общие сведения
InterSquish является многопоточным Win32-приложением, каждое соединение с клиентом обслуживается отдельным потоком. Рекомендуемый режим запуска InterSquish - сервис Windows NT.

### 3.2 Постинг
InterSquish поддерживает постинг в эхоконференции. Постинг осуществляется посредством преобразования входящей статьи в .PKT-файл, который затем передается тоссеру.

## 4. Инсталляция
После распаковки архива вам необходимо установить параметры в файлах конфигурации - is.cfg и users.cfg так, чтобы они соответствовали вашим требованиям и программному окружению. Во избежание неполадок все пути должны быть полными, с указанием имени диска.

## 5. Ключи командной строки
/Install - регистрация в качестве сервиса Windows NT\
/Uninstall - удаление InterSquish из базы служб Windows NT\
/Win9X - запуск InterSquish в Windows 95, 98.

## 6. Будущие версии
В будущих версиях планируется:
* Исправить ошибки, которые возможно найдутся.

## 7. Поддержка
Данный продукт является freeware, распространяется по принципу as is, и автор никаких гарантий дать не может. Эха поддержки - RU.INTERSQUISH. Спрашивайте у аплинков.

## 8. Автор и разработчики
Автор сервера InterSquish - Иван Усков. Но с июля 2001 года он перестал заниматься поддержкой InterSquish (точнее, по прежнему поддерживает зарегистрированных пользователей, но больше самим InterSquish не занимается). С ним можно связаться по следующим адресам:\
ivus@tele-kom.ru (предпочтительнее)\
2:5055/114@fidonet

Следующий разработчик, начиная с версии 1.7 - Фёдор Устинов. С ним можно связаться так:\
ufm@kgb.ru\
2:5020/79.0\
http://ufm.kgb.ru

Следующий разработчик - Андрей Сахно:\
a.sakhno@tut.by\
2:457/79.11
Его версии программы, а также документация доступны на сайте http://intersquish.narod.ru (осторожно, навязчивая реклама!)

## 9. Создатель данного репозитория
Меня зовут Андрей Иванов. Недавно я осуществил свою детскую мечту и подключился к сети Фидо, став поинтом (2:5023/24.3586) узла wfido.ru, на котором установлен InterSquish. В процессе использования NNTP-доступа я обнаружил досадный баг, не позволявший мне писать сообщения с некоторыми сабжами (при отправке письма происходила ошибка). Будучи программистом, я решил найти и исправить этот баг. В локалке моего босса HOBBIT.LOCAL мне дали ссылку на репозиторий https://sourceforge.net/p/intersquish/code/HEAD/tree/trunk/, созданный Андреем Сахно в 2009 году. Этот репозиторий использует устаревшую систему контроля версий SVN, поэтому для удобства багфиксинга я создал локальный Git-репозиторий на своей машине. Через несколько дней баг был успешно исправлен, обновленная версия InterSquish установлена на wfido.ru, а у меня возникла мысль поделиться данными доработками с сообществом. В результате после некоторого причесывания коммитов я залил свой репозиторий на GitHub.
Поскольку я не являюсь программистом C++ (мой "родной" язык - C#), я не претендую на роль следующего разработчика InterSquish и не планирую реализовывать новый функционал. Но обнаруженные критические баги постараюсь по возможности исправить. Со мной можно связаться по электронной почте slimshaggy@live.com.

## 10. Коротко о структуре репозитория
Ветка master создана на основе версии исходников, лежащих в архиве https://sourceforge.net/p/intersquish/code/HEAD/tree/trunk/is.rar в репозитории Андрея Сахно. В проекте указана версия 2.0.5.20. Из этих исходников без каких-либо изменений был собран релиз 2.0.5.20. Мои правки по багу с сабжами вошли в релиз 2.0.5.21.
Также в репозитории создана ветка 2.0.5.31. Она содержит код из ветки trunk (https://sourceforge.net/p/intersquish/code/HEAD/tree/trunk/) репозитория Андрея Сахно (в проекте указана версия 2.0.5.31). Некоторые изменения в этом коде относительно версии 2.0.5.20 показались мне сомнительными, а еще некоторые - непонятными по назначению, поэтому использовать данный код я не стал и просто залил в отдельную ветку как есть.

Чтобы собрать исполняемый файл InterSquish, необходимо сбилдить проект Projects\InterSquish\IS.bpr в Borland C++ Builder 6 (https://winworldpc.com/product/borland-c-builder/6x). В репозитории также имеется ряд пакетов .bpk и групп проектов .bpg. Билдить их не нужно - в основном проекте пакеты не используются, а содержащиеся в них .cpp-файлы просто добавлены в него напрямую.

В результате сборки получается исполняемый файл IS.EXE, который можно упаковать в zip вместе с документацией и примерами конфигов с помощью скрипта Projects\InterSquish\\!makedist.cmd.
