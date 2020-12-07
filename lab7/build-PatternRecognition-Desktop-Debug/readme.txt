/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i sekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
 *
 **********************************************************************/
    
      N       brute			sortering
 -------------------------------------------------------------------
    150      29,4 ms			48,4 ms
    200	     68,8 ms			92,6 ms
    300	     209,4 ms			197 ms
    400	     491,2 ms			333,8 ms
    800	     3868,2 ms			1337 ms
   1600	     30 544 ms			2607 ms
   3200	     241 297,6 ms		10620,2 ms
   6400	     190 625 1 ms		44231 ms
  12800	     15 059 383,2 ms		192311 ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N⁴) vid värstafallstiden ty det är 4 for-loopar i varandra. 

Sortering: 
