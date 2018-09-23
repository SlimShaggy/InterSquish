
                              InterSquish NNTP Server
                          Version 1.3.4 dated 15.11.1999
                                     Summary

1. Description
     InterSquish is used to convert messages stored in the Squish format
     into News format.  Actually InterSquish is an NNTP server, that
     stores its messages in a squish messagebase.  The primary use for
     InterSquish is routing of Fidonet echoconferences to newsgroups and
     vice versa.  Starting from the current version you can also route
     netmail in both directions(SMTP->FTN and FTN->POP3).

2. Sysytem requirements.
2.1 Environment
     InterSquish has been tested under Windows NT, ParmaTosser 1.06 as
     a tosser and MS Outlook Express and Netscape Messenger as news
     client.  The author does not deny the possibility that InterSquish
     can work under Windows 95 with other squish-like tossers and nntp
     clients.  Having a functionin TCP/IP stack is mandatory.

2.2 Hardware requirements.
     InterSquish will function on any workstation that is sufficient for
     Windows NT (Windows 95/98)

3. Tips and Limitations.

3.1 General info.
     InterSquish is a multithreaded Win32 application, which is capable of 
     working as a Windows NT service.  Each InterSquish connection is
     served with a different thread.

3.2 Posting
     the registered version of InterSquish allows posting into
     echoconferences.  The outgoing article is transformed into a *.pkt
     file, which is then fed to the tosser.
     
4. Installation
    After unpacking the archive you should modify parameters in the
    configuration files - is.cfg and users.cfg - so that they conform to
    your needs and the system environment.  Please make sure you have
    entered complete paths, including drive letters.

5.Command Line Options
    /Install - register as a Windows NT service
    /Uninstall - delete InterSquish Windows NT services database
    /Win9X - launch InterSquish under Windows 95, 98.

6. Future versions
    In the future versions it is planned:
    -to fix the bugs, which a surely still here

7. Support
    The author guarantees support for registered users only.
    Support echoconference - RU.INTERSQUISH. Ask it from your uplinks.

8. Author
     InterSquish Server author - Ivan Uskov. You can contact me at the
     following addresses:
    2:5055/101.3@fidonet (preferred)
    2:5055/114@fidonet
    citousers@interdacom.ru

    HomePages:
    http://intersquish.da.ru
        
