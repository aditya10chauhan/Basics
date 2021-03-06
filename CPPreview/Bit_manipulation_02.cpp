/*  Bitwise Operators:
 *
 *  NOT ( ~ ):  1's complement, flip 0 to 1; 1 to 0
char a = 0xA5;	  // 1010.0101
char b = ~a;      // 0101.1010
 *
 *  AND ( & ):  operates on two equal-length bit patterns; 1 & 1 = 1, otherwise 0
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010
int r = x & y;    // 0100.0010
 *
 *  OR ( | ):   operates on two equal-length bit patterns; 0 | 0 = 0, otherwise 1
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010
int r = x | y;    // 0101.1011
 *
 *  XOR ( ^ ):  takes two equal-length bit patterns; 1 ^ 0 = 1; 0 ^ 1 = 1, otherwise 0
char x = 75;      // 0100.1011
char y = 82;      // 0101.0010			x ^ 0 = x
int r = x ^ y;    // 0001.1001			x ^ x = 0
 *
 *  Left Shift ( << ): appends 0s at the end; is equivalent to multiplying with 2^k ( if we are shifting k bits )
char x = 75;      // 0100.1011
char r = x << 4;  // 1011.0000
 *
 *  Right Shift ( >> ): appends 0s at the beginning;
char x = 75;      // 0100.1011
char r = x >> 4;  // 0000.0100
 *
 * /theory/ NOR
 There is no immediate operand NOR instruction. NOR is equivalent to performing the OR operation, 
 then complementing the bits (change 0 to 1 and 1 to 0): NOT X  =  X NOR 0
 */
 

// 0. Odd or even
// 1. Check if a given number is a power of 2, 4
// 2. Count the number of 1s in the binary representation of a number
// 3. Check if the ith bit is set (is 1) in the binary form of a number
// 4. Generate all the possible subsets of a set
// 5. Find the largest power of 2 (leftmost 1 in bin), less equal to N
// 6. Find the rightmost 1 in binary representation of x
// 7. Set nth bit
// 8. Sum of Two Integers without +
// 9. find 2 odd occuring elements in an array
 

// 0. Odd or even-----------------------------------------------------------------------------
if (number & 1) {
  // It's odd 
}

// 1. Check if a given number is a power of 2, 4----------------------------------------------
// x = 4 = (100)2
// x - 1 = 3 = (011)2 
// x & (x-1) = 4 & 3 = (100)2 & (011)2 = (000)2
 
 bool isPowerOfTwo(int x) {
	// x will check if x == 0 and !(x & (x - 1)) will check if x is a power of 2 or not
	return (x && !(x & (x - 1)));
 }

// Powers of two can have a 1 bit in either odd or even bit positions, but powers of 4 only have 1 bit in odd positions
// mathematically, 4^n - 1 can be divided by 3

bool isPowerOfFour(int num) {
    int mask = 0b01010101010101010101010101010101;
    return num > 0 && (num & (num - 1)) == 0 && (num | mask) == mask;
}
bool isPowerOfFour(int num) {
return (num > 0) && ((num & (num - 1)) == 0) && ((num & 0x55555555));
}
bool isPowerOfFour(int num) {
    return num > 0 && (num & (num - 1)) == 0 && (num - 1) % 3 == 0;
}
 
// 2. Count the number of 1s in the binary representation of a number------------------------
// 888 = (1101111000)2
// 887 = (1101110111)2
// in n and n-1 the rightmost 1 and bits right to it are flipped
// x & (x - 1) will reduce x to a number containing number of 1s (in its binary form) less than the previous state of x

int count_one (int n) {
    int count = 0;
    while( n ) {
	n = n & (n - 1);
	count++;
	}
    return count;
}

// Complexity: O(K), where K is the number of 1s

// 3. Check if the ith bit is set in the binary form of a number-----------------------------
// if non-zero number -> bit is set
 bool check (int N) {
        if( N & (1 << i) )
            return true;
        else
            return false;
    }

// 4. Generate all the possible subsets of a set---------------------------------------------
// for a set of N elements: each element has 2 possibilities - in set or not
// total number of subsets in 2^N, 	for 3 -> 2^3 = 8 subsets;  char A[]{ 'a', 'b', 'c' };
0 = (000)2 = {}
1 = (001)2 = {c}
2 = (010)2 = {b}
3 = (011)2 = {b, c}
4 = (100)2 = {a}
5 = (101)2 = {a, c}
6 = (110)2 = {a, b}
7 = (111)2 = {a, b, c}

void possibleSubsets(char A[], int N) {
	for (int i = 0; i < (1 << N); ++i) {
		for (int j = 0; j < N; ++j)
			if (i & (1 << j))
				std::cout << A[j] << ' ';
		std::cout << std::endl;
	}
}

// 5. Find the largest power of 2 (leftmost 1 in bin), less equal to N----------------------
// if all bits are 1s: 31 = {11111} = 32 - 1 = 2 * 16 - 1, we are searching for 16
int a = 0b1000'0000'0010'0000'0000;	10000000001000000000			
int b = a | (a >> 1);			11000000001100000000		
int c = b | (b >> 2);			11110000001111000000		
int d = c | (c >> 4);			11111111001111111100		
int e = d | (d >> 8);			11111111111111111111		
int f = e | (e >> 16); //if needed	11111111111111111111		
int res = (f + 1) >> 1;			524800 -> 524288		

// 6. Find the rightmost 1 in binary representation of x-------------------------------------
x ^ ( x & (x-1))	// or
x & (-x)
/* x & (-x) gives 1 -> 2 -> 4... which are powers of two, use `log2(res & -res);` to find idx
 *
 *   x  = 10  = (1010)2
 *   (-x) = -10 = (0110)2
 *   x & (-x) = (1010)2 & (0110)2 = (0010)2   
 */
	
// 7. Set nth bit----------------------------------------------------------------------------
x | (1 << n) 
/*
x = 10 = (1010)2 n = 2
1 << n = (0100)2 
x | (1 << n) = (1010)2 | (0100)2 = (1110)2   

	std::cout << (0 | 1 << 0) << std::endl;   1     00000
	std::cout << (0 | 1 << 1) << std::endl;   2     00010
	std::cout << (0 | 1 << 2) << std::endl;   4     00100
	std::cout << (0 | 1 << 3) << std::endl;   8     01000
	std::cout << (0 | 1 << 4) << std::endl;   16    10000
*/
	
// 8. Sum of Two Integers without + ---------------------------------------------------------
// adding can be done with ^, except of 1 + 1 case. Here use (a & b) << 1 and add up again	
	
int getSum(int a, int b) {
	int carry = 0;
	while (b != 0) {
		carry = (a & b) << 1;   // 01 & 01 = 01; 01 << 1 = 10; shift in all 1s pairs
		a = a ^ b;              // ^ for simple cases : 0 + 1 or 1 + 0
		b = carry;              // for 1 + 1 bit case      
	}
	return a;
}	
	
// 9. find 2 odd occuring elements in an array-----------------------------------------------
pair<int, int> findOddOccuring(vector<int> arr, int n) {
	int res = 0;
	for (int i = 0; i < n; i++)   res = res ^ arr[i];

	int k = log2(res & -res);
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (arr[i] & (1 << k))        // elements that have k'th bit 1
			x = x ^ arr[i];
		else                          // elements that have k'th bit 0
			y = y ^ arr[i];
	}
	return make_pair(x, y);
}


//-------------------------------------------------------------------------------------------

