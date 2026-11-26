# NumAI for TI-84 Plus CE

NumAI v0.1.4 brings the NumWorks and [Casio](https://github.com/cis5123467-sudo/numai-casio) revision catalog to the TI-84 Plus CE Python Edition. It includes Edexcel IGCSE and A Level Maths, OCR Additional Maths, and AQA Biology, Chemistry and Physics. The catalog contains 540 entries, including 34 science Key Ideas summaries. Maths topics include worked examples and interactive forms where provided.

## Download and install

Get the program and course files from the [v0.1.4 release](https://github.com/cis5123467-sudo/numai-ti84/releases/tag/0.1.4). Transfer these files to **Archive** using TI Connect CE.

- `numai-ti84-v0.1.4.8xp` appears as `NUMAI` on the calculator.
- Transfer `NMTABLE.8xv` and all seven `NMC000.8xv` through `NMC006.8xv` files. These hold the course catalog in flash.
- Transfer `numai-ce-libs-v15.0.8xg` if you still need the four CE libraries. It contains LibLoad, GraphX, KeypadC and FileIOC. If a library is already installed, avoid replacing it unnecessarily.

The target is a TI-84 Plus CE Python on OS 5.8.3 with an existing native program launcher. Open **NUMAI** from that launcher. Press **MODE** to exit.

## Controls

| TI key | NumAI action |
| --- | --- |
| MATH | Courses and topics |
| VARS | CAS operations |
| STAT | Search course notes and titles |
| ZOOM or 2nd then ENTER | Preferences |
| ENTER / CLEAR | Open or calculate / go back or clear input |
| Arrows / DEL | Navigate, move cursor, delete |
| TRACE / GRAPH | Page back and forward, or change form field |
| ALPHA / 2nd then ALPHA | Printed letters / letter lock |
| ALPHA then X,T,θ,n | Return to the main calculation page |
| Y= / WINDOW | Enter a fraction slash / show last result or working |
| APPS / PRGM | Clear input / insert absolute value |
| X,T,θ,n / STO→ | Insert x / store arrow |
| 2nd then x², ^, or (-) | Square root, pi, or Ans |
| 2nd then ( | Insert an equals sign |
| 1–9 or ALPHA+A/B | Open the marked row on the current menu page |

## Build

Use [CEdev v15.0](https://github.com/CE-Programming/toolchain/releases/tag/v15.0), Python 3, and a host C compiler named `cc`. Put `CEdev/bin` on PATH, then run `make`. To assemble a local release, run `make package CE_LIBRARIES=/path/to/clibs.8xg` with the [CE Libraries v15.0 bundle](https://github.com/CE-Programming/libraries/releases/tag/v15.0). Only source, build scripts, documentation and the icon belong in the Git tree. Release files are attached to GitHub Releases.

This first TI build uses a compact interface and the core CAS, including factorisation, expansion, differentiation, integration and solving. Compared with the Casio build, it omits persistent sessions, favourites and dedicated science equation, unit conversion and molecule tools. Host checks confirmed catalog loading and six CAS examples. Physical launch and appearance on a TI-84 have yet to be verified.
