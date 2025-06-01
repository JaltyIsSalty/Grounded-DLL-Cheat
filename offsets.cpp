#include <windows.h>
#include "offsets.h"

bool IsWritableAddress(uintptr_t address)
{
	MEMORY_BASIC_INFORMATION mbi = {};
	if (VirtualQuery((LPVOID)address, &mbi, sizeof(mbi)))
	{
		DWORD protect = mbi.Protect;

		// Allow readable memory pages (writable or not), but still skip noaccess/guard
		if (!(protect & (PAGE_NOACCESS | PAGE_GUARD)))
		{
			return true;
		}
	}
	return false;
}

namespace Get
{
	//Player X Coord
	extern float* ZCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x128);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x140);
		float* zCoord_Address = (float*)(ptr3 + 0x214);

		return zCoord_Address;
	}

	//Player Y Coord
	extern float* YCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x128);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x140);
		float* yCoord_Address = (float*)(ptr3 + 0x218);

		return yCoord_Address;
	}

	//Player Z Coord
	extern float* XCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x128);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x140);
		float* xCoord_Address = (float*)(ptr3 + 0x210);

		return xCoord_Address;
	}

	extern float* XWayPCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C0C48);
		float* XWayPCoordAddress = (float*)(ptr1 + 0x18);

		return XWayPCoordAddress;
	}

	extern float* YWayPCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C0C48);
		float* YWayPCoordAddress = (float*)(ptr1 + 0x14);

		return YWayPCoordAddress;
	}

	extern float* ZWayPCoordAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C0C48);
		float* ZWayPCoordAddress = (float*)(ptr1 + 0x10);

		return ZWayPCoordAddress;
	}

	//Player Look Degree
	extern float* PlayerLookDegreeAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		if (!IsWritableAddress(base))
			return nullptr;
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		if (!IsWritableAddress(ptr1))
			return nullptr;
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x258);
		if (!IsWritableAddress(ptr2))
			return nullptr;
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0xF0);
		if (!IsWritableAddress(ptr3))
			return nullptr;
		float* PlayerLookDegree_Address = (float*)(ptr3 + 0x2BC);
		if (!IsWritableAddress(base))
			return nullptr;

		return PlayerLookDegree_Address;
	}

	//Player Current Damage Taken
	extern float* DamageTakenAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x1A8);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x0);
		float* DamageTakenAddress = (float*)(ptr3 + 0x284);

		return DamageTakenAddress;
	}

	extern float* StaminaAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x1B8);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x160);
		float* StaminaAddress = (float*)(ptr3 + 0xD8);

		return StaminaAddress;
	}

	extern float* HungerAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		uintptr_t ptr1 = *(uintptr_t*)(base + 0x059C32B0);
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x1A8);
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x30);
		float* Hunger = (float*)(ptr3 + 0x278);

		return Hunger;
	}

	extern float* ThirstAddress()
	{
		uintptr_t base = (uintptr_t)GetModuleHandleA("Maine-WinGDK-Shipping.exe");
		if (!IsWritableAddress(base))
			return nullptr;
		uintptr_t address1 = base + 0x059C32B0;
		if (!IsWritableAddress(address1))
			return nullptr;
		uintptr_t ptr1 = *(uintptr_t*)address1;
		if (!IsWritableAddress(ptr1))
			return nullptr;
		uintptr_t ptr2 = *(uintptr_t*)(ptr1 + 0x1A8);
		if (!IsWritableAddress(ptr2))
			return nullptr;
		uintptr_t ptr3 = *(uintptr_t*)(ptr2 + 0x30);
		if (!IsWritableAddress(ptr3))
			return nullptr;
		float* Thirst = (float*)(ptr3 + 0x27C);

		return Thirst;
	}
}


