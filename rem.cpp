/*
 * rem.cpp
 *
 *  Created on: Oct. 20, 2019
 *      Author: navjot
 Reverse a number entered by user
 */
    #include <iostream>
    using namespace std;
    int main()
    {
        int n, reversedNumber = 0, remainder;
        cout << "Enter an integer: ";
        cin >> n;
        while(n != 0)
        {
            remainder = n%10;
            reversedNumber = reversedNumber*10 + remainder;
            n /= 10;
        }
        cout << "Reversed Number is:" << reversedNumber;
        return 0;
    }

