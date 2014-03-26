#ifndef __focus_h__
#define __focus_h__

/* returns true if the AF/MF switch is in the MF position, or you have a manual lens */
int is_manual_focus();

/* enqueue some focus steps in the focus task */
void lens_focus_enqueue_step(int dir);

/* abort the current rack focus operation, if any */
void lens_focus_stop( void );

/* for rack focus menu */
int handle_rack_focus_menu_overrides(struct event * event);
void reset_override_zoom_buttons();

/* DOF info in menu (the fine print) */
void display_lens_hyperfocal();

int is_follow_focus_active();
int get_follow_focus_mode();
int get_follow_focus_dir_h();
int get_follow_focus_dir_v();

/* trap focus */
int can_lv_trap_focus_be_active();
int get_lv_focus_confirmation();

int get_focus_confirmation();

/* focus stacking */
int is_focus_stack_enabled();

/* private stuff (focus stacking code tigtly coupled with HDR bracketing stuff */
void focus_stack_run(int skip_frame);
#endif
