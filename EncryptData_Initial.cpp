// EncryptData.cpp
//
// This file uses the input data and key information to encrypt the input data
//

#include "Main.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// code to encrypt the data as specified by the project assignment
int encryptData(char *data, int dataLength)
{
	int resulti = 0;

	gdebug1 = 0;					// a couple of global variables that could be used for debugging
	gdebug2 = 0;					// also can have a breakpoint in C code

	// You can not declare any local variables in C, but should use resulti to indicate any errors
	// Set up the stack frame and assign variables in assembly if you need to do so
	// access the parameters BEFORE setting up your own stack frame
	// Also, you cannot use a lot of global variables - work with registers

	__asm {
		// you will need to reference some of these global variables
		// (gptrPasswordHash or gPasswordHash), (gptrKey or gkey), gNumRounds

		/* simple example that xors 2nd byte of data with 14th byte in the key file
		lea esi,gkey				// put the ADDRESS of gkey into esi
		mov esi,gptrKey;			// put the ADDRESS of gkey into esi (since *gptrKey = gkey)

		lea	esi,gPasswordHash		// put ADDRESS of gPasswordHash into esi
		mov esi,gptrPasswordHash	// put ADDRESS of gPasswordHash into esi (since unsigned char *gptrPasswordHash = gPasswordHash)

		mov al,byte ptr [esi]				// get first byte of password hash
		mov al,byte ptr [esi+4]				// get 5th byte of password hash
		mov ebx,2
		mov al,byte ptr [esi+ebx]			// get 3rd byte of password hash
		mov al,byte ptr [esi+ebx*2]			// get 5th byte of password hash

		mov ax,word ptr [esi+ebx*2]			// gets 5th and 6th bytes of password hash ( gPasswordHash[4] and gPasswordHash[5] ) into ax
		mov eax,dword ptr [esi+ebx*2]		// gets 4 bytes, as in:  unsigned int X = *( (unsigned int*) &gPasswordHash[4] );

		mov al,byte ptr [gkey+ebx]			// get's 3rd byte of gkey[] data

		mov al,byte ptr [gptrKey+ebx]		// THIS IS INCORRECT - will add the address of the gptrKey global variable (NOT the value that gptrKey holds)

		mov al,byte ptr [esi+0xd];			// access 14th byte in gkey[]: 0, 1, 2 ... d is the 14th byte
		mov edi,data				// Put ADDRESS of first data element into edi
		xor byte ptr [edi+1],al		// Exclusive-or the 2nd byte of data with the 14th element of the keyfile
									// NOTE: Keyfile[14] = 0x21, that value changes the case of a letter and flips the LSB
									// Capital "B" = 0x42 becomes lowercase "c" since 0x42 xor 0x21 = 0x63
		*/


		xor ebx,ebx					// reset ecx to 0
		startOfLoop:
		mov edx, data				// moves the address of data into edx
		add edx, ebx				// add ecx(index) to edx
		/* Milestone 1 code
		xor byte ptr[edx],0x1		// xor data at index ecx with a 1 (0x1)
		*/
		
		//C - start
		xor eax,eax					// reset eax to 0
		mov al, byte ptr[edx]		// get ecx-th byte into al
		xor bl,bl					// clear bl
		xor cl,cl					//
		mov cl,8					// 
	RLOOP:							// loop to put the reveresed al into bl
		rcr al,1
		rcl bl,1
		loop RLOOP
		mov byte ptr[edx],bl		//move the reversed byte into the data
		//C - end

		//D - start
		xor eax, eax				// reset eax to 0
		mov al, byte ptr[edx]		// get ecx-th byte into al
		rol ax
		rol ax
		rol ax
		rol ax
		test ah,8
		jz bit4_is_zero
		rol ah
		or ah,1
		and ah,0xEF
		jmp doneah
	bit4_is_zero:
		rol ah
	doneah:
		test al,16
		jz bit5_is_zero
		ror al
		or al,0x80
		and al,0x8
		jmp doneal
	bit5_is_zero:
		ror al
	doneal:
		ror ax
		ror ax
		ror ax
		ror ax
		mov byte ptr[edx],al
		//D - end

		inc ebx						// increment ecx(index)
		cmp ebx,dataLength			// check if ecx is lower than dataLength
		jb startOfLoop				// jump to startOfLoop if ecx is lower than dataLength
		
	done:
		nop
	}

	return resulti;
} // encryptData