/******************************************************************************
 *                                                                            *
 *************************  SWC     : SSD_interface   *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/ 


#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

/* Macros for SSD id */
typedef enum
{
 SSD_1,
 SSD_2
}SSD_IDs;


                   /*************** APIS PROTO TYPES ***************/

void SSD_voidInit                    (void);
void SSD_voidDisplayNumber           (u8 copy_u8DesiredNumber, u8 copy_u8Id);
void SSD_voidDisplayMultiplexedNumber(u8 copy_u8DesiredNumber);

#endif /* SSD_INTERFACE_H_ */
