## Kernel Hidden Execute

To hide codes/data in the kernel address space.

## System requirements

Windows 7 or higher, 64-bit.

## Mechanism

Using the method of modifying PTEs, switch specific PTEs to the hidden pages before executing hidden codes or reading hidden data, and switch back to the original page after executing or reading.

In order to hide real codes or data in the non-mapped physical pages, and clean original codes
 or data before calling the hidden functions, we should map the physical pages to correct position.
If we have to call windows API in our hidden functions, we should call the transfer functions(not hidden).

### Features of transfer functions

- check & change IRQL
- restore & rewrite page table(PTEs)
- call specific APIs

## Develop environment

- Visual Studio 2019
- Windows SDK 10
- Windows Driver Kit 10
- QT5.12 for MSVC