

#ifndef MTIMER_H
#define	MTIMER_H

// Timer0 _ Clock Selection Options
#define Timer0_OFF          0
#define Timer0_PRE_Non      1
#define Timer0_PRE_8        2
#define Timer0_PRE_64       3
#define Timer0_PRE_256      4
#define Timer0_PRE_1024     5
#define Timer0_Falling_Edge 6
#define Timer0_Rising_Edge  7


// Timer0 _ Modes
#define Timer0_Normal       0       // (WGM01 = 0, WGM00 = 0)
#define Timer0_CTC          1       // (WGM01 = 1, WGM00 = 0)
#define Timer0_PWM          2       // (WGM01 = 0, WGM00 = 1)
#define Timer0_FPWM         3       // (WGM01 = 1, WGM00 = 1)

// Timer0_OC0_Normal modes
#define Timer0_Normal_OC0_disconnect    0
#define Timer0_Normal_OC0_toggle        1
#define Timer0_Normal_OC0_clear         2
#define Timer0_Normal_OC0_set           3

// Timer0_OC0_PWM modes
#define Timer0_PWM_OC0_disconnect       0
#define Timer0_PWM_OC0_clear_set        2
#define Timer0_PWM_OC0_set_clear        3

// Timer0_OC0_FPWM modes
#define Timer0_FPWM_OC0_disconnect       0
#define Timer0_FPWM_OC0_clear_set        2
#define Timer0_FPWM_OC0_set_clear        3

#define DutyCycle_50                     50

void Timer0_select_CLK(char Clock_Select);
void Timer0_select_Mode(char Timer0_mode);
void Timer0_select_OC0_mode(char Timer0_OC0_mode);
void Timer0_enable_OVIE();
void Timer0_enable_OCIE();

void Timer0_set_DutyCycle(char DutyCycle_percentage);

void init_Timer0(char Timer0_mode,
        char Timer0_OC0_mode,
        char Timer0_OC0_DutyCycle,
        char Timer0_Prescalar
        );

void PWM_init();



#endif	/* MTIMER_H */

