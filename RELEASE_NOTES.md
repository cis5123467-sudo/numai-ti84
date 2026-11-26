# NumAI TI-84 v0.1.4

First TI-84 Plus CE Python build, targeting OS 5.8.3 on a calculator with an existing native launcher. Transfer the program and all eight course AppVars to Archive, plus the CE Libraries group if the dependencies are missing. Launch **NUMAI** and press **MODE** to exit.

## Courses and CAS

- Includes all 540 topics from the Casio v0.1.4 catalog. The 428 AQA science entries include all 34 Key Ideas pages. Maths keeps worked examples and editable forms.
- Press **MATH** to browse, **STAT** to search and **VARS** to select a CAS operation. Calculation, solving, factorisation, simplification, expansion, derivatives and supported integrals are available.
- The TI keypad and 320 × 240 display have their own mappings and layout. Read [the controls](https://github.com/cis5123467-sudo/numai-ti84#controls) for details.
- The TI build does not carry over saved sessions, favourites, dedicated science equations, unit conversions or molecule drawings.

## Release files and validation

- `numai-ti84-v0.1.4.8xp` is the native program. Its TI file header, archive flag, native marker and checksum passed validation.
- `NMTABLE.8xv` and `NMC000.8xv` to `NMC006.8xv` are all required. `numai-ce-libs-v15.0.8xg` includes LibLoad, GraphX, KeypadC and FileIOC.
- CEdev v15.0 compiled the program. Host checks loaded 540 topics and verified the placement of 34 Key Ideas entries, rejected missing, unarchived and truncated course data, and passed six CAS checks. Physical launcher and keypad operation have not been verified.
