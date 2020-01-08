# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Changed
- Refactored code to Hungarian notation.

## [0.2.0] - 2020-01-06
### Added
- FAT16 initialization routine that verifies first partition is FAT16, loads the
boot sector, and computes the FAT, root directory, and data region start
sectors.
- FAT16 find routine that finds a file and returns its starting cluster.
- FAT16 read routine that loads a file from disk into RAM.
### Changed
- Initialize FAT16, find KITOS.BIN, and load into RAM after SD card setup.
- Simulation loads pre-fabricated SD card image into RAM.
- Used ```generic``` and ```longbranch``` macro packages where it makes sense.
- Added color to top level makefile for readability when making project.
- Swap gcc for clang in ```bin2c``` makefile.
- Minor changes to ```bin2c``` source to address warnings.
- Minor style change to KitBIOS makefile.
- Adjusted zero page addresses to reflect removal of general purpose registers.
### Removed
- General purpose registers in first 16 bytes of zero page.

## [0.1.7] - 2019-11-09
### Changed
- Updated ```stack``` command in KitMon to be more efficient.

## [0.1.6] - 2019-11-09
### Changed
- Updated ```load``` and ```write``` commands in KitMon to be more efficient.

## [0.1.5] - 2019-11-09
### Changed
- Updated ```register``` command in KitMon to be more efficient.
- Updated Makefile output headers for better readability.

## [0.1.4] - 2019-11-06
### Changed
- Updated ```jump``` command in KitMonto be more efficient and removed CALL
code.

## [0.1.3] - 2019-11-05
### Changed
- Updated ```fill``` command in KitMon to be more efficient.
- Updated ```help``` command source comments.

## [0.1.2] - 2019-10-30
### Changed
- Updated ```enter``` command in KitMon to be more efficient.

## [0.1.1] - 2019-10-17
### Changed
- Updated ```dump``` command in KitMon to output 128 bytes (8 lines).

## [0.1.0] - 2019-10-16
### Added
- Initial commit.
- Working serial interface, SD card interface, uptime counter, and ROM monitor.
