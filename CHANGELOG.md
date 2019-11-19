# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- FAT16 initialization that verifies first partition is FAT16, loads the boot
sector, and computes the root directory region.
### Changed
- Initialize FAT16 in RAM after SD card setup.
- Simulation loads pre-fabricated FAT16 image into RAM.

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
