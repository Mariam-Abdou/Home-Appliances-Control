#ifndef BITWISE_OPERATIONS_H
#define BITWISE_OPERATIONS_H

#define SET_BIT(REG, BIT)     ((REG) |= (1 << (BIT))) 

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(1 << (BIT)))

#define TOGGLE_BIT(REG, BIT)  ((REG) ^= (1 << (BIT)))

#define GET_BIT(REG, BIT)     (((REG) >> (BIT)) & 1)



#endif // BITWISE_OPERATIONS_H









