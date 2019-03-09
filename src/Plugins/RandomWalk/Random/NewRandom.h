#ifndef __NEW_RANDOM_H__
#define __NEW_RANDOM_H__
/* initializes mt[N] with a seed */
void InitRandom(unsigned long s);

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
void InitRandomByArray(unsigned long init_key[], unsigned long key_length);

/* generates a random number on [0,0xffffffff]-interval */
unsigned long NewRandom(void);

#endif //__NEW_RANDOM_H__