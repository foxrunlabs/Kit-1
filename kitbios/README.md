# KitBIOS

**KitBIOS** is the system firmware and machine monitor for the
[Kit-1 8-bit computer](https://github.com/foxrunlabs/Kit-1), a homebrew computer
built around the WDC 65C02 microprocessor.

Written in 65C02 assembly, KitBIOS provides the low-level services required to
operate the Kit-1 hardware, including terminal I/O and block-level microSD
access. It also includes **KitMon**, an interactive machine-language monitor for
examining memory, modifying system state, loading and saving data, and executing
code.

KitBIOS is assembled with the **cc65** toolchain and can be built either for the
physical Kit-1 computer or for the project's 65C02 simulation environment.

## Overview

KitBIOS occupies the lowest software layer of the Kit-1:

```text
┌─────────────────────────────────────┐
│           User Programs             │
├─────────────────────────────────────┤
│              KitMon                 │
│       Machine-Language Monitor      │
├─────────────────────────────────────┤
│             KitBIOS                 │
│                                     │
│   Terminal I/O    microSD Access    │
├─────────────────────────────────────┤
│          Kit-1 Hardware             │
│                                     │
│  W65C02   65C51   65C22   microSD   │
└─────────────────────────────────────┘
```

At reset, KitBIOS establishes the software environment for the machine and
provides a small set of callable firmware services. KitMon builds on those
services to provide an interactive development and debugging environment over
the serial terminal.

## BIOS Services

KitBIOS exposes the following firmware services:

| Call | Service |
| ---: | --- |
| `0` | Reset |
| `1` | Write character to terminal |
| `2` | Write string to terminal |
| `3` | Read character from terminal without echo |
| `4` | Read sector from SD card |
| `5` | Write sector to SD card |

These routines provide a small hardware-abstraction layer for software running
on the Kit-1.

Rather than requiring every program to directly manipulate the serial and
storage hardware, applications can use the BIOS entry points for common I/O
operations.

Conceptually:

```text
Application / Monitor
        │
        ▼
   KitBIOS Call
        │
   ┌────┴────┐
   │         │
   ▼         ▼
Terminal   microSD
   │         │
   ▼         ▼
 65C51     65C22
```

## KitMon

**KitMon** is the interactive machine-language monitor included with KitBIOS.

A monitor provides direct access to the computer without requiring a higher-level
operating system. It is useful for hardware bring-up, debugging, inspecting
machine state, entering small programs, and transferring blocks of memory.

### Commands

| Command | Function |
| :---: | --- |
| `D` | Dump memory |
| `E` | Enter data into memory |
| `F` | Fill a memory range |
| `J` | Jump to an address |
| `L` | Load data |
| `R` | Display registers |
| `S` | Display stack |
| `W` | Write data |
| `?` | Display help |
| `Ctrl-R` | Reset |

All numeric parameters are entered in **hexadecimal**.

Address ranges are separated by a space.

For example, the monitor's help menu can be displayed by entering:

```text
?
```

and pressing Return.

## Serial Terminal

KitMon communicates with the user through the Kit-1 serial interface.

Configure the terminal for:

```text
Baud rate:       19200
Data bits:       8
Parity:          None
Stop bits:       1
Local echo:      Off
Terminal:        VT100
Return key:      LF
Standalone LF:   Interpret as CRLF
```

In conventional shorthand:

```text
19200 8-N-1
```

The terminal should not locally echo characters because terminal interaction is
handled by the Kit-1.

## Building

KitBIOS uses the assembler and linker from the **cc65** toolchain:

- `ca65` — 6502-family assembler
- `ld65` — linker

The assembler is explicitly configured for the **65C02** instruction set.

### Hardware Build

From the `kitbios` directory:

```bash
make
```

This assembles the source files and links them using `memory.conf`.

The resulting BIOS image is:

```text
bin/kitbios.bin
```

Assembly listings and linker map information are written to the build
directory, which can be useful when debugging low-level code or examining the
final memory layout.

### Simulator Build

A separate BIOS image can be generated for the Kit-1 simulation environment:

```bash
make sim
```

This builds the source with the `SIM` assembler symbol defined and produces:

```text
bin/kitbios-sim.bin
```

The conditional simulator build allows hardware-dependent portions of KitBIOS
to be adapted while retaining the same core BIOS source.

### Cleaning

Remove generated build products with:

```bash
make clean
```

This removes the `build/` and `bin/` directories.

## Build Process

The build pipeline is intentionally straightforward:

```text
              65C02 Assembly
                     │
                     ▼
                   ca65
                     │
                     ▼
              Object Files
                     │
                     ▼
                   ld65
                     │
              memory.conf
                     │
                     ▼
                KitBIOS Image
                     │
           ┌─────────┴─────────┐
           │                   │
           ▼                   ▼
    kitbios.bin        kitbios-sim.bin
      Hardware             Simulator
```

For the normal build, `ca65` generates 65C02 object files that are linked by
`ld65` according to the memory layout defined in `memory.conf`.

The simulator build follows the same process but defines `SIM` during assembly.

## Hardware Context

KitBIOS was written specifically for the Kit-1 computer.

The Kit-1 is built around a WDC W65C02 and uses traditional 65xx peripheral
hardware:

- **W65C02** — primary CPU
- **65C51 ACIA** — asynchronous serial communications
- **65C22 VIA** — parallel I/O and microSD interfacing
- **SRAM** — system memory
- **PIC18F47K40** — bootstrap controller / Virtual ROM

During a hard reset, the PIC temporarily takes control of the system bus and
copies KitBIOS into SRAM while the W65C02 is held in reset. Once the transfer is
complete, the PIC releases the bus and the processor begins executing KitBIOS
from RAM.

This architecture provides ROM-like bootstrap behavior without permanently
mapping a physical ROM into the W65C02's 64 KiB address space.

## Development and Simulation

KitBIOS was designed so that development does not depend exclusively on the
physical Kit-1 hardware.

The separate `SIM` build supports the Kit-1 project's 65C02 simulation
environment, allowing BIOS code to be exercised on a development computer.

This provides two complementary development paths:

```text
                  KitBIOS Source
                        │
               ┌────────┴────────┐
               │                 │
               ▼                 ▼
        Hardware Build     Simulator Build
               │                 │
               ▼                 ▼
           Kit-1              py65
           W65C02             65C02
```

Simulation is particularly useful for testing monitor behavior and other
software-level functionality before moving to the physical machine.

## Design Highlights

KitBIOS demonstrates several aspects of low-level system-software development:

- **65C02 assembly programming** — the BIOS executes directly on the Kit-1 CPU.
- **Bare-metal development** — there is no underlying operating system or
  runtime environment.
- **Memory-mapped I/O** — firmware communicates directly with the Kit-1
  peripheral hardware.
- **Serial communications** — the BIOS provides terminal I/O through the
  machine's 65C51 interface.
- **Block storage** — BIOS services expose sector-level access to the microSD
  interface.
- **Machine monitor** — KitMon provides an interactive environment for
  inspecting and manipulating the computer at a low level.
- **Hardware abstraction** — callable BIOS routines isolate higher-level
  software from some device-specific I/O details.
- **Custom memory layout** — `ld65` and `memory.conf` control placement of the
  firmware within the W65C02 address space.
- **Conditional assembly** — the same source tree supports both physical
  hardware and simulation.
- **Hardware/software co-design** — KitBIOS is closely coupled to the Kit-1
  memory map, peripheral architecture, and PIC-based bootstrap process.

## Relationship to Kit-1

KitBIOS is one component of the larger Kit-1 project:

```text
                  Kit-1
                    │
        ┌───────────┼───────────┐
        │           │           │
        ▼           ▼           ▼
     Hardware    KitBIOS     PIC Firmware
        │           │           │
        │           │           │
        └───────────┼───────────┘
                    │
                    ▼
             Working Computer
```

The hardware provides the 65C02 execution environment and peripherals, the PIC
firmware bootstraps the machine, and KitBIOS provides the low-level software
environment used once the CPU begins execution.

## License

KitBIOS is available under the **Apache License, Version 2.0**.

Copyright © 2019 Ryan Clarke

See the Kit-1 repository's license information for the complete terms.