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
    150      29,4 ms			23,6 ms
    200	     68,8 ms			43,6 ms
    300	     209,4 ms			94 ms
    400	     491,2 ms			158,2 ms
    800	     3868,2 ms			639,2 ms
   1600	     30 544 ms			2 607 ms
   3200	     241 297,6 ms		10 620,2 ms
   6400	     190 625 1 ms		44 231 ms
  12800	     15 059 383,2 ms		192 311 ms


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute: O(N⁴) vid värstafallstiden ty det är 4 for-loopar i varandra. 

Sortering: O(N³) ty 3 for-loopar i varandra.
