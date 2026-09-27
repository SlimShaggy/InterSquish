# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project overview

InterSquish is an NNTP server / FTN (FidoNet Technology Network) gate for Windows, written in Borland C++ (C++Builder 6, VCL). It converts FidoNet echoconferences stored in Squish or JAM message-base format into NNTP newsgroups, and gates them back (NNTP post → `.PKT` file handed to an external FTN tosser like ParmaTosser). It also gates netmail bidirectionally: SMTP→FTN and FTN→POP3. It runs as a multithreaded Win32 app, normally installed as an NT service (one thread per client connection).

This is a maintenance fork of an old (pre-2009) SourceForge project (`intersquish`, originally by Ivan Uskov, later Fyodor Ustinov and Andrey Sakhno). The current maintainer (see README.md §9) is not a C++ developer by trade and only fixes bugs found in real-world use on a live Fido node — there is no active new-feature development. Keep changes minimal, targeted bug fixes; don't refactor broadly or introduce new abstractions/dependencies.

## Build

- Toolchain: **Borland/CodeGear C++ Builder 6** (VCL). There is no modern build system, no CI, and no automated test suite.
- Main project file: `Projects/InterSquish/IS.bpr` — open and build this in C++ Builder 6 to produce `IS.exe`.
- Several `.bpk`/`.bpg` package files exist under `comp/` and `ProjectGroups/` (e.g. `iuFTN.bpk`, `iuNet`, `iuRSA.bpk`...). Per README.md §10, these do **not** need to be built separately — their `.cpp` files are added directly into `IS.bpr`, so the packages are effectively vendored/legacy artifacts, not real build targets.
- Distribution: `Projects/InterSquish/!MakeDist.cmd` zips `IS.exe` together with docs/sample configs into `iss.zip`. Requires 7-Zip (`7z`) on `PATH`.
- Since there's no build available on this (non-Windows-C++Builder) environment, verification of C++ changes is by careful reading, not compilation — flag this to the user rather than claiming a build was tested.

## Source encoding — read before editing any `.cpp`/`.h`/`.txt` file

C++ and plaintext source files in this repo are encoded in **Windows-1251 (cp1251)**, not UTF-8 (see `.vscode/settings.json`: `"[cpp]"`/`"[plaintext]"` → `files.encoding: windows1251`; `.bat`/config files use `cp866`). Most files contain Russian comments/strings/doc text in this encoding. New comments added to source files must be in Russian as well.

Standard UTF-8-aware text edit tools will misinterpret or corrupt the Cyrillic bytes. When editing these files, use a byte-safe approach (e.g. a small script that reads/writes the file treating it as raw bytes/`latin1` rather than decoding as UTF-8), especially when touching lines containing Cyrillic text. Verify by re-reading the raw bytes after editing rather than trusting a UTF-8 render.

## Architecture

### Entry point and app shell (`Projects/InterSquish/`)
- `IS.cpp` — `WinMain`. Depending on the `/Win9X` command-line switch, either runs as a normal VCL GUI app with `isControlWindow` (Win9x/manual mode) or creates the three server forms and runs as an NT service (`/Install`, `/Uninstall` switches handled elsewhere via `ISSetup.cpp`).
- `isNNTP.*`, `isSMTP.*`, `isPOP3.*` — thin VCL form wrappers (`TISsNNTP`, `TISsSMTP`, `TISsPOP3`) around the actual protocol server components; mostly config wiring and lifecycle.
- `isInit.*` — `TisMain`: loads the shared config objects (`TSquishCfg`, `TCustomUsersCfg`, `TTextCfg`) from `is.cfg`/`users.cfg`, and `ReadNNTPServerConfiguration`/`ReadSMTPServerConfiguration`/`ReadPOP3ServerConfiguration` apply that config to each server component.
- `isControlWindow.*` — status/control GUI window shown in non-service (Win9x) mode.
- `is.cfg`, `users.cfg`, `mask.ini` — runtime configuration (paths, area/user mappings); sample/documented versions live under `DOC/RUS` and `DOC/ENG`.

### Shared component library (`comp/`)
- `iuNet/` — generic threaded TCP server framework, independent of FTN specifics: `TiuServer` (base server socket: thread pool, IP twit-list, logging, optional WSH scripting hook) plus per-protocol layers `iuNNTPServer`/`iuNNTPServerThread`, `iuSMTPServer`/`...Thread`, `iuPOP3Server`/`...Thread`, and the base `iuServerClientThread`.
- `iuFTNPlus/iuInterSquishServer.cpp` (~2500 lines, the largest and most central file) — implements the actual gating logic by subclassing the `iuNet` protocol servers:
  - `TiuIssNNTPServer`/`Thread` — exposes FTN areas as newsgroups (article retrieval from Squish/JAM, newsgroup list building, posting converts an article into a `.PKT`).
  - `TiuIssSMTPServer`/`Thread` — accepts SMTP netmail and converts it into FTN `.PKT` netmail.
  - `TiuIssPOP3Server`/`Thread` — emulates a POP3 mailbox backed by a user's FTN netmail.
- `iuFTN/` — FTN/Fido domain logic used by the above: `FTNMsg` (message model), `FTNPKT` (`.PKT` packet read/write), `FTNDataSet` (abstraction over Squish/JAM message bases), `Cfg` (parses `is.cfg`/`users.cfg`/`areas.cfg`), `Kludges` (FTN kludge-line handling), `AreasTreeView`.
- `iuMisc/` — string/charset/transliteration utilities (`iuString`, `Transliterates`), `CRC32`, Windows service helper (`service.cpp`), `log.cpp` (also under `iuLogs/`), registry helpers.
- `iuScript/` — optional WSH scripting integration (`iuScriptControl` wraps `MSScriptControl`) used for per-area/per-user scripting hooks (see `SCRIPTS/*.vbs`).
- `iuRSA/` — vendored RSA/MD5 (RSAREF-derived) code used for auth.
- `jamapi/`, `msgapi/` — vendored third-party C reference implementations of the **JAM** and **Squish** message-base APIs (not InterSquish-authored; treat as reference/unmodified vendored code unless a bug is clearly in InterSquish's use of them).

### Data flow
Incoming FTN mail/echomail lands as a `.PKT` (read via `FTNPKT`) or directly in a Squish/JAM base (read via `FTNDataSet`). The NNTP server thread (`TiuIssNNTPServerThread`) surfaces base articles as newsgroup content; posting an NNTP article builds a `.PKT` that gets picked up by the external tosser. Netmail flows the same way through the SMTP (inbound Internet mail → outbound `.PKT`) and POP3 (FTN netmail → mailbox read) server threads. Config for which FTN areas map to which newsgroups, and which users/addresses are known, comes from `TSquishCfg`/`TCustomUsersCfg` (`comp/iuFTN/Cfg.cpp`), loaded once at startup by `isInit.cpp`.

### Version/changelog
Release version and changelog live in `Projects/InterSquish/DOC/RUS/history.txt` (Russian) / `DOC/ENG/HISTORY.TXT`, using `*`/`-`/`+`/`!` flags per README §"History flags" (rewrite/removed/added/fixed). DO NOT bump the version and add entries here unless asked! This repo's commit messages also tend to be short, changelog-style descriptions of a single fix (often in Russian).
