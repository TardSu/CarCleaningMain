#ifndef __INTERFACE_DISPLAY7SEG_H__
#define __INTERFACE_DISPLAY7SEG_H__

void Display7Segment(char *dat,unsigned char dot,unsigned char cmd1,unsigned char cmd2);

void Display7SegmentTime(time_t time);
void Display7SegmentMoney(double money);
void Display7SegmentMoneyBlink(double money);
void Display7SegmentNameMenu(char *dat,unsigned char dot,unsigned char cmddis);
void Display7SegmentTimeEdit(time_t time,unsigned char dot,unsigned char cmddis);
void Display7SegmentTimeSetting(time_t time);
void Display7SegmentNumEdit(unsigned int dat,unsigned char dot,unsigned char cmddis);

#endif
