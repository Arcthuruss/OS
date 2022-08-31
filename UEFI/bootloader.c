#include <efi.h>
#include <efilib.h>

void write_string( int color, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = color;
    }
}

EFI_STATUS
EFIAPI
efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_LOADED_IMAGE *loaded_image = NULL;
    EFI_STATUS status;
    InitializeLib(ImageHandle, SystemTable);

    status = uefi_call_wrapper(SystemTable->BootServices->HandleProtocol,
        3, ImageHandle, &LoadedImageProtocol, (void **)&loaded_image);
    if (EFI_ERROR(status)) {
        Print(L"handleprotocol: %r\n", status);
        return EFI_SUCCESS;
    }

    /* GetMemoryMap */
    UINTN MemoryMapSize = sizeof(EFI_MEMORY_DESCRIPTOR) * 0x10;
    EFI_MEMORY_DESCRIPTOR *MemoryMap = AllocatePool (MemoryMapSize);
    UINTN MapKey = 0;
    UINTN DescriptorSize = 0;
    UINT32 DescriptorVersion = 0;
    status = uefi_call_wrapper(SystemTable->BootServices->GetMemoryMap,
        &MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (EFI_ERROR(status)) {
        Print(L"GetMemoryMap: %r\n", status);
        return EFI_SUCCESS;
    }

    /* ExitBootServices */
    status = uefi_call_wrapper(SystemTable->BootServices->ExitBootServices,
        ImageHandle, MapKey);
    if (EFI_ERROR(status)) {
        Print(L"ExitBootServices: %r\n", status);
        return EFI_SUCCESS;
    }

    write_string(0x07, "example");
}