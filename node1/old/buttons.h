#ifndef NODE1_BUTTONS_H
#define NODE1_BUTTONS_H


typedef struct {
    int left;
    int right;
} button_t;


void buttons_init(void);


button_t button_status_read(void);


void buttons_send_status_to_can(void);


#endif