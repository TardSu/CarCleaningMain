#ifndef __INTERFACE_JQ6500_H__
#define __INTERFACE_JQ6500_H__

void JQ6500Listen(void);
void JQ6500Task100ms(void);

void JQ6500Volume(unsigned char vol);
void JQ6500PlayOne(unsigned char index);

#endif
