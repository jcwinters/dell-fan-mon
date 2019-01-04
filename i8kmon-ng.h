
#ifndef _I8KMON_NG_H
#define _I8KMON_NG_H

// dellfan start
#define DISABLE_BIOS_METHOD1 0x30a3
#define ENABLE_BIOS_METHOD1 0x31a3
#define DISABLE_BIOS_METHOD2 0x34a3
#define ENABLE_BIOS_METHOD2 0x35a3

#define DISABLE_BIOS_METHOD3 0x32a3
#define ENABLE_BIOS_METHOD3 0x33a3

struct smm_regs
{
    unsigned int eax;
    unsigned int ebx __attribute__((packed));
    unsigned int ecx __attribute__((packed));
    unsigned int edx __attribute__((packed));
    unsigned int esi __attribute__((packed));
    unsigned int edi __attribute__((packed));
};
void bios_fan_control(int);
void init_ioperm();
int i8k_smm(struct smm_regs *);
int send_smm(unsigned int, unsigned int);
// dellfan end

// i8kctl start
#define I8K_PROC "/proc/i8k"
#define I8K_FAN_LEFT 1
#define I8K_FAN_RIGHT 0

#define I8K_FAN_OFF 0
#define I8K_FAN_LOW 1
#define I8K_FAN_HIGH 2

#define I8K_GET_TEMP _IOR('i', 0x84, size_t)
#define I8K_GET_FAN _IOWR('i', 0x86, size_t)
#define I8K_SET_FAN _IOWR('i', 0x87, size_t)
void i8k_set_fan_status(int, int);
int i8k_get_fan_status(int);
int i8k_get_cpu_temp();
void i8k_open();
// i8kctl end

// i8kmon-ng
#define CFG_FILE "/etc/i8kmon-ng.conf"
#define MON_SPACE "   "
#define true 1
#define false 0

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

struct t_cfg
{
    int verbose;
    unsigned long period;
    unsigned long fan_check_period;
    int monitor_fan_id;
    unsigned long jump_timeout;
    int jump_temp_delta;
    int t_low;
    int t_mid;
    int t_high;
    int foolproof_checks;
    int daemon;
    int bios_disable_method;
    int monitor_only;
    int tick;
};

void monitor();
void monitor_show_legend();
void parse_args(int, char **);
void exit_failure();
void usage();

void signal_handler(int);
void signal_handler_init();

void cfg_load();
void cfg_set(char *, int, int);
void cfg_error(int);

int foolproof_error(char *);
void foolproof_checks();
#endif
