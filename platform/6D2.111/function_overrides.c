// functions 6D2/105

// SJE overrides for functions I couldn't find stubs for,
// as well as ones that I think function sig has changed,
// so we can define wrappers.

#include <dryos.h>
#include <property.h>
#include <bmp.h>
#include <config.h>
#include <consts.h>
#include <lens.h>
#include <tasks.h>
#include <edmac.h>

struct chs_entry
{
    uint8_t head;
    uint8_t sector; //sector + cyl_msb
    uint8_t cyl_lsb;
}__attribute__((packed));

struct partition
{
    uint8_t  state;
    struct   chs_entry start;
    uint8_t  type;
    struct   chs_entry end;
    uint32_t start_sector;
    uint32_t size;
}__attribute__((aligned,packed));

struct partition_table
{
    uint8_t  state; // 0x80 = bootable
    uint8_t  start_head;
    uint16_t start_cylinder_sector;
    uint8_t  type;
    uint8_t  end_head;
    uint16_t end_cylinder_sector;
    uint32_t sectors_before_partition;
    uint32_t sectors_in_partition;
}__attribute__((packed));

void fsuDecodePartitionTable(void *partIn, struct partition_table *pTable){
    struct partition *part = (struct partition *)partIn;
    pTable->state = part->state;
    pTable->type = part->type;
    pTable->start_head = part->start.head;
    pTable->end_head = part->end.head;
    pTable->sectors_before_partition = part->start_sector;
    pTable->sectors_in_partition = part->size;

    //tricky bits - TBD
    pTable->start_cylinder_sector = 0;
    pTable->end_cylinder_sector = 0;
}

void LoadCalendarFromRTC(struct tm *tm)
{
    _LoadCalendarFromRTC(tm, 0, 0, 16);
}

#ifndef CONFIG_INSTALLER
extern struct task* first_task;
int get_task_info_by_id(int unknown_flag, int task_id, void *task_attr)
{
    // task_id is something like two u16s concatenated.  The flag argument,
    // present on D45 but not on D678 allows controlling if the task info request
    // uses the whole thing, or only the low half.
    //
    // ML calls with this set to 1, meaning task_id is used as is,
    // if 0, the high half is masked out first.
    //
    // D678 doesn't have the 1 option, we use the low half as index
    // to find the full value.
    struct task *task = first_task + (task_id & 0xffff);
    return _get_task_info_by_id(task->taskId, task_attr);
}
#endif

void SetEDmac(unsigned int channel, void *address, struct edmac_info *ptr, int flags)
{
    return;
}

void ConnectWriteEDmac(unsigned int channel, unsigned int where)
{
    return;
}

void ConnectReadEDmac(unsigned int channel, unsigned int where)
{
    return;
}

void StartEDmac(unsigned int channel, int flags)
{
    return;
}

void AbortEDmac(unsigned int channel)
{
    return;
}

void RegisterEDmacCompleteCBR(int channel, void (*cbr)(void*), void* cbr_ctx)
{
    return;
}

void UnregisterEDmacCompleteCBR(int channel)
{
    return;
}

void RegisterEDmacAbortCBR(int channel, void (*cbr)(void*), void* cbr_ctx)
{
    return;
}

void UnregisterEDmacAbortCBR(int channel)
{
    return;
}

void RegisterEDmacPopCBR(int channel, void (*cbr)(void*), void* cbr_ctx)
{
    return;
}

void UnregisterEDmacPopCBR(int channel)
{
    return;
}

void _EngDrvOut(uint32_t reg, uint32_t value)
{
    return;
}

uint32_t shamem_read(uint32_t addr)
{
    return 0;
}

void _engio_write(uint32_t* reg_list)
{
    return;
}

unsigned int UnLockEngineResources(struct LockEntry *lockEntry)
{
    return 0;
}
