#ifndef __MDFN_MEDNAFEN_DRIVER_H
#define __MDFN_MEDNAFEN_DRIVER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "settings-common.h"

extern std::vector<MDFNGI *>MDFNSystems;

/* Indent stdout newlines +- "indent" amount */
void MDFN_indent(int indent);
void MDFN_printf(const char *format, ...);

#define MDFNI_printf MDFN_printf

/* Displays an error.  Can block or not. */
void MDFND_PrintError(const char *s);
void MDFND_Message(const char *s);

uint32 MDFND_GetTime(void);

#ifdef WANT_THREADING
/* Being threading support. */
// Mostly based off SDL's prototypes and semantics.
// Driver code should actually define MDFN_Thread and MDFN_Mutex.

struct MDFN_Thread;
struct MDFN_Mutex;
struct MDFN_Cond;

void MDFND_Sleep(uint32 ms);

MDFN_Thread *MDFND_CreateThread(int (*fn)(void *), void *data);
void MDFND_WaitThread(MDFN_Thread *thread, int *status);
void MDFND_KillThread(MDFN_Thread *thread);

MDFN_Mutex *MDFND_CreateMutex(void);
MDFN_Cond *MDFND_CreateCond(void);
void MDFND_DestroyCond(MDFN_Cond *cond);
void MDFND_DestroyMutex(MDFN_Mutex *mutex);
int MDFND_WaitCond(MDFN_Cond *cond, MDFN_Mutex *mutex);
int MDFND_SignalCond(MDFN_Cond *cond);
int MDFND_LockMutex(MDFN_Mutex *mutex);
int MDFND_UnlockMutex(MDFN_Mutex *mutex);

/* End threading support. */
#endif

/* path = path of game/file to load.  returns NULL on failure. */
MDFNGI *MDFNI_LoadGame(const char *force_module, const char *path);

MDFNGI *MDFNI_LoadCD(const char *sysname, const char *devicename);

/* Sets the base directory(save states, snapshots, etc. are saved in directories
   below this directory. */
void MDFNI_SetBaseDirectory(const char *dir);

void MDFN_DispMessage(const char *format, ...);
#define MDFNI_DispMessage MDFN_DispMessage

uint32 MDFNI_CRC32(uint32 crc, uint8 *buf, uint32 len);

// NES hackish function.  Should abstract in the future.
int MDFNI_DatachSet(const uint8 *rcode);

void MDFNI_DumpModulesDef(const char *fn);


#endif
