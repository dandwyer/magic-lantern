/** \file
 * Entry points into the firmware image.
 *
 * These are the functions that we can call from our tasks
 * in the Canon 2.0.3 firmware for the EOS M.
 *
 */
/*
 * Copyright (C) 2012 Magic Lantern Team
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#include <stub.h>

.text


#define RAM_OFFSET (0xFFA6AF40 - 0x1900) // some functions are copied to RAM at around ff0c009c; they have to be called from RAM...

/** Startup **/
NSTUB( ROMBASEADDR, firmware_entry )
NSTUB(0xFF0C1C10,  cstart)
NSTUB(0xFFAA0518 - RAM_OFFSET,  bzero32)
NSTUB(0xFFA6C4F8 - RAM_OFFSET,  create_init_task)           // 2EB8
NSTUB(0xFF0C5480,  init_task)

/** File I/O **/
NSTUB(0xFF346544, _FIO_OpenFile)
NSTUB(0xFF346600, _FIO_CreateFile)
NSTUB(0xFF3466AC, _FIO_RemoveFile)
NSTUB(0xFF346754,  FIO_ReadFile)
NSTUB(0xFF346804,  FIO_SeekSkipFile)
NSTUB(0xFF3468F4,  FIO_WriteFile)
NSTUB(0xFF3469A4,  FIO_CloseFile)
NSTUB(0xFF346B20, _FIO_GetFileSize)
NSTUB(0xFF347038, _FIO_RenameFile)
NSTUB(0xFF347200, _FIO_CreateDirectory)
NSTUB(0xFF3477C8, _FIO_FindFirstEx)
NSTUB(0xFF3478BC,  FIO_FindNextEx)
NSTUB(0xFF34799C,  FIO_FindClose)                           // proper name: FindClose

/** GUI **/
NSTUB(   0x3E154,  gui_main_struct)
NSTUB(   0x58DA0,  gui_task_list)
NSTUB(0xFF0D7350,  gui_main_task)
NSTUB(0xFF0D7724,  GUI_Control)
NSTUB(0xFF0D7DC8,  gui_init_end)
NSTUB(0xFF1A810C,  SetGUIRequestMode)

/** ASIF **/
NSTUB(0xFF134D94,  PowerMicAmp)
NSTUB(0xFF1351A0,  PowerAudioOutput)                        // Look for actrlCpowerControl Case 1 Sub
NSTUB(0xFF133150,  SetAudioVolumeOut)
NSTUB(0xFF1345B4,  SetSamplingRate)
NSTUB(0xFF10A724,  StartASIFDMAADC)                         // To Regular
NSTUB(0xFF10A9D0,  SoundDevShutDownIn)                      // Temporarily using address for StopASIFDMAADC to resolve MLV_SND issue
NSTUB(0xFF10A9D0,  StopASIFDMAADC)                          // Regular -- Stop ASIF ADC - needed for future changes to mlv_snd.c
NSTUB(0xFF10AAF8,  StartASIFDMADAC)                         // Needs Patches Or
NSTUB(0xFF10AD78,  StopASIFDMADAC)                          // NormalStopAsif
NSTUB(0xFF10B240,  SetNextASIFADCBuffer)                    // Int16
NSTUB(0xFF10B428,  SetNextASIFDACBuffer)                    // Int16 Regular
NSTUB(0xFF10D1F8,  SoundDevActiveIn)

/** Audio **/
NSTUB(   0x3E46C,  sounddev)
NSTUB(0xFF339540, _audio_ic_write)                          // str:i2c(int *array)
NSTUB(0xFF339B8C, _audio_ic_read)                           // Good Candidate i2c read
NSTUB(0xFF7FBC90,  audio_thresholds)
NSTUB(0xFF10CDF0,  sounddev_task)

/** Bitmap **/
NSTUB(   0x6BAB4,  LCD_Palette)                             // in InitializeBitmapDisplayDevice, right after 0xc0f14800
NSTUB(   0x6D2B4,  bmp_vram_info)                           // look in SetBitmapVramAddress - as in 60D

/** CFN **/
NSTUB(0xFF681968,  GetCFnData)
NSTUB(0xFF681B80,  SetCFnData)

/** Camera interface? **/
NSTUB(0xC0220000,  camera_engine)

/** DMA **/
NSTUB(0xFFA74280 - RAM_OFFSET,  dma_memcpy)

/** Debug messages **/
NSTUB(   0x3EC7C,  dm_names)
NSTUB(0xFFA6D714 - RAM_OFFSET,  DryosDebugMsg)
NSTUB(0xFFA6DA80 - RAM_OFFSET,  dm_set_store_level)

/** Dialog API **/
NSTUB(0xFF4C49AC,  dialog_redraw)
NSTUB(0xFF52F7F8,  dialog_set_property_str)

/** Dialog handlers **/
NSTUB(0xFF3BC128,  PlayMain_handler)
NSTUB(0xFF520A10,  ErrForCamera_handler)                    // ERR70, ERR80 etc (DlgErrForCamera.c, AJ_DIALOG.HANDLER_DlgErrForCamera.c)
NSTUB(0xFF5380BC,  HideUnaviFeedBack_maybe)                 // look for StartUnaviFeedBackTimer
NSTUB(0xFF53A608,  LiveViewApp_handler)
NSTUB(0xFF541C84,  ShootOlcApp_handler)                     // AJ_DIALOG.HANDLER_DlgShootOlcInfo.c
NSTUB(0xFF554194,  PlayMovieGuideApp_handler)
NSTUB(0xFF6A2EB4,  ErrCardForLVApp_handler)
NSTUB(0xFF6FBDF8,  LiveViewShutterApp_handler)

/** Display **/

/** EDMAC **/
NSTUB(0xFFA85C3C - RAM_OFFSET,  SetEDmac)
NSTUB(0xFFA85CE8 - RAM_OFFSET,  ConnectWriteEDmac)
NSTUB(0xFFA85DAC - RAM_OFFSET,  ConnectReadEDmac)
NSTUB(0xFFA85F54 - RAM_OFFSET,  StartEDmac)
NSTUB(0xFFA86140 - RAM_OFFSET,  RegisterEDmacCompleteCBR)
NSTUB(0xFFA8617C - RAM_OFFSET,  UnregisterEDmacCompleteCBR)
NSTUB(0xFFA86228 - RAM_OFFSET,  RegisterEDmacAbortCBR)
NSTUB(0xFFA86264 - RAM_OFFSET,  UnregisterEDmacAbortCBR)
NSTUB(0xFFA862BC - RAM_OFFSET,  RegisterEDmacPopCBR)
NSTUB(0xFFA862F8 - RAM_OFFSET,  UnregisterEDmacPopCBR)

/** Electronic Level **/

/** Engio **/
NSTUB(0xFF2C1744, _EngDrvOut)                               // AJ_EngDrvOut_1xVar_to_ShadowStruct
NSTUB(0xFF2C1A5C, _engio_write)
NSTUB(0xFF2C17E0,  shamem_read)                             // AJ_0x8FB0_engio_struct_n_R0_manipulation_to_get_ptr

/** Eventprocs (call by name) **/
NSTUB(0xFF137CCC,  call)

/** Events **/
NSTUB(0xFFA8B28C - RAM_OFFSET,  TryPostStageEvent)
NSTUB(0xFFA8B310 - RAM_OFFSET,  TryPostStageEvent_end)
NSTUB(0xFFA8B96C - RAM_OFFSET,  TryPostEvent)
NSTUB(0xFFA8B9F0 - RAM_OFFSET,  TryPostEvent_end)

/** ExMem **/
NSTUB(0xFF0E768C,  SRM_AllocateMemoryResourceFor1stJob)
NSTUB(0xFF0EB6EC,  SRM_FreeMemoryResourceFor1stJob)
NSTUB(0xFF13B870,  AllocateMemoryResource)                  // m_pfAllocMemoryCBR
NSTUB(0xFF13B8BC,  AllocateContinuousMemoryResource)        // m_pfContAllocMemoryCBR
NSTUB(0xFF13B9D4,  FreeMemoryResource)                      // m_pfFreeMemoryCBR
NSTUB(0xFFA71264 - RAM_OFFSET,  GetSizeOfMaxRegion)
NSTUB(0xFFA7217C - RAM_OFFSET,  CreateMemoryChunk)          // called from CreateMemorySuite
NSTUB(0xFFA72720 - RAM_OFFSET,  GetMemoryAddressOfMemoryChunk)
NSTUB(0xFFA72C78 - RAM_OFFSET,  AddMemoryChunk)             // called before " 32(Src,bytes,Unit)=(%#lx,%#lx,%#lx)" in many places; see also hAddSuite
NSTUB(0xFFA72D48 - RAM_OFFSET,  GetFirstChunkFromSuite)     // AJ_PackMemory_PackMem_p3
NSTUB(0xFFA734E4 - RAM_OFFSET,  GetNextMemoryChunk)

/** GUI for old cameras **/

/** GUI timers **/
NSTUB(0xFF52CE78,  CancelDateTimer)
NSTUB(0xFFA6ED90 - RAM_OFFSET,  SetHPTimerAfterNow)
NSTUB(0xFFA6EE80 - RAM_OFFSET,  SetHPTimerNextTick)
NSTUB(0xFFA752F8 - RAM_OFFSET,  SetTimerAfter)
NSTUB(0xFFA754F8 - RAM_OFFSET,  CancelTimer)

/** H264 Encoder **/
NSTUB(   0x4C124,  mvr_config)
NSTUB(0xFF2C04EC,  mvrSetDefQScale)
NSTUB(0xFF2C09F4,  mvrFixQScale)

/** Interrupts **/
NSTUB(0xFFAA7808 - RAM_OFFSET,  pre_isr_hook)
NSTUB(0xFFAA780C - RAM_OFFSET,  post_isr_hook)

/** LCD Sensor **/

/** Making the card bootable **/
NSTUB(   0x606DC,  sd_device)
NSTUB(0xFF4F83F8,  fsuDecodePartitionTable)                 // AJ_fsuGetPart_related

/** Memory allocation **/
NSTUB(0xFF0C8360, _malloc)
NSTUB(0xFF0C83B8, _free)                                    // see "can't malloc"
NSTUB(0xFFA712B8 - RAM_OFFSET,  GetMemoryInformation)
NSTUB(0xFFA71518 - RAM_OFFSET, _AllocateMemory)
NSTUB(0xFFA718B4 - RAM_OFFSET, _FreeMemory)
NSTUB(0xFFA72794 - RAM_OFFSET,  DeleteMemorySuite)
NSTUB(0xFFA7299C - RAM_OFFSET,  CreateMemorySuite)
NSTUB(0xFFA8BBB4 - RAM_OFFSET, _alloc_dma_memory)
NSTUB(0xFFA8BBE8 - RAM_OFFSET, _free_dma_memory)

/** Message queues **/
NSTUB(0xFFA73D34 - RAM_OFFSET,  msg_queue_create)
NSTUB(0xFFA88298 - RAM_OFFSET,  msg_queue_receive)          // 1EC58
NSTUB(0xFFA88484 - RAM_OFFSET,  msg_queue_post)             // 1EE44
NSTUB(0xFFA884C4 - RAM_OFFSET,  msg_queue_count)            // 0x1EE84 Above "!!!!!!! QUE Overflo"

/** PTP **/
NSTUB(0xFF45FC8C,  ptp_register_handler)

/** Properties **/
NSTUB(0xFF11F9C0,  prop_register_slave)
NSTUB(0xFF11FBB4, _prop_request_change)
NSTUB(0xFF120170,  prop_deliver)
NSTUB(0xFF12023C, _prop_cleanup)
///NSTUB(0xFF121824,  PROPAD_GetPropertyData)                  /* present on 7D.203, 60D.111, 6D.113, 5D3.113, 50D.109, 5D2.212, 600D.102, 550D.109 */

/** RPC (for 7D) **/

/** Recursive locks **/
NSTUB(0xFFA73F1C - RAM_OFFSET,  CreateRecursiveLock)
NSTUB(0xFFA885D0 - RAM_OFFSET,  AcquireRecursiveLock)       // AJ_KernelDry_KerRLock.c
NSTUB(0xFFA886E4 - RAM_OFFSET,  ReleaseRecursiveLock)       // AJ_KernelDry_KerRLock.c_p2

/** ResLock **/
NSTUB(0xFF2C58F8,  CreateResLockEntry)
NSTUB(0xFF2C5DC0,  LockEngineResources)
NSTUB(0xFF2C5F64,  UnLockEngineResources)

/** Semaphores **/
NSTUB(0xFFA6FF98 - RAM_OFFSET,  create_named_semaphore)
NSTUB(0xFFA700F8 - RAM_OFFSET,  take_semaphore)
NSTUB(0xFFA701E4 - RAM_OFFSET,  give_semaphore)

/** Task info **/
NSTUB(   0x3F14C,  task_max)
NSTUB(0xFFA6BB6C - RAM_OFFSET,  get_current_task)
NSTUB(0xFFA784AC - RAM_OFFSET,  get_obj_attr)               // AJ_checks_if_Process_id_created_by_Dryos
NSTUB(0xFFA965E0 - RAM_OFFSET,  is_taskid_valid)            // AJ_task_trampoline_related_p10

/** Task sleep **/
NSTUB(0xFFA705D4 - RAM_OFFSET,  msleep)                     // 6F94

/** Tasks **/
NSTUB(   0x3DD60,  task_dispatch_hook)
NSTUB(0xFFA70688 - RAM_OFFSET,  task_create)
NSTUB(0xFFA759A0 - RAM_OFFSET,  task_trampoline)


/** Misc **/
NSTUB(0xFF1321C8,  LoadCalendarFromRTC)
NSTUB(0xFFA89C0C - RAM_OFFSET,  vsnprintf)                  // 205CC













