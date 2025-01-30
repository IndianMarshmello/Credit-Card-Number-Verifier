/*
File: ccv.cpp
Author: Amaan Zaidi
Date: 2025-1-27
Description:
    Input a credit card Number, verifies if it is a real CCNUM using the Luhn algorithm.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
validccnum:
    4670009360252821
    374319177519123
    5329858139046159
invalidccnum:
    6670009760252821
    6670009960252821
*/
/*
returns:

    Invalid input - only enter numerical values that can be contained in a 64bit signed value (max 9223372036854775807)

    0 is invalid

    cardNumber is valid

    cardNumber is invalid

    Closing application.
*/

int checkNotText(std::string input,long long &ccnum) {
    try{
        ccnum = std::stoll(input);
    } catch (const std::exception& e) {
        std::cout << "Invalid input - only enter numerical values that can be contained in a 64bit signed value (max 9223372036854775807)" << std::endl;
        return 1;
    }
    return 0;

}

int checkDigits(std::vector<int> ccnumVec,int &sizeOfVec,long long ccnum) {
    switch(ccnumVec.size()) {
        case 13:
            sizeOfVec = 13;
            break;
        case 14:
            sizeOfVec = 14;
            break;
        case 15:
            sizeOfVec = 15;
            break;
        case 16:
            sizeOfVec = 16;
            break;
        default:
            std::cout << std::endl << ccnum << " is invalid, failed digit check" << std::endl;
            return 1;
    }
    return 0;
}

int checkPrefixValid(std::vector<int> ccnumVec, long long ccnum) {

    switch(ccnumVec[0]) {
        case 4:
            break;
        case 5:
            break;
        case 3:
            if (ccnumVec[1] != 7){
                std::cout << std::endl << ccnum << " is invalid, failed ID check" << std::endl;
                return 1;
            }
            break;
        case 6:
            break;
        default:
            std::cout << std::endl << ccnum << " is invalid, failed ID check" << std::endl;
            return 1;
    }

    return 0;
    
}

int checkNumberValid(std::vector<int> ccnumVec, int sizeOfVec, int &evens, int &odds) {

    std::vector<int> hold;
    for (int i = sizeOfVec - 1; i >= 0; --i) {
        // calculate the position (1-based) from right to left
        int position_from_right = sizeOfVec - i;

        if (position_from_right % 2 == 0) { // check position is even
            int doubledValue = ccnumVec[i] * 2; // double the value
            if (doubledValue > 9) { // check if doubling the position will make it more than single digit
                hold.push_back(doubledValue % 10);
                hold.push_back(doubledValue / 10);
                 // add the digits together to make a single digit, add to evens sum.
                evens += (hold[0] + hold[1]);
            } else {
                // add to evens sum.
                evens += doubledValue;
            }
            hold.clear();
        } else {
            // add to odds sum.
            odds = odds + ccnumVec[i];
        }
    }

}

int main() {
    while (true) {
    std::string input;
    long long ccnum;
    std::vector<int> ccnumVec;
    int sizeOfVec;

    // prompt and input ccnum
    std::cout << "Enter a Credit Card number to check validity for (-1 to exit application): ";
    std::cin >> input; // Use ccnum for now.

    // check for invalid input (i.e, can't be converted to int/long long) 
    if (checkNotText(input, ccnum) == 1) {
        continue;
    }

    // closing the application
    if (ccnum == -1) {
        std::cout << "Closing Application" << std::endl;
        return 0;
    }

    // I really don't understand the point of this block, but part of the project requirments.
    if (ccnum == 0) {
        std::cout << "0 is invalid" << std::endl;
        continue;
    }

    // Extract digits from the number
    long long copy = ccnum;
    while (copy > 0) {
        long long digit = copy % 10; // Get the Last digit
        ccnumVec.push_back(digit); // Add the digit to the vector
        copy /= 10; // Remove the last digit
    }
    
    std::reverse(ccnumVec.begin(), ccnumVec.end());

    // Check if the ccnum has a valid number of digits
    if (checkDigits(ccnumVec, sizeOfVec, ccnum) == 1) {
        continue;
    }

    // check for a valid ccnum identifier
    if (checkPrefixValid(ccnumVec, ccnum) == 1) {
        continue;
    }

    // Algorithm verifying ccnum
    int sum = 0, evens = 0, odds = 0;
    checkNumberValid(ccnumVec, sizeOfVec, evens, odds);
    sum = evens + odds;
    if ((sum % 10) != 0) {
        std::cout << ccnum << " is invalid, failed algorithm check." << std::endl;
    } else {
        std::cout << ccnum << " is valid" << std::endl;
    }

    ccnumVec.clear();
    }
    // ----prompt and input ccnum----check
    // ----verify number is between 13 and 16 digits----check
    // ----identify identifier "4", "5", "37", "6"----check
    /*----
    The Luhn Algorithm:
        group each digit based on even or odd position in the number starting from the right and going left.
        digits in an even position are doubled (if the product is 2 digits, add them together. ie. 7*2=14, 1+4=5.) before they are grouped.
        add both sums from sum of even position numbers and odd position numbers together and confirm it is divisible by 10 (sumofsums % 10 = 0).

    */
    // *----check
    
    return 0;
}